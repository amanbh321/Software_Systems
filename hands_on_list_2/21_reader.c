/*
============================================================================
Name : 21_reader.c
Author : Aman Bahuguna
Description : Write two programs so that both can communicate by FIFO -Use two way communications.
Date: 20th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#define FIFO_NAME_WRITE "fifo_write"
#define FIFO_NAME_READ "fifo_read"

int main(void) {
    int fd_write, fd_read;
    char buffer[80];

    // Open the FIFO for reading
    fd_read = open(FIFO_NAME_WRITE, O_RDONLY);
    if (fd_read == -1) {
        perror("Failed to open FIFO for reading");
        exit(EXIT_FAILURE);
    }

    // Read the message from the writer
    read(fd_read, buffer, sizeof(buffer));
    printf("Received from writer: %s\n", buffer);

    // Open the FIFO for writing
    fd_write = open(FIFO_NAME_READ, O_WRONLY);
    const char *response = "Hello from the reader!";
    write(fd_write, response, strlen(response) + 1);
    printf("Response sent to writer: %s\n", response);

    // Close the FIFOs
    close(fd_read);
    close(fd_write);
    return 0;
}

/*
===========================================================================================
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ ./reader
Received from writer: Hello from the writer!
Response sent to writer: Hello from the reader!
============================================================================================
*/