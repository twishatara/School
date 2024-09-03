#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

void error_flag(const char *msg) {
    fprintf(stderr, "Error: %s\n", msg);
    exit(1);
}

void send_request(const char *host, const char *path, const char *method, int port) {
    int sockfd, n;
    struct sockaddr_in server_addr;
    struct hostent *server;
    char buffer[BUFFER_SIZE];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error_flag("ERROR opening socket");

    server = gethostbyname(host);
    if (server == NULL)
        error_flag("ERROR, no such host\n");

    bzero((char *) &server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&server_addr.sin_addr.s_addr, server->h_length);
    server_addr.sin_port = htons(port);

    if (connect(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0)
        error_flag("ERROR connecting");

    snprintf(buffer, BUFFER_SIZE, "%s %s HTTP/1.1\r\nHost: %s\r\nConnection: close\r\n\r\n", method, path, host);
    n = write(sockfd, buffer, strlen(buffer));
    if (n < 0)
        error_flag("ERROR writing to socket");

    while ((n = read(sockfd, buffer, BUFFER_SIZE - 1)) > 0) {
        buffer[n] = '\0';
        printf("%s", buffer);
    }
    if (n < 0)
        error_flag("ERROR reading from socket");

    close(sockfd);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <hostname> <URL>\n", argv[0]);
        exit(1);
    }

    const char *host = argv[1];
    char *url = argv[2];
    const char *method = "GET";
    int port = 80;
    char path[BUFFER_SIZE];

    char *portStr = strchr(url, ':');
    if (portStr) {
        *portStr = '\0';  // Split the URL at the colon
        port = atoi(portStr + 1);  // Extract the port number
        strcpy(path, strchr(portStr + 1, '/'));  // Get the path
    } else {
        strcpy(path, url);  // Use the URL as the path if no port is specified
    }

    printf("Sending %s request to %s:%d%s\n", method, host, port, path);
    send_request(host, path, method, port);

    return 0;
}


