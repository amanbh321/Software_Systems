/*
============================================================================
Name : 12.c
Author : Aman Bahuguna
Description : Write a program to find out the opening mode of a file. Use fcntl.
Date: 27th Aug, 2024.
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    int fd;
    int flags;

    // Ensure a file path is provided as a command-line argument
    if (argc != 2) {
        printf("Usage: %s <file path>\n", argv[0]);
        return 1;
    }

    // Open the file
    fd = open(argv[1], O_RDONLY); // Initially open in read-only mode to ensure the file can be accessed
    if (fd < 0) {
        perror("Failed to open file");
        return 1;
    }

    // Get the file status flags
    flags = fcntl(fd, F_GETFL);
    if (flags < 0) {
        perror("fcntl failed");
        close(fd);
        return 1;
    }

    // Determine the access mode
    int access_mode = flags & O_ACCMODE;
    switch (access_mode) {
        case O_RDONLY:
            printf("The file is opened in read-only mode.\n");
            break;
        case O_WRONLY:
            printf("The file is opened in write-only mode.\n");
            break;
        case O_RDWR:
            printf("The file is opened in read-write mode.\n");
            break;
        default:
            printf("Unknown access mode.\n");
            break;
    }

    // Check for additional flags
    if (flags & O_APPEND)
        printf("The file is opened in append mode.\n");
    if (flags & O_NONBLOCK)
        printf("The file is opened in non-blocking mode.\n");
    if (flags & O_SYNC)
        printf("The file is opened in synchronous write mode.\n");
    if (flags & O_CREAT)
        printf("The file was opened with O_CREAT flag.\n");
    if (flags & O_TRUNC)
        printf("The file was opened with O_TRUNC flag.\n");

    // Close the file descriptor
    close(fd);

    return 0;
}


/*
=======================================================================
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_1$ gcc 12.c
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_1$ ./a.out file3.txt
The file is opened in read-only mode.
========================================================================
*/