/*
============================================================================
Name : 8b.c
Author : Aman Bahuguna
Description : Write a separate program using signal system call to catch the following signals.
              b) SIGINT
Date: 16th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handle_sigint(int signum) {
    printf("Received SIGINT: Interrupt signal caught!\n");
    exit(EXIT_SUCCESS);
}

int main() {
    // Register the signal handler for SIGINT
    if (signal(SIGINT, handle_sigint) == SIG_ERR) {
        perror("Failed to set signal handler");
        exit(EXIT_FAILURE);
    }

    printf("Press Ctrl+C to trigger SIGINT...\n");
    
    // Infinite loop to keep the program running
    while (1) {
        pause(); // Suspend the process until a signal is caught
    }

    return 0; // This line will not be reached
}

/*
===========================================================================================
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ gcc 8b.c
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ ./a.out
Press Ctrl+C to trigger SIGINT...
^CReceived SIGINT: Interrupt signal caught!
============================================================================================
*/