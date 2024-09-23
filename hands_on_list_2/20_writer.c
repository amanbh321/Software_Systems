/*
============================================================================
Name : 20_writer.c
Author : Aman Bahuguna
Description : Write two programs so that both can communicate by FIFO -Use one way communication.
Date: 20th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>  // Include for mkfifo
#include <sys/stat.h>   // Include for mkfifo

#define FIFO_NAME "myfifo"

int main(void) {
    int fd;
    const char *message = "Hello from the writer!";

    // Create the FIFO if it doesn't exist
    mkfifo(FIFO_NAME, 0666);

    // Open the FIFO for writing
    fd = open(FIFO_NAME, O_WRONLY);
    if (fd == -1) {
        perror("Failed to open FIFO for writing");
        exit(EXIT_FAILURE);
    }

    // Write the message to the FIFO
    write(fd, message, strlen(message) + 1); // +1 for null terminator
    printf("Message written to FIFO: %s\n", message);

    // Close the FIFO
    close(fd);
    return 0;
}

/*
===========================================================================================
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ gcc -o writer 20_writer.c
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ gcc -o reader 20_reader.c
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ ./writer
Message written to FIFO: Hello from the writer!
============================================================================================
*/