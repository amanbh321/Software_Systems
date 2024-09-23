/*
============================================================================
Name : 17b.c
Author : Aman Bahuguna
Description : Write a program to execute ls -l | wc.
              b) use dup2
Date: 19th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <unistd.h>

int main() {
    int pipefd[2];
    pipe(pipefd); // Create a pipe

    if (fork() == 0) {
        // Child process for executing 'ls -l'
        close(pipefd[0]); // Close the read end
        dup2(pipefd[1], 1); // Redirect stdout to pipe's write end
        close(pipefd[1]); // Close the original write end
        execlp("ls", "ls", "-l", NULL); // Run 'ls -l'
    } 
    
    else {
        // Parent process for executing 'wc'
        close(pipefd[1]); // Close the write end
        dup2(pipefd[0], 0); // Redirect stdin to pipe's read end
        close(pipefd[0]); // Close the original read end
        execlp("wc", "wc", NULL); // Run 'wc'
    }

    return 0;
}

/*
===========================================================================================
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ gcc 17b.c
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ ./a.out
     19     164     851
============================================================================================
*/