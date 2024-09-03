#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <errno.h>

// Desine Maximum size of each packet od data
#define MTU 512
// Set the limit of how many times a packet is retransmitted if not acknowledged
#define MAX_RETRANSMISSIONS 5
// Timeout in seconds
#define ACK_TIMEOUT 2

// Structure to represent the packet to be sent
typedef struct {
    // Sequence number - keep track of packets and their acks
    int sequenceNumber;
    // Data
    char data[MTU];
} Packet;

// Main function
int main(int argc, char **argv) {
    // Argument checking
    // Make sure that the program is run with the correct number of arguments
    if (argc != 5) {
        printf("Usage: %s <server IP> <server port> <input file path> <output file path>\n", argv[0]);
        return 1;
    }

    // Assign arguments to necessary variables
    const char *SERVER_IP = argv[1];
    int SERVER_PORT = atoi(argv[2]);
    char *inputFilePath = argv[3];
    char *outputFilePath = argv[4]; // Not used in this client, but may be needed for sending file path info to server

    // Create the UDP socket (SOCK_DGRAM) and IPv4 protocol family (PF_INET)
    int sockfd = socket(PF_INET, SOCK_DGRAM, 0);
    if(sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set up the server address to which the client will send packets
    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET; // IPv4 addresses
    serverAddr.sin_port = htons(SERVER_PORT);
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);

    // Open the input file to read in binary mode
    FILE *file = fopen(inputFilePath, "rb");
    if (file == NULL) {
        perror("Failed to open input file");
        exit(1);
    }

    int seqNum = 0;
    int ackNum;

    // Configire UDP socket so that when recvfrom is used it will wait 2 seconds for the data to arrive
    // Set structure used to handle internet addresses
    struct sockaddr_in fromAddr;
    // Store the address of the sender from whom the program receives the data
    socklen_t fromAddrLen = sizeof(fromAddr);
    // Set a receive timeout on the socket
    struct timeval tv; // Specify time intervals in seconds and microseconds
    tv.tv_sec = ACK_TIMEOUT;
    // No more microseconds added to the timeout period
    tv.tv_usec = 0;
    // use setsockopt to set options for the socket refered by the file descriptor
    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof(tv));

    Packet pkt;
    int bytes_read;
    // Read rge file in chunks of MTU size and send each chunk in a packet. Continue until the entire file is read and sent
    while ((bytes_read = fread(pkt.data, 1, MTU, file)) > 0) {
        pkt.sequenceNumber = seqNum;
        int attempts = 0;

        // Send a packet and wait for an acknowledgement
        while (attempts < MAX_RETRANSMISSIONS) {
            sendto(sockfd, &pkt, sizeof(Packet), 0, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
            printf("Sent packet %d\n", seqNum);
            // If acknowledgement is not received within timeout, retransmit the packet (max of MAX_RETRANSMISSIONS attempts)
            if (recvfrom(sockfd, &ackNum, sizeof(int), 0, (struct sockaddr *)&fromAddr, &fromAddrLen) < 0) {
                if (errno == EWOULDBLOCK) {
                    printf("Timeout, retransmitting packet %d\n", seqNum);
                    attempts++;
                } else {
                    perror("recvfrom failed");
                    break;
                }
            } else if (ackNum == seqNum) {
                printf("Received ACK for packet %d\n", seqNum);
                break; // Packet successfully sent and acknowledged
            }
        }

        if (attempts == MAX_RETRANSMISSIONS) {
            printf("Failed to send packet %d after %d attempts\n", seqNum, MAX_RETRANSMISSIONS);
            fclose(file);
            close(sockfd);
            exit(1);
        }

        seqNum++;
    }

    fclose(file);
    close(sockfd);
    printf("File transfer completed successfully.\n");

    return 0;
}
