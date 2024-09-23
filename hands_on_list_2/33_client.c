/*
============================================================================
Name : 32c.c
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
    int client_socket;
    struct sockaddr_in server_address;
    const char *client_message = "Hello from client!";
    char response_buffer[BUFFER_SIZE] = {0};

    // Create a socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0) {
        perror("Socket creation failed");
        return EXIT_FAILURE;
    }

    // Set up the server address structure
    memset(&server_address, 0, sizeof(server_address)); // Clear the structure
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT_NUMBER); // Convert port to network byte order

    // Convert the IPv4 address from text to binary
    if (inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr) <= 0) { // Update with the server's IP as needed
        perror("Invalid address or Address not supported");
        close(client_socket);
        return EXIT_FAILURE;
    }

    // Establish a connection to the server
    if (connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("Connection to server failed");
        close(client_socket);
        return EXIT_FAILURE;
    }

    // Send a message to the server
    send(client_socket, client_message, strlen(client_message), 0);
    printf("Message sent to server.\n");

    // Receive the server's response
    ssize_t bytes_read = read(client_socket, response_buffer, BUFFER_SIZE);
    if (bytes_read > 0) {
        printf("Response from server: %s\n", response_buffer);
    } 
    else {
        perror("Failed to read response from server");
    }

    // Close the socket
    close(client_socket);

    return EXIT_SUCCESS;
}


/*
===========================================================================================
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ ./client
Message sent to server.
Response from server: Hello from the server!
============================================================================================
*/
