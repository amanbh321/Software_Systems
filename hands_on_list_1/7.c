/*
============================================================================
Name : 7.c
Author : Aman Bahuguna
Description : Write a program to copy file1 into file2 ($cp file1 file2)
Date: 26th Aug, 2024.
============================================================================
*/

#include <fcntl.h>     // For open()
#include <unistd.h>    // For read(), write(), and close()
#include <stdio.h>     // For perror() and printf()

#define BUFFER_SIZE 1024 // Define a buffer size for reading data

int main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source_file> <destination_file>\n", argv[0]);
        return 1;
    }

    const char *sourceFile = argv[1];
    const char *destFile = argv[2];

    int srcFD = open(sourceFile, O_RDONLY);
    int destFD = open(destFile, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);

    if (srcFD == -1 || destFD == -1) {
        perror("Error opening file");
        return 1;
    }

    char buffer[BUFFER_SIZE];
    ssize_t bytesRead, bytesWritten;

    while ((bytesRead = read(srcFD, buffer, BUFFER_SIZE)) > 0) {
        bytesWritten = write(destFD, buffer, bytesRead);
        if (bytesWritten == -1) {
            perror("Error writing to file");
            close(srcFD);
            close(destFD);
            return 1;
        }
    }

    if (bytesRead == -1) {
        perror("Error reading from file");
    } else {
        printf("File copied successfully!\n");
    }

    close(srcFD);
    close(destFD);
    return 0;
}

/*
========================================================================================
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_1$ gcc 7.c
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_1$ ./a.out file1.txt file2.txt
File copied successfully!
==========================================================================================
*/
