/*
============================================================================
Name : Q11.c
Author : Aman Bahuguna
Description : Write a program to open a file, duplicate the file descriptor and 
              append the file with both the descriptors and check whether the 
              file is updated properly or not.
              a. use dup
              b. use dup2
              c. use fcntl
Date: 26th Aug, 2024.
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd, fd_dup, fd_dup2, fd_fcntl;
    ssize_t bytes_written;
    char buffer1[] = "Hello, ";
    char buffer2[] = "World!";
    char buffer3[] = " How are you?";
    
    // Open the file in read-write mode and append mode, create it if it doesn't exist
    fd = open("example_dup.txt", O_RDWR | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd < 0) {
        perror("Failed to open file");
        return 1;
    }

    // Duplicate the file descriptor using dup
    fd_dup = dup(fd);
    if (fd_dup < 0) {
        perror("dup failed");
        close(fd);
        return 1;
    }

    // Duplicate the file descriptor using dup2
    fd_dup2 = dup2(fd, fd_dup + 1);  // Assuming fd_dup + 1 is free
    if (fd_dup2 < 0) {
        perror("dup2 failed");
        close(fd);
        close(fd_dup);
        return 1;
    }

    // Duplicate the file descriptor using fcntl
    fd_fcntl = fcntl(fd, F_DUPFD, fd_dup2 + 1);  // Assuming fd_dup2 + 1 is free
    if (fd_fcntl < 0) {
        perror("fcntl failed");
        close(fd);
        close(fd_dup);
        close(fd_dup2);
        return 1;
    }

    // Append data using the original file descriptor
    bytes_written = write(fd, buffer1, sizeof(buffer1) - 1);
    if (bytes_written < 0) {
        perror("Failed to write with original descriptor");
    }

    // Append data using the duplicated file descriptor (dup)
    bytes_written = write(fd_dup, buffer2, sizeof(buffer2) - 1);
    if (bytes_written < 0) {
        perror("Failed to write with dup descriptor");
    }

    // Append data using the duplicated file descriptor (dup2)
    bytes_written = write(fd_dup2, buffer3, sizeof(buffer3) - 1);
    if (bytes_written < 0) {
        perror("Failed to write with dup2 descriptor");
    }

    // Close all file descriptors
    close(fd);
    close(fd_dup);
    close(fd_dup2);
    close(fd_fcntl);

    // Open the file again to verify the content
    fd = open("example_dup.txt", O_RDONLY);
    if (fd < 0) {
        perror("Failed to open file for reading");
        return 1;
    }

    // Read and print the file content
    char content[256];
    ssize_t bytes_read = read(fd, content, sizeof(content) - 1);
    if (bytes_read >= 0) {
        content[bytes_read] = '\0';  // Null-terminate the string
        printf("File content:\n%s\n", content);
    } else {
        perror("Failed to read file content");
    }

    // Close the file descriptor
    close(fd);

    return 0;
}

/*
=======================================================================
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_1$ gcc 11.c
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_1$ ./a.out file3.txt
File content:
Hello, World! How are you?
========================================================================
*/