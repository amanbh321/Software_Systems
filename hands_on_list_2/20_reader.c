/*
============================================================================
Name : 20_reader.c
Author : Aman Bahuguna
Description : Write two programs so that both can communicate by FIFO -Use one way communication.
Date: 20th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define FIFO_NAME "myfifo"

int main(void) {
    int fd;
    char buffer[80];

    // Open the FIFO for reading
    fd = open(FIFO_NAME, O_RDONLY);
    if (fd == -1) {
        perror("Failed to open FIFO for reading");
        exit(EXIT_FAILURE);
    }

    // Read the message from the FIFO
    read(fd, buffer, sizeof(buffer));
    printf("Received from FIFO: %s\n", buffer);

    // Close the FIFO
    close(fd);
    return 0;
}


/*
===========================================================================================
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ ./reader
Received from FIFO: Hello from the writer!
============================================================================================
*/