/*
============================================================================
Name : 3.c
Author : Aman Bahuguna
Description : Write a program to set (any one) system resource limit. Use setrlimit system call.
Date: 15th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <sys/resource.h>
#include <stdlib.h>

int main() {
    struct rlimit new_limit;

    // Set new soft and hard limits
    new_limit.rlim_cur = 1024;  // Soft limit for file descriptors
    new_limit.rlim_max = 2048;  // Hard limit for file descriptors

    // Apply the new limits
    if (setrlimit(RLIMIT_NOFILE, &new_limit) == 0) {
        printf("Limits updated: Soft limit = %ld, Hard limit = %ld\n", (long)new_limit.rlim_cur, (long)new_limit.rlim_max);
    } else {
        perror("Failed to set limit");
        return EXIT_FAILURE;
    }

    return 0;
}


/*
===========================================================================================
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ gcc 3.c
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ ./a.out
Limits updated: Soft limit = 1024, Hard limit = 2048
============================================================================================
*/