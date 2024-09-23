/*
============================================================================
Name : 8d.c
Author : Aman Bahuguna
Description : Write a separate program using signal system call to catch the following signals.
              d) SIGALRM (use alarm system call)
Date: 16th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handle_sigalrm(int signum) {
    printf("Received SIGALRM: The alarm has been triggered!\n");
    exit(EXIT_SUCCESS);
}

int main() {
    // Register the signal handler for SIGALRM
    if (signal(SIGALRM, handle_sigalrm) == SIG_ERR) {
        perror("Failed to set signal handler");
        exit(EXIT_FAILURE);
    }

    // Set an alarm for 2 seconds
    alarm(2);
    printf("Waiting for the alarm to go off...\n");

    // Pause the process until a signal is received
    pause();

    return 0; // This line will not be reached
}



/*
===========================================================================================
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ gcc 8d.c
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ ./a.out
Waiting for the alarm to go off...
Received SIGALRM: The alarm has been triggered!
============================================================================================
*/