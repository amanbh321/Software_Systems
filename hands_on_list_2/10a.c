/*
============================================================================
Name : 10a.c
Author : Aman Bahuguna
Description : Write a separate program using sigaction system call to catch the following signals.
              a) SIGSEGV
Date: 17th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handle_sigsegv(int signum, siginfo_t *info, void *context) {
    printf("Signal caught: SIGSEGV (Segmentation Fault)\n");
    printf("Faulting address: %p\n", info->si_addr);
    exit(EXIT_FAILURE);
}

int main() {
    struct sigaction action;

    // Set up the signal handler
    action.sa_sigaction = handle_sigsegv;
    action.sa_flags = SA_SIGINFO; // Use sa_sigaction for additional info
    sigemptyset(&action.sa_mask);  // Initialize the signal set to empty

    // Register the signal handler for SIGSEGV
    if (sigaction(SIGSEGV, &action, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    printf("Signal handler installed. Triggering SIGSEGV...\n");

    // Trigger SIGSEGV by dereferencing a null pointer
    int *null_pointer = NULL;
    printf("Attempting to dereference a null pointer...\n");
    *null_pointer = 0; // This will generate a segmentation fault

    return 0; // This line won't be reached
}

/*
===========================================================================================
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ gcc 10a.c
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ ./a.out
Signal handler installed. Triggering SIGSEGV...
Attempting to dereference a null pointer...
Signal caught: SIGSEGV (Segmentation Fault)
Faulting address: (nil)
============================================================================================
*/