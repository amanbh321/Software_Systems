/*
============================================================================
Name : 8e.c
Author : Aman Bahuguna
Description : Write a separate program using signal system call to catch the following signals.
              e) SIGALRM (use setitimer system call)
Date: 16th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

void handle_sigalrm(int signum) {
    printf("Received SIGALRM: Alarm has been triggered via setitimer!\n");
    exit(EXIT_SUCCESS);
}

int main() {
    struct itimerval timer;

    // Set up the signal handler for SIGALRM
    if (signal(SIGALRM, handle_sigalrm) == SIG_ERR) {
        perror("Error setting up signal handler");
        exit(EXIT_FAILURE);
    }

    // Configure the timer
    timer.it_value.tv_sec = 2;  // Start the timer with a 2-second delay
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 0; // No recurring timer
    timer.it_interval.tv_usec = 0;

    // Activate the timer
    if (setitimer(ITIMER_REAL, &timer, NULL) == -1) {
        perror("Error setting timer");
        exit(EXIT_FAILURE);
    }

    printf("Waiting for the alarm to trigger...\n");
    pause(); // Suspend the process until a signal is caught

    return 0; // This line won't be executed
}



/*
===========================================================================================
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ gcc 8e.c
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ ./a.out
Waiting for the alarm to trigger...
Received SIGALRM: Alarm has been triggered via setitimer!
============================================================================================
*/