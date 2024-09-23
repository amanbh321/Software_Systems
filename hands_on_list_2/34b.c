/*
============================================================================
Name : 34a.c
Author : Aman Bahuguna
Description :  Write a program to create a concurrent server.
               b) use pthread_create
Date: 23th Sep, 2024.
============================================================================
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void *client_handler(void *socket_ptr) {
    int client_socket = *(int *)socket_ptr;
    free(socket_ptr); // Free the dynamically allocated memory
    char buffer[BUFFER_SIZE] = {0};

    // Read message from the client
    ssize_t bytes_read = read(client_socket, buffer, BUFFER_SIZE);
    if (bytes_read > 0) {
        printf("Received message from client: %s\n", buffer);
    } 
    else {
        perror("Error reading from client");
    }

    // Send a response back to the client
    const char *response_message = "Hello from the pthread server!";
    send(client_socket, response_message, strlen(response_message), 0);
    printf("Response sent to client.\n");

    // Close the client socket
    close(client_socket);
    return NULL;
}

int main() {
    int server_socket, *new_socket;
    struct sockaddr_in server_addr;
    socklen_t addr_len = sizeof(server_addr);

    // Create a socket for the server
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set up the server address structure
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY; // Bind to any available interface
    server_addr.sin_port = htons(PORT); // Set the port

    // Bind the socket to the specified address and port
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Binding failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    // Start listening for incoming connections
    if (listen(server_socket, 5) < 0) { // Allow up to 5 pending connections
        perror("Listening failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d\n", PORT);

    while (1) {
        // Accept a new client connection
        new_socket = malloc(sizeof(int)); // Allocate memory for the socket
        *new_socket = accept(server_socket, (struct sockaddr *)&server_addr, &addr_len);

        if (*new_socket < 0) {
            perror("Failed to accept connection");
            free(new_socket);
            continue;
        }

        pthread_t thread_id;
        // Create a new thread to handle the client
        if (pthread_create(&thread_id, NULL, client_handler, (void *)new_socket) != 0) {
            perror("Thread creation failed");
            close(*new_socket);
            free(new_socket);
        }
        
        pthread_detach(thread_id); // Detach the thread to clean up after it finishes
    }

    // Close the server socket (unreachable code in this infinite loop)
    close(server_socket);
    return 0;
}



/*
===========================================================================================
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ gcc 34b.c
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ ./a.out
Server is listening on port 8080
Received message from client: Hello from client!
Response sent to client.

aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ ./client
Message sent to server.
Response from server: Hello from the pthread server!
============================================================================================
*/
