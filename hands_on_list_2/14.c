/*
============================================================================
Name : 14.c
Author : Aman Bahuguna
Description : Write a simple program to create a pipe, write to the pipe, read from 
              pipe and display on the monitor
Date: 18th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int pipefd[2];
    char buffer[100];
    const char *message = "Hello, Pipe!";

    pipe(pipefd); // Create a pipe

    if (fork() == 0) { // Child process
        close(pipefd[0]); // Close read end
        write(pipefd[1], message, strlen(message) + 1); // Write to pipe
        close(pipefd[1]); // Close write end
    } 
    
    else { // Parent process
        close(pipefd[1]); // Close write end
        read(pipefd[0], buffer, sizeof(buffer)); // Read from pipe
        printf("Message from pipe: %s\n", buffer); // Display message
        close(pipefd[0]); // Close read end
    }

    return 0;
}

/*
===========================================================================================
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ gcc 14.c
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ ./a.out
Message from pipe: Hello, Pipe!
============================================================================================
*/