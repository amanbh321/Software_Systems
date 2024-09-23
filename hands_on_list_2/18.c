/*
============================================================================
Name : 18.c
Author : Aman Bahuguna
Description : Write a program to find out total number of directories on the pwd.
              execute ls -l | grep ^d | wc ? Use only dup2.
Date: 19th Sep, 2024.
============================================================================
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int fd_ls[2], fd_grep[2];

    // Create pipes
    if (pipe(fd_ls) == -1 || pipe(fd_grep) == -1) {
        perror("pipe failed");
        exit(EXIT_FAILURE);
    }

    if (fork() == 0) { // First child process for "ls -l"
        dup2(fd_ls[1], STDOUT_FILENO); // Redirect stdout to fd_ls[1]
        close(fd_ls[0]); // Close unused read end of fd_ls
        close(fd_grep[0]); // Close both ends of fd_grep
        close(fd_grep[1]);
        execlp("ls", "ls", "-l", (char *)NULL);
        perror("execlp ls failed");
        exit(EXIT_FAILURE);
    }

    if (fork() == 0) { // Second child process for "grep ^d"
        dup2(fd_ls[0], STDIN_FILENO);  // Redirect stdin to fd_ls[0]
        dup2(fd_grep[1], STDOUT_FILENO); // Redirect stdout to fd_grep[1]
        close(fd_ls[1]); // Close write end of fd_ls
        close(fd_grep[0]); // Close read end of fd_grep
        execlp("grep", "grep", "^d", (char *)NULL);
        perror("execlp grep failed");
        exit(EXIT_FAILURE);
    }

    // Parent process for "wc -l"
    dup2(fd_grep[0], STDIN_FILENO); // Redirect stdin to fd_grep[0]
    close(fd_ls[0]); // Close unused ends
    close(fd_ls[1]);
    close(fd_grep[1]); // Close write end of fd_grep

    // Wait for children to finish
    int status;
    while (wait(&status) > 0);

    // Execute wc to count the directories
    execlp("wc", "wc", "-l", (char *)NULL);
    perror("execlp wc failed");
    exit(EXIT_FAILURE);
}



/*
===========================================================================================
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ gcc 18.c
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ ./a.out
3
============================================================================================
*/