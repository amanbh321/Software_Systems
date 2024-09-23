/*
============================================================================
Name : 34a.c
Author : Aman Bahuguna
Description :  Write a program to create a concurrent server.
               a) use fork
Date: 23th Sep, 2024.
============================================================================
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT_NUMBER 8080
#define BUFFER_SIZE 1024

void process_client(int client_socket) {
    char buffer[BUFFER_SIZE] = {0};

    // Read data sent by the client
    ssize_t bytes_read = read(client_socket, buffer, BUFFER_SIZE);
    if (bytes_read > 0) {
        printf("Received from client: %s\n", buffer);
    } 
    else {
        perror("Failed to read from client");
    }

    // Send a response back to the client
    const char *response_message = "Hello from concurrent server!";
    send(client_socket, response_message, strlen(response_message), 0);
    printf("Response sent to client.\n");

    // Close the client socket
    close(client_socket);
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr;
    socklen_t addr_length = sizeof(server_addr);

    // Create a socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set up server address structure
    memset(&server_addr, 0, sizeof(server_addr)); // Clear the structure
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY; // Listen on all interfaces
    server_addr.sin_port = htons(PORT_NUMBER); // Convert port to network byte order

    // Bind the socket to the specified port
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Binding failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    // Start listening for incoming connections
    if (listen(server_socket, 5) < 0) { // Backlog size set to 5
        perror("Listening failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d\n", PORT_NUMBER);

    while (1) {
        // Accept a new client connection
        client_socket = accept(server_socket, (struct sockaddr *)&server_addr, &addr_length);
        if (client_socket < 0) {
            perror("Connection acceptance failed");
            continue; // Continue to the next iteration on error
        }

        // Fork a new process to handle the client
        pid_t pid = fork();
        if (pid < 0) {
            perror("Fork failed");
            close(client_socket);
            continue; // Continue on error
        }

        if (pid == 0) { // Child process
            close(server_socket); // Close the listening socket in the child
            process_client(client_socket);
            exit(0); // Exit child process after handling
        }

        // Parent process closes the client socket
        close(client_socket);
    }

    // This code will never be reached; added for clarity
    close(server_socket);
    return 0;
}



/*
===========================================================================================
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ gcc 34a.c
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ ./a.out
Server is listening on port 8080
Received from client: Hello from client!
Response sent to client.

aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ ./client
Message sent to server.
Response from server: Hello from concurrent server!
============================================================================================
*/
