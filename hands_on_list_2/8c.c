/*
============================================================================
Name : 8c.c
Author : Aman Bahuguna
Description : Write a separate program using signal system call to catch the following signals.
              c) SIGFPE
Date: 16th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handle_sigfpe(int signum) {
    printf("Received SIGFPE: Arithmetic error detected!\n");
    exit(EXIT_FAILURE);
}

int main() {
    // Register the signal handler for SIGFPE
    if (signal(SIGFPE, handle_sigfpe) == SIG_ERR) {
        perror("Error setting signal handler");
        exit(EXIT_FAILURE);
    }

    printf("Triggering SIGFPE (division by zero)...\n");
    
    // Inducing SIGFPE by dividing by zero
    int numerator = 1;
    int denominator = 0;
    int result = numerator / denominator; // This line will cause SIGFPE

    return 0; // This line will not be executed
}



/*
===========================================================================================
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ gcc 8c.c
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ ./a.out
Triggering SIGFPE (division by zero)...
Received SIGFPE: Arithmetic error detected!
============================================================================================
*/