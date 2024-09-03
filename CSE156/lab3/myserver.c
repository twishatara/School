#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <time.h>

// Define size of the buffer for receiving data
#define BUFFER_SIZE 1024
// Desine the size of data in each packet
#define MTU 512

// Flag to control the main loop, altered by signal handler ro sadely stop the server
volatile sig_atomic_t keepRunning = 1;
// Controks the prob of a dropping packet, set on command line args
int dropPercentage = 0;

// Define linked list structure for packets
typedef struct Packet {
    // Sewuence number
    int sequenceNumber;
    // Data
    char data[MTU];
    // Pointer to the next packet
    struct Packet *next;
} Packet;

// Bundle client address, server socket, buffer, and bytes received into a single sturcture, passed to threads
typedef struct {
    struct sockaddr_in clientAddr;
    int serverSock;
    char buffer[BUFFER_SIZE];
    int bytesReceived;
} ClientData;

// Function for graceful termination of the server loop when an interrupt signal (CtrlC) is received
void sigHandler(int dummy) {
    keepRunning = 0;
}

// Log when a packet is dropped, including a timestamp and the sequence number of the dropped packet
void logDropPacket(int sequenceNumber) {
    char timestamp[30];
    time_t now = time(NULL);
    struct tm *tm = gmtime(&now);
    strftime(timestamp, 30, "%Y-%m-%dT%H:%M:%S.000Z", tm);
    printf("%s, DROP DATA, %d\n", timestamp, sequenceNumber);
}

// Function inserts packet into a linked list in sequential order based on their sequence numbers
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

// Function intened to process the linked list of packets and save them to a file
void processAndSavePackets(int serverSock, const struct sockaddr_in *clientAddr, Packet **head, const char* filePath) {
    FILE *file = fopen(filePath, "wb");
    if (file == NULL) {
        perror("Failed to open file for writing");
        return;
    }

    while (*head != NULL) {
        fwrite((*head)->data, 1, MTU, file);
        Packet *temp = *head;
        *head = (*head)->next;
        free(temp);
    }

    fclose(file);
}

// Function hat is the threads main function. Processes each received datagram, decides wether to drop it, adds it to the packet list, and sends and acknowledgement back to the client
void *handleDatagram(void *arg) {
    ClientData *clientData = (ClientData *)arg;
    Packet *head = NULL;

    int seqNum;
    memcpy(&seqNum, clientData->buffer, sizeof(int));

    if ((rand() % 100) < dropPercentage) {
        logDropPacket(seqNum);
        free(clientData);
        pthread_exit(NULL);
    }

    char *packetData = clientData->buffer + sizeof(int);
    addPacketInOrder(&head, seqNum, packetData);

    // Send ACK for received packet
    sendto(clientData->serverSock, &seqNum, sizeof(seqNum), 0, 
           (struct sockaddr *)&clientData->clientAddr, sizeof(clientData->clientAddr));
    printf("Sent ACK for packet %d\n", seqNum);

    // Note: Implement the logic to determine when to call processAndSavePackets
    // processAndSavePackets(clientData->serverSock, &clientData->clientAddr, &head, "output_file_path_here");

    free(clientData);
    pthread_exit(NULL);
}

// Main loop
int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <port> <drop percentage>\n", argv[0]);
        return 1;
    }

    int port = atoi(argv[1]);
    dropPercentage = atoi(argv[2]);

    signal(SIGINT, sigHandler);

    // Initialize the server
    int serverSock;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addr_size = sizeof(clientAddr);

    serverSock = socket(PF_INET, SOCK_DGRAM, 0);
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    // Bind to a socket
    if (bind(serverSock, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Bind failed");
        return 1;
    }

    printf("UDP Server is running on port %d\n", port);

    // Enter loop to receive datagrams
    while (keepRunning) {
        ClientData *clientData = malloc(sizeof(ClientData));
        clientData->serverSock = serverSock;
        clientData->bytesReceived = recvfrom(serverSock, clientData->buffer, BUFFER_SIZE, 0, 
                                             (struct sockaddr *)&clientAddr, &addr_size);
        // For each received datagram, there is a new thread created to handle it - concurrent processing
        if (clientData->bytesReceived > 0) {
            pthread_t threadId;
            if (pthread_create(&threadId, NULL, handleDatagram, clientData) != 0) {
                perror("Failed to create thread");
                free(clientData);
            }
            // Allow threads to clean themselves up
            pthread_detach(threadId);
        } else {
            free(clientData);
        }
    }

    close(serverSock);
    printf("Server stopped.\n");
    return 0;
}

