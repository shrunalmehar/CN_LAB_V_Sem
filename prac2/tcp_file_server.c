#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 10143
#define BUFFER_SIZE 1024

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    char buffer[BUFFER_SIZE];
    char filename[256];
    FILE *fp;

    // Create TCP socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("Socket creation failed");
        exit(1);
    }

    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);
    address.sin_addr.s_addr = INADDR_ANY;

    // Bind
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(1);
    }

    // Listen
    if (listen(server_fd, 5) < 0) {
        perror("Listen failed");
        close(server_fd);
        exit(1);
    }
    printf("Server listening on port %d...\n", PORT);

    socklen_t addrlen = sizeof(address);
    new_socket = accept(server_fd, (struct sockaddr*)&address, &addrlen);
    if (new_socket < 0) {
        perror("Accept failed");
        close(server_fd);
        exit(1);
    }
    printf("Connection established with client.\n");

    // Receive filename first
    recv(new_socket, filename, sizeof(filename), 0);
    printf("📥 Receiving file: %s\n", filenam
