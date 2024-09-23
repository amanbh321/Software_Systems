/*
============================================================================
Name : 33.c
Author : Aman Bahuguna
Description :  Write a program to communicate between two machines using socket.
Date: 22th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT_NUMBER 8080
#define BUFFER_SIZE 1024

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr;
    socklen_t addr_length = sizeof(server_addr);
    char receive_buffer[BUFFER_SIZE] = {0};

    // Create a socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set up the server address structure
    memset(&server_addr, 0, sizeof(server_addr)); // Initialize to zero
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY; // Allow connections from any IP
    server_addr.sin_port = htons(PORT_NUMBER); // Convert port to network byte order

    // Bind the socket to the address and port
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Binding failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    // Start listening for incoming connections
    if (listen(server_socket, 3) < 0) {
        perror("Listening failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d\n", PORT_NUMBER);

    // Accept a new client connection
    client_socket = accept(server_socket, (struct sockaddr *)&server_addr, &addr_length);
    if (client_socket < 0) {
        perror("Accepting connection failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    // Read data sent by the client
    ssize_t bytes_read = read(client_socket, receive_buffer, BUFFER_SIZE);
    if (bytes_read > 0) {
        printf("Message from client: %s\n", receive_buffer);
    } else {
        perror("Failed to read message from client");
    }

    // Send a response back to the client
    const char *server_response = "Hello from the server!";
    send(client_socket, server_response, strlen(server_response), 0);
    printf("Response sent to client.\n");

    // Close the sockets
    close(client_socket);
    close(server_socket);

    return EXIT_SUCCESS;
}


/*
===========================================================================================
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ gcc 33_server.c -o server
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ gcc 33_client.c -o client
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ ./server
Server is listening on port 8080
Message from client: Hello from client!
Response sent to client.
============================================================================================
*/
