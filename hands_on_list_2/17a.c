/*
============================================================================
Name : 17a.c
Author : Aman Bahuguna
Description : Write a program to execute ls -l | wc.
              a. use dup
Date: 19th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <unistd.h>

int main() {
    int pipefd[2];
    pipe(pipefd);

    if (fork() == 0) {
        // Child process for 'ls -l'
        close(pipefd[0]); // Close unused read end

        // Redirect stdout to the write end of the pipe
        if (pipefd[1] != STDOUT_FILENO) {
            close(STDOUT_FILENO); // Close original stdout
            dup(pipefd[1]); // Duplicate the pipe's write end to stdout
        }

        close(pipefd[1]); // Close the write end after duplication
        execlp("ls", "ls", "-l", NULL); // Execute 'ls -l'
    } 
    
    else {
        // Parent process for 'wc'
        close(pipefd[1]); // Close unused write end

        // Redirect stdin to the read end of the pipe
        if (pipefd[0] != STDIN_FILENO) {
            close(STDIN_FILENO); // Close original stdin
            dup(pipefd[0]); // Duplicate the pipe's read end to stdin
        }

        close(pipefd[0]); // Close the read end after duplication
        execlp("wc", "wc", NULL); // Execute 'wc'
    }

    return 0;
}

/*
===========================================================================================
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ gcc 17a.c
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ ./a.out
     18     155     803
============================================================================================
*/