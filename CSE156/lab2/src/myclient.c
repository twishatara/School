#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

#define MTU 512

typedef struct {
    int sockfd;
    struct sockaddr_in serverAddr;
    char* inputFilePath;
    char* outputFilePath;
} ThreadArgs;

// Function to handle the sending thread
// Open input file, read the data, send the data to the server
void* sendThreadFunc(void* arg) {
    // ThreadArgs is cast from void* to gain access to the arguments passed to the thread 
    ThreadArgs* args = (ThreadArgs*) arg;
    FILE *file = fopen(args->inputFilePath, "rb");
    char buffer[MTU];
    
    // If the file cannot be opened, and error is flagged, program exits 
    if (file == NULL) {
        perror("Failed to open input file");
        exit(1);
    }

    // Loop and read the data and send it to the server, until the end of file is reached
    while (fread(buffer, 1, MTU, file) > 0) {
        sendto(args->sockfd, buffer, MTU, 0, (struct sockaddr *) &args->serverAddr, sizeof(args->serverAddr));
    }

    // Close the file
    fclose(file);
    // Send EOF indicator
    const char *eofIndicator = "EOF";
    sendto(args->sockfd, eofIndicator, strlen(eofIndicator), 0, (struct sockaddr *) &args->serverAddr, sizeof(args->serverAddr));

    // Exit the thread
    pthread_exit(NULL);
}

// Function for handling the receving thread
// Opens the output file, receives the da†a from the server and writes it to the file. 
void* receiveThreadFunc(void* arg) {
    // Similar to sendThread, casts ThreadArgs from void*
    ThreadArgs* args = (ThreadArgs*) arg;
    FILE *file = fopen(args->outputFilePath, "wb");
    char buffer[MTU];
    int bytesReceived;

    // If the file cannot be opened, and error is flagged and the program exits
    if (file == NULL) {
        perror("Failed to open output file");
        exit(1);
    }

    // Set a timeout for receiving data
    struct timeval tv;
    tv.tv_sec =  5; // Timeout in seconds
    tv.tv_usec = 0; //Additional microseconds (not needed here)
    setsockopt(args->sockfd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);

    // Loop and receive data (continuous) from the server and write it to the output file until no more data is received
    while ((bytesReceived = recv(args->sockfd, buffer, MTU, 0)) > 0) {
        fwrite(buffer, 1, bytesReceived, file);
    }

    // Receive data from the server with a timeout
    if (bytesReceived < 0) {
        perror("Receive timeout or error");
    }

    // Close the file
    fclose(file);
    // Exit the pthread
    pthread_exit(NULL);
}

// Function to compare two files for data integrity
int compareFiles(const char *file1Path, const char *file2Path) {
    FILE *file1 = fopen(file1Path, "rb");
    FILE *file2 = fopen(file2Path, "rb");
    if (file1 == NULL || file2 == NULL) {
        if (file1) fclose(file1);
        if (file2) fclose(file2);
        return -1;  // Error opening files
    }

    // Assume that the files are identical
    int result = 1;
    char ch1, ch2;
    while (!feof(file1) && !feof(file2)) {
        ch1 = fgetc(file1);
        ch2 = fgetc(file2);

        if (ch1 != ch2) {
            result = 0;  // Files are different
            break;
        }
    }

    // Check if both files reached the end
    if (!(feof(file1) && feof(file2))) {
        result = 0;
    }

    fclose(file1);
    fclose(file2);
    return result;  // 1 if files are identical, 0 otherwise
}

// Main Function
int main(int argc, char **argv) {
    // Check if proper number of command line arguments were given
    if (argc != 5) {
        // Else print wrror message and quit
        printf("Usage: %s <server IP> <server port> <input file path> <output file path>\n", argv[0]);
        return 1;
    }

    // Initalize the necessary variables, and convert them to the correct and necessary format
    const char *SERVER_IP = argv[1];
    int SERVER_PORT = atoi(argv[2]);
    char *inputFilePath = argv[3];
    char *outputFilePath = argv[4];
    
    // Create UDP socket
    int sockfd = socket(PF_INET, SOCK_DGRAM, 0);
    // Set up the server address structure
    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);


    // Prepare the arguments to be passed through the threads
    ThreadArgs args;
    // Prep the socket
    args.sockfd = sockfd;
    // Prep the server address
    args.serverAddr = serverAddr;
    // Prep the input file path
    args.inputFilePath = inputFilePath;
    // Prep the output file path
    args.outputFilePath = outputFilePath;

    // Create 2 threads, one for sending data and one for receiving data
    pthread_t sendThread, receiveThread;
    pthread_create(&sendThread, NULL, sendThreadFunc, &args);
    pthread_create(&receiveThread, NULL, receiveThreadFunc, &args);

    // Wait for both threads to complete their tasks
    pthread_join(sendThread, NULL);
    pthread_join(receiveThread, NULL);

    // Close the socket
    close(sockfd);

    // Compare input and output files for data integrity
    if (compareFiles(argv[3], argv[4]) == 1) {
        printf("Files are identical. Data integrity verified.\n");
    } else {
        printf("Files are different. Data loss or corruption occurred.\n");
    }

    // Return to indiate success
    return 0;
}







