/*
============================================================================
Name : 3.c
Author : Aman Bahuguna
Description : Write a program to create a file and print the file descriptor value. 
              Use creat ( ) system call
Date: 25th Aug, 2024.
============================================================================
*/

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    int fd = creat("example.txt", 0644);
    
    if (fd == -1) {
        perror("error while creating file");
        return 1;
    }

    printf("value of file descriptor is: %d \n", fd);

    if (close(fd) == -1) {
        perror("Error while closing file descriptor");
        return 1;
    }

    return 0;
}

/*=============================================================
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_1$ gcc 3.c
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_1$ ./a.out
value of file descriptor is: 3 
================================================================
*/
