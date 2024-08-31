/*
============================================================================
Name : 4.c
Author : Aman Bahuguna
Description : Write a program to open an existing file with read write mode. 
              Try O_EXCL flag also
Date: 25th Aug, 2024.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main(void) {
    int fileDescriptor = open("example.txt", O_RDWR); // Open the file in read-write mode
    if (fileDescriptor == -1) {
        perror("Failed to open the file");
        exit(EXIT_FAILURE);
    }
    printf("Successfully opened 'example.txt' in read-write mode.\n");

    close(fileDescriptor); // Close the file descriptor

    // Attempt to open the file with O_EXCL to ensure it is not overwritten
    fileDescriptor = open("example.txt", O_RDWR | O_CREAT | O_EXCL, 0644);
    if (fileDescriptor == -1) {
        if (errno == EEXIST) {
            printf("Cannot open 'example.txt' with O_EXCL because it already exists.\n");
        } else {
            perror("Failed to open the file with O_EXCL flag");
            exit(EXIT_FAILURE);
        }
    } else {
        printf("Successfully opened 'example.txt' with O_EXCL flag.\n");
        close(fileDescriptor); // Close the file descriptor
    }

    return 0;
}


/*
============================================================================
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_1$ gcc 4.c
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_1$ ./a.out
Successfully opened 'example.txt' in read-write mode.
Cannot open 'example.txt' with O_EXCL because it already exists.
============================================================================
*/