/*
============================================================================
Name : 23.c
Author : Aman Bahuguna
Description : Write a program to print the maximum number of files can be opened within a process 
              and size of a pipe (circular buffer).
Date: 20th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <fcntl.h>

int main() {
    long maxFiles = sysconf(_SC_OPEN_MAX); // Get the max number of open files
    long pipeSize = fpathconf(STDIN_FILENO, _PC_PIPE_BUF); // Get the pipe buffer size

    printf("Max number of files that can be opened: %ld\n", maxFiles);
    printf("Size of the pipe buffer: %ld bytes\n", pipeSize);
    
    return 0;
}

/*
===========================================================================================
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ gcc 23.c
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ ./a.out
Max number of files that can be opened: 1048576
Size of the pipe buffer: 4096 bytes
============================================================================================
*/