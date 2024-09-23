/*
============================================================================
Name : 20_writer.c
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
    const char *message = "Hello from the writer!";
    char buffer[80];

    // Create FIFOs if they don't exist
    mkfifo(FIFO_NAME_WRITE, 0666);
    mkfifo(FIFO_NAME_READ, 0666);

    // Open the FIFO for writing
    fd_write = open(FIFO_NAME_WRITE, O_WRONLY);
    if (fd_write == -1) {
        perror("Failed to open FIFO for writing");
        exit(EXIT_FAILURE);
    }

    // Write the message to the reader
    write(fd_write, message, strlen(message) + 1);
    printf("Message written to FIFO: %s\n", message);

    // Open the FIFO for reading
    fd_read = open(FIFO_NAME_READ, O_RDONLY);
    read(fd_read, buffer, sizeof(buffer));
    printf("Received from reader: %s\n", buffer);

    // Close the FIFOs
    close(fd_write);
    close(fd_read);
    return 0;
}


/*
===========================================================================================
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ gcc -o writer 21_writer.c
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ gcc -o reader 21_reader.c
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ ./writer
Message written to FIFO: Hello from the writer!
Received from reader: Hello from the reader!
============================================================================================
*/