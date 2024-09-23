/*
============================================================================
Name : 8g.c
Author : Aman Bahuguna
Description : Write a separate program using signal system call to catch the following signals.
              g) SIGPROF (use setitimer system call)
Date: 16th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

void handle_sigprof(int signum) {
    printf("Received SIGPROF: Profiling timer alarm activated!\n");
    exit(EXIT_SUCCESS);
}

int main() {
    struct itimerval timer;

    // Set up the signal handler for SIGPROF
    struct sigaction sa;
    sa.sa_handler = handle_sigprof;
    sa.sa_flags = 0; // No special flags
    sigemptyset(&sa.sa_mask); // No additional signals to block
    if (sigaction(SIGPROF, &sa, NULL) == -1) {
        perror("Error setting up signal handler");
        exit(EXIT_FAILURE);
    }

    // Configure the profiling timer
    timer.it_value.tv_sec = 2;  // Start after 2 seconds
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 0; // No recurring timer
    timer.it_interval.tv_usec = 0;

    // Activate the profiling timer
    if (setitimer(ITIMER_PROF, &timer, NULL) == -1) {
        perror("Failed to set profiling timer");
        exit(EXIT_FAILURE);
    }

    printf("Awaiting profiling timer alarm...\n");
    
    // Infinite loop to wait for the signal
    while (1) {
        pause(); // Suspend the process until a signal is received
    }

    return 0; // This line will not be reached
}


/*
===========================================================================================
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ gcc 8g.c
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ ./a.out
Awaiting profiling timer alarm...
============================================================================================
*/