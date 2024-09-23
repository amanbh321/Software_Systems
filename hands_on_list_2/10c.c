/*
============================================================================
Name : 10b.c
Author : Aman Bahuguna
Description : Write a separate program using sigaction system call to catch the following signals.
              c) SIGFPE
Date: 17th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handle_sigfpe(int signum, siginfo_t *info, void *context) {
    printf("Caught SIGFPE: Division by zero or arithmetic error!\n");
    exit(EXIT_FAILURE);
}

int main() {
    struct sigaction action;

    // Set up the signal handler for SIGFPE
    action.sa_sigaction = handle_sigfpe;
    action.sa_flags = SA_SIGINFO; // Enable additional info for the handler
    sigemptyset(&action.sa_mask);  // Initialize the signal mask

    // Register the signal handler
    if (sigaction(SIGFPE, &action, NULL) == -1) {
        perror("sigaction failed");
        exit(EXIT_FAILURE);
    }

    printf("Generating SIGFPE (division by zero)...\n");

    // Trigger SIGFPE (division by zero)
    int numerator = 1;
    int denominator = 0;
    int result = numerator / denominator; // This will cause SIGFPE

    return 0; // This line won't be reached
}

/*
===========================================================================================
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ gcc 10c.c
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ ./a.out
Generating SIGFPE (division by zero)...
Caught SIGFPE: Division by zero or arithmetic error!
============================================================================================
*/