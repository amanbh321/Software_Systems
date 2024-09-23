/*
============================================================================
Name : 8a.c
Author : Aman Bahuguna
Description : Write a separate program using signal system call to catch the following signals.
              a) SIGSEGV
Date: 16th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handle_sigsegv(int signum) {
    printf("Received SIGSEGV: Segmentation fault occurred!\n");
    exit(EXIT_FAILURE);
}

int main() {
    // Register the signal handler for SIGSEGV
    if (signal(SIGSEGV, handle_sigsegv) == SIG_ERR) {
        perror("Failed to set signal handler");
        exit(EXIT_FAILURE);
    }

    printf("Triggering SIGSEGV by dereferencing a null pointer...\n");

    // Intentionally cause a segmentation fault
    int *null_ptr = NULL;
    *null_ptr = 42; // This will trigger a segmentation fault

    return 0; // This line won't be executed
}

/*
===========================================================================================
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ gcc 8a.c
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ ./a.out
Triggering SIGSEGV by dereferencing a null pointer...
Received SIGSEGV: Segmentation fault occurred!
============================================================================================
*/