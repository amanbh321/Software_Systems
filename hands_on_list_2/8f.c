/*
============================================================================
Name : 8f.c
Author : Aman Bahuguna
Description : Write a separate program using signal system call to catch the following signals.
              f) SIGVTALRM (use setitimer system call)
Date: 16th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

void handle_sigvtalrm(int signum) {
    printf("Received SIGVTALRM: Virtual timer alarm triggered!\n");
    exit(EXIT_SUCCESS);
}

int main() {
    struct itimerval timer;

    // Set up the signal handler for SIGVTALRM
    struct sigaction sa;
    sa.sa_handler = handle_sigvtalrm;
    sa.sa_flags = 0; // No special flags
    sigemptyset(&sa.sa_mask); // No additional signals to block
    
    if (sigaction(SIGVTALRM, &sa, NULL) == -1) {
        perror("Failed to set signal handler");
        exit(EXIT_FAILURE);
    }

    // Configure the virtual timer
    timer.it_value.tv_sec = 2;  // Start the timer with a 2-second delay
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 0; // No recurring timer
    timer.it_interval.tv_usec = 0;

    // Activate the timer
    if (setitimer(ITIMER_VIRTUAL, &timer, NULL) == -1) {
        perror("Error setting virtual timer");
        exit(EXIT_FAILURE);
    }

    printf("Waiting for virtual timer alarm...\n");
    
    // Wait indefinitely for the signal to be caught
    while (1) {
        pause(); // Suspend the process until a signal is received
    }

    return 0; // This line will not be executed
}




/*
===========================================================================================
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ gcc 8f.c
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ ./a.out
Waiting for virtual timer alarm...
============================================================================================
*/