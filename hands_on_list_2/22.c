/*
============================================================================
Name : 22.c
Author : Aman Bahuguna
Description : Write a program to wait for data to be written into FIFO within 10 seconds, use select
              system call with FIFO.
Date: 20th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/time.h>

#define FIFO_NAME "myfifo"
#define BUFFER_SIZE 80

int main(void) {
    int fifo_fd;
    char buffer[BUFFER_SIZE];
    fd_set read_fds;
    struct timeval timeout;

    // Open FIFO for reading
    fifo_fd = open(FIFO_NAME, O_RDONLY);
    if (fifo_fd == -1) {
        perror("Failed to open FIFO");
        return EXIT_FAILURE;
    }

    // Initialize the file descriptor set
    FD_ZERO(&read_fds);
    FD_SET(fifo_fd, &read_fds);

    // Set timeout for select (10 seconds)
    timeout.tv_sec = 10;
    timeout.tv_usec = 0;

    // Wait for data to be available
    int retval = select(fifo_fd + 1, &read_fds, NULL, NULL, &timeout);
    if (retval == -1) {
        perror("select error");
        close(fifo_fd);
        return EXIT_FAILURE;
    }     
    else if (retval == 0) {
        printf("No data available within 10 seconds.\n");
        close(fifo_fd);
        return EXIT_SUCCESS;
    }

    // Read from FIFO if data is available
    read(fifo_fd, buffer, sizeof(buffer));
    printf("Data from FIFO: %s\n", buffer);

    // Close the FIFO
    close(fifo_fd);
    return EXIT_SUCCESS;
}

/*
===========================================================================================
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ gcc 22.c
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ mkfifo ourfifo
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ ./a.out
Data from FIFO: Hello, FIFO!

aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ echo "Hello, FIFO!" > myfifo
============================================================================================
*/