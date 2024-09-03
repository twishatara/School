#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>

#define MAX_PAYLOAD_SIZE 508
#define MAX_PATH 1024

typedef struct {
    int sequence_number;
    int ack_number;
    int is_ack;
    int is_last_packet;
    char payload[MAX_PAYLOAD_SIZE];
} Packet;

// Function to create directories if they don't exist
void create_directories(const char *path) {
    char tmp[MAX_PATH];
    strcpy(tmp, path);
    size_t len = strlen(tmp);
    if (tmp[len - 1] == '/') {
        tmp[len - 1] = '\0';
    }

    for (char *p = tmp + 1; *p; p++) {
        if (*p == '/') {
            *p = '\0';
            if (access(tmp, F_OK) != 0) {
                if (mkdir(tmp, S_IRWXU) != 0 && errno != EEXIST) {
                    perror("mkdir failed");
                    exit(EXIT_FAILURE);
                }
            }
            *p = '/';
        }
    }

    if (access(tmp, F_OK) != 0) {
        if (mkdir(tmp, S_IRWXU) != 0 && errno != EEXIST) {
            perror("mkdir failed");
            exit(EXIT_FAILURE);
        }
    }
}

// Function to handle packets
void handle_packet(int sockfd, struct sockaddr_in cliaddr, Packet recv_packet, const char *folder_name) {
    char current_output_path[MAX_PATH];
    snprintf(current_output_path, sizeof(current_output_path), "%s/outfile.txt", folder_name);
    static int file_created = 0;

    if (!file_created) {
        create_directories("server1_folder");
        file_created = 1;
    }

    FILE *file = fopen(current_output_path, "ab");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    if (fwrite(recv_packet.payload, 1, strlen(recv_packet.payload), file) != strlen(recv_packet.payload)) {
        perror("Error writing to file");
        fclose(file);
        exit(EXIT_FAILURE);
    }
    fclose(file);

    // Send acknowledgment for the received packet
    Packet ack_packet;
    ack_packet.sequence_number = recv_packet.sequence_number;
    ack_packet.is_ack = 1;
    sendto(sockfd, &ack_packet, sizeof(Packet), 0, (const struct sockaddr *)&cliaddr, sizeof(cliaddr));
}

void start_server(int port, const char *folder_name) {
    int sockfd;
    struct sockaddr_in servaddr, cliaddr;

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(port);

    if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    while (1) {
        Packet recv_packet;
        socklen_t len = sizeof(cliaddr);
        ssize_t n = recvfrom(sockfd, &recv_packet, sizeof(Packet), 0, (struct sockaddr *)&cliaddr, &len);

        if (n > 0 && !recv_packet.is_ack) {
            handle_packet(sockfd, cliaddr, recv_packet, folder_name);
        }
    }

    close(sockfd);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s port_number droppc folder_name\n", argv[0]);
        return EXIT_FAILURE;
    }

    int port = atoi(argv[1]);
    // int droppc = atoi(argv[2]); // Not implemented yet
    char *folder_name = argv[3];

    start_server(port, folder_name);
    return 0;
}
