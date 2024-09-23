/*
============================================================================
Name : 15.c
Author : Aman Bahuguna
Description : Write a simple program to send some data from parent to the child process.
Date: 18th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int pipefd[2];
    pid_t pid;
    const char *message = "Data from parent";
    char buffer[50];

    pipe(pipefd); // Create a pipe

    pid = fork(); // Create a child process

    if (pid < 0) {
        perror("fork failed");
        return 1; // Handle fork error
    }

    if (pid == 0) { // In child process
        close(pipefd[1]); // Close write end
        read(pipefd[0], buffer, sizeof(buffer)); // Read data from pipe
        printf("Child received: %s\n", buffer); // Print received data
        close(pipefd[0]); // Close read end
    } 
    
    else { // In parent process
        close(pipefd[0]); // Close read end
        write(pipefd[1], message, strlen(message) + 1); // Send data to pipe
        close(pipefd[1]); // Close write end
    }

    return 0;
}

/*
===========================================================================================
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ gcc 15.c
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ ./a.out
Child received: Data from parent
============================================================================================
*/