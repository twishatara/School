#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <math.h>
#include <pthread.h>

#define MAX_PAYLOAD_SIZE 508
#define MAX_SERVERS 10
#define INET_ADDRSTRLEN 16

typedef struct {
    int sequence_number;
    int ack_number;
    int is_ack;
    int is_last_packet;
    char *payload;  // Change to pointer for dynamic allocation
} Packet;

typedef struct {
    char ip[INET_ADDRSTRLEN];
    int port;
} ServerConfig;

typedef struct {
    int sockfd;
    struct sockaddr_in server_addr;
    Packet *packets;
    int total_packets;
    int window_size;
} ThreadArgs;

void log_packet(const char *type, int local_port, const char *remote_ip, int remote_port, int packet_sn) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    char timestamp[64];
    strftime(timestamp, 64, "%Y-%m-%dT%H:%M:%S", localtime(&tv.tv_sec));
    printf("%s.%06ldZ, %d, %s, %d, %s, %d\n", 
           timestamp, (long)tv.tv_usec, local_port, remote_ip, remote_port, type, packet_sn);
}

void free_packets(Packet *packets, int total_packets) {
    for (int i = 0; i < total_packets; ++i) {
        free(packets[i].payload);
    }
    free(packets);
}

Packet *create_packets(const char *filename, int *total_packets, int max_payload_size, const char *output_file_path) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Error opening file");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    *total_packets = (int)ceil((double)file_size / max_payload_size);

    Packet *packets = (Packet *)malloc(*total_packets * sizeof(Packet));
    if (!packets) {
        perror("Memory allocation failed");
        fclose(file);
        return NULL;
    }

    for (int i = 0; i < *total_packets; ++i) {
        packets[i].sequence_number = i;
        packets[i].ack_number = 0;
        packets[i].is_ack = 0;
        packets[i].is_last_packet = (i == (*total_packets - 1)) ? 1 : 0;
        packets[i].payload = (char *)malloc(max_payload_size * sizeof(char));

        if (!packets[i].payload) {
            perror("Memory allocation for payload failed");
            free_packets(packets, i);  // Free previously allocated packets
            fclose(file);
            return NULL;
        }

        if (i == 0) {
            // For the first packet, use the output file path as payload
            strncpy(packets[i].payload, output_file_path, max_payload_size);
        } else {
            size_t bytes_read = fread(packets[i].payload, sizeof(char), max_payload_size, file);
            packets[i].payload[bytes_read] = '\0';  // Null-terminate the payload
        }
    }

    fclose(file);
    return packets;
}

void send_file_to_server(int sockfd, struct sockaddr_in server_addr, Packet *packets, int total_packets, int window_size) {
    int base = 0;
    int nextseqnum = 0;
    struct timeval tv;
    fd_set readfds;

    while (base < total_packets) {
        while (nextseqnum < base + window_size && nextseqnum < total_packets) {
            sendto(sockfd, &packets[nextseqnum], sizeof(Packet) + strlen(packets[nextseqnum].payload), 0, (const struct sockaddr *)&server_addr, sizeof(server_addr));
            log_packet("DATA", ntohs(server_addr.sin_port), inet_ntoa(server_addr.sin_addr), ntohs(server_addr.sin_port), packets[nextseqnum].sequence_number);
            nextseqnum++;
        }

        tv.tv_sec = 2;  // Set timeout to 2 seconds
        tv.tv_usec = 0;
        FD_ZERO(&readfds);
        FD_SET(sockfd, &readfds);

        if (select(sockfd + 1, &readfds, NULL, NULL, &tv) > 0) {
            Packet ack_packet;
            recvfrom(sockfd, &ack_packet, sizeof(Packet), 0, NULL, NULL);
            if (ack_packet.is_ack) {
                log_packet("ACK", ntohs(server_addr.sin_port), inet_ntoa(server_addr.sin_addr), ntohs(server_addr.sin_port), ack_packet.sequence_number);
                base = ack_packet.sequence_number + 1;
            }
        } else {
            // Timeout, resend packets from base
            nextseqnum = base;
        }
    }
}

ServerConfig *read_server_config(const char *filename, int *num_servers) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening config file");
        return NULL;
    }

    ServerConfig *servers = malloc(MAX_SERVERS * sizeof(ServerConfig));
    *num_servers = 0;

    while (fscanf(file, "%15s %d", servers[*num_servers].ip, &servers[*num_servers].port) == 2) {
        (*num_servers)++;
    }

    fclose(file);
    return servers;
}

void *thread_send_file_to_server(void *arg) {
    ThreadArgs *args = (ThreadArgs *)arg;
    send_file_to_server(args->sockfd, args->server_addr, args->packets, args->total_packets, args->window_size);
    close(args->sockfd);
    free(arg);  // Free the dynamically allocated memory for thread arguments
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 7) {
        fprintf(stderr, "Usage: %s servn servaddr.conf mtu winsz infile outfile\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int servn = atoi(argv[1]);
    char *config_file = argv[2];
    int mtu = atoi(argv[3]);
    int window_size = atoi(argv[4]);
    char *input_file_path = argv[5];
    char *output_file_path = argv[6];
    int max_payload_size = mtu - sizeof(Packet);

    int num_servers;
    ServerConfig *servers = read_server_config(config_file, &num_servers);
    if (num_servers < servn) {
        fprintf(stderr, "Error: Number of servers in config file is less than servn\n");
        exit(EXIT_FAILURE);
    }

    int total_packets;
    Packet *packets = create_packets(input_file_path, &total_packets, max_payload_size, output_file_path);
    if (!packets) {
        free(servers);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < servn; ++i) {
        int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
        if (sockfd < 0) {
            perror("Cannot create socket");
            exit(EXIT_FAILURE);
        }

        struct sockaddr_in server_addr;
        memset(&server_addr, 0, sizeof(server_addr));
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(servers[i].port);
        if (inet_pton(AF_INET, servers[i].ip, &server_addr.sin_addr) <= 0) {
            fprintf(stderr, "Invalid address for server %d\n", i + 1);
            exit(EXIT_FAILURE);
        }

        send_file_to_server(sockfd, server_addr, packets, total_packets, window_size);
        close(sockfd);
    }
    
    pthread_t threads[servn];
    for (int i = 0; i < servn; ++i) {
        int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
        if (sockfd < 0) {
            perror("Cannot create socket");
            exit(EXIT_FAILURE);
        }

        struct sockaddr_in server_addr;
        memset(&server_addr, 0, sizeof(server_addr));
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(servers[i].port);
        if (inet_pton(AF_INET, servers[i].ip, &server_addr.sin_addr) <= 0) {
            fprintf(stderr, "Invalid address for server %d\n", i + 1);
            exit(EXIT_FAILURE);
        }

        // Allocate memory for thread arguments
        ThreadArgs *args = (ThreadArgs *)malloc(sizeof(ThreadArgs));
        if (!args) {
            perror("Failed to allocate memory for thread arguments");
            exit(EXIT_FAILURE);
        }
        args->sockfd = sockfd;
        args->server_addr = server_addr;
        args->packets = packets;
        args->total_packets = total_packets;
        args->window_size = window_size;

        // Create a thread for each server
        if (pthread_create(&threads[i], NULL, thread_send_file_to_server, (void *)args) != 0) {
            perror("Failed to create thread");
            exit(EXIT_FAILURE);
        }
    }

    // Wait for all threads to complete
    for (int i = 0; i < servn; ++i) {
        pthread_join(threads[i], NULL);
    }

    free_packets(packets, total_packets);
    free(servers);
    printf("File transfer to %d servers completed successfully\n", servn);
    return 0;
}
