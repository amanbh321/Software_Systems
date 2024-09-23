/*
============================================================================
Name : 10b.c
Author : Aman Bahuguna
Description : Write a separate program using sigaction system call to catch the following signals.
              b) SIGINT
Date: 17th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handle_sigint(int signum, siginfo_t *info, void *context) {
    printf("Received SIGINT: Interrupt signal caught!\n");
    exit(EXIT_SUCCESS);
}

int main() {
    struct sigaction action;

    // Set up the signal handler
    action.sa_sigaction = handle_sigint;
    action.sa_flags = SA_SIGINFO; // Use sa_sigaction for additional info
    sigemptyset(&action.sa_mask);  // Initialize the signal mask to empty

    // Register the signal handler for SIGINT
    if (sigaction(SIGINT, &action, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    printf("Waiting for SIGINT (press Ctrl+C to send)...\n");
    while (1) {
        pause(); // Suspend the process until a signal is caught
    }

    return 0; // This line won't be reached
}

/*
===========================================================================================
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ gcc 10b.c
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ ./a.out
Waiting for SIGINT (press Ctrl+C to send)...
^CReceived SIGINT: Interrupt signal caught!
============================================================================================
*/