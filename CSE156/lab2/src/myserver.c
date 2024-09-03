#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>

#define BUFFER_SIZE 1024
#define MTU 512

// Global variable for signal handling
// sig_atomic so it can be safley accessed across all threads and signal handers
volatile sig_atomic_t keepRunning = 1;

// Packet structure for the linked list for packet ordering
typedef struct Packet {
    int sequenceNumber;
    char data[MTU];
    struct Packet *next;
} Packet;

// ClientData structure for the information about each clients datagram
typedef struct {
    struct sockaddr_in clientAddr;
    int serverSock;
    char buffer[BUFFER_SIZE];
    int bytesReceived;
} ClientData;

// Function, sets the keepRunning flag to 0, causing main loop to exit
void sigHandler(int dummy) {
    keepRunning = 0;
}

// Function to add packet to the linked list in order based on sequence number
void addPacketInOrder(Packet **head, int seqNum, const char *data) {
    Packet *newNode = (Packet *)malloc(sizeof(Packet));
    newNode->sequenceNumber = seqNum;
    memcpy(newNode->data, data, MTU);
    newNode->next = NULL;

    if (*head == NULL || (*head)->sequenceNumber > seqNum) {
        newNode->next = *head;
        *head = newNode;
    } else {
        Packet *current = *head;
        while (current->next != NULL && current->next->sequenceNumber < seqNum) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

// Function to echo packets in the correct order
void processAndEchoPackets(int serverSock, const struct sockaddr_in *clientAddr, Packet **head) {
    while (*head != NULL) {
        sendto(serverSock, (*head)->data, MTU, 0, (struct sockaddr *)clientAddr, sizeof(*clientAddr));
        Packet *temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}

// Thread function to handle each packet
void *handleDatagram(void *arg) {
    ClientData *clientData = (ClientData *)arg;
    Packet *head = NULL;

    // Extract sequence number and data from the buffer
    int seqNum;
    memcpy(&seqNum, clientData->buffer, sizeof(int));
    // Extract the packet data, skipping the sequence number
    char *packetData = clientData->buffer + sizeof(int);

    // Add the packet to the linked list
    addPacketInOrder(&head, seqNum, packetData);

    // Process and echo the packets
    processAndEchoPackets(clientData->serverSock, &clientData->clientAddr, &head);

    // Free the linked list
    while (head != NULL) {
        Packet *temp = head;
        head = head->next;
        free(temp);
    }

    // Free the allocated memory for client data
    free(clientData);

    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    // Check if the correct number of arguments were given in command line
    if (argc != 2) {
        printf("Usage: %s <port>\n", argv[0]);
        return 1;
    }

    // Set up the signal handler for the SIGINT signal, press CTRL C
    signal(SIGINT, sigHandler);

    // Convert the port number from a string to an integer and checks if its a valid port
    int port = atoi(argv[1]);
    if (port <= 0) {
        printf("Invalid port number.\n");
        return 1;
    }

    // Create a UDP socket for the server
    int serverSock;
    // Initialize  structures for handling network address
    struct sockaddr_in serverAddr, clientAddr;
    // Initialize var to store the size of the client address structure
    socklen_t addr_size = sizeof(clientAddr);
    // Set up the server address 
    serverSock = socket(PF_INET, SOCK_DGRAM, 0);
    memset(&serverAddr, 0, sizeof(serverAddr));
    // Set IPv4
    serverAddr.sin_family = AF_INET;
    // Set port number to the one provided in command line
    serverAddr.sin_port = htons(port);
    // Accept connectuons to any interface
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    // Bind the socket to the server address
    // If binding fails, it prints an error and exits
    if (bind(serverSock, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Bind failed");
        return 1;
    }

    printf("UDP Server is running on port %d\n", port);

    // Initialize head for the packet linked list
    Packet *head = NULL;

    // Start the main loop
    while (keepRunning) {
        // Allocate memory for CLientData to store info about each received packet
        ClientData *clientData = malloc(sizeof(ClientData));
        // Receives data from the client and stores it in clientData->buffer
        clientData->serverSock = serverSock;
        //socklen_t addr_size = sizeof(clientData->clientAddr);

        // Receive data into the buffer of clientData
        clientData->bytesReceived = recvfrom(serverSock, clientData->buffer, BUFFER_SIZE, 0, 
                                             (struct sockaddr *)&clientData->clientAddr, &addr_size);
        // Check if the data was received
        if (clientData->bytesReceived > 0) {
            // Check for EOF indicator
            if (strncmp(clientData->buffer, "EOF", 3) == 0) {
                free(clientData);
                break; // Break out of the loop when EOF is detected
            }
            
            // Extract the sequence number from the beginning of the buffer
            int sequenceNumber;
            // Copy the first few bytes from clientData into sequenceNumber
            memcpy(&sequenceNumber, clientData->buffer, sizeof(int));

            // Rest of the packet is the actual data, skip sequence num
            //char *packetData = clientData->buffer + sizeof(int);

            // Create a thread to handle the packet (MAYBE pass both sequence number and packet data)
            pthread_t threadId;
            // If creation fails print error
            if (pthread_create(&threadId, NULL, handleDatagram, clientData) != 0) {
                perror("Failed to create thread");
                free(clientData);
            }

            // Detach the thread to allow it to run independently
            pthread_detach(threadId);
        } else {
            free(clientData);
        }
    }


    // Process remaining packets in the linked list
    processAndEchoPackets(serverSock, &clientAddr, &head);

    // Close the server socket
    close(serverSock);
    // Print the message indicating that the server has stopped
    printf("Server stopped.\n");
    // Return 0 for indicating success`
    return 0;
}


