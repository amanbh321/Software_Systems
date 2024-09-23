/*
============================================================================
Name : 4.c
Author : Aman Bahuguna
Description : Write a program to measure how much time is taken to execute 100 getppid ( ) system call. 
              Use time stamp counter.
Date: 15th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <inttypes.h> // Include this for PRIu64 macro

// Function to read the time stamp counter
static inline uint64_t read_tsc() {
    unsigned int low, high;
    __asm__ __volatile__("rdtsc" : "=a"(low), "=d"(high));
    return ((uint64_t)high << 32) | low;
}

int main() {
    uint64_t start_time, end_time;

    // Start the time stamp counter
    start_time = read_tsc();

    // Call getppid() 100 times
    for (int i = 0; i < 100; i++) {
        getppid();
    }

    // End the time stamp counter
    end_time = read_tsc();

    // Use PRIu64 to print uint64_t values
    printf("Time taken (in CPU cycles): %" PRIu64 "\n", (end_time - start_time));

    return 0;
}



/*
===========================================================================================
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ gcc 4.c
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ ./a.out
Time taken (in CPU cycles): 164554
============================================================================================
*/