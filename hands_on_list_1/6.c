/*
============================================================================
Name : 6.c
Author : Aman Bahuguna
Description : Write a program to take input from STDIN and display on STDOUT. 
              Use only read/write system calls
Date: 25th Aug, 2024.
============================================================================
*/

#include <unistd.h>    // For read() and write()
#include <stdio.h>     // For perror()

#define BUFFER_SIZE 100  // Define a buffer size of 1 byte

int main()
{
    char buffer[BUFFER_SIZE];
    ssize_t bytesRead, bytesWritten;

    while (1) {
        bytesRead = read(STDIN_FILENO, buffer, 1);
        if (bytesRead == -1) {
            perror("Read error");
            break;
        }

        bytesWritten = write(STDOUT_FILENO, buffer, 1);
        if (bytesWritten == -1) {
            perror("Write error");
            break;
        }
    }

    return 0;
}
