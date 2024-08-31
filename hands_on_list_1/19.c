/*
============================================================================
Name : 19.c
Author : Aman Bahuguna
Description : Write a program to find out time taken to execute getpid system call. 
              Use time stamp counter.
Date: 29th Aug, 2024.
============================================================================
*/

#include <sys/time.h>  // For `gettimeofday` function
#include <sys/types.h> // For data types used in system calls
#include <unistd.h>    // For `getpid` function
#include <stdio.h>     // For `printf`

// Include for __rdtsc() based on compiler
#ifdef _MSC_VER
#include <intrin.h>
#else
#include <x86intrin.h>
#endif

int main()
{
    unsigned long long startCycle, endCycle;
    int processID;
    struct timeval timeInfo;

    // Record the start cycle count
    startCycle = __rdtsc();
    
    // Get the process ID
    processID = getpid();

    // Record the end cycle count
    endCycle = __rdtsc();

    // Print the process ID
    printf("Process ID: %d\n", processID);
    
    // Print the number of CPU cycles taken
    printf("CPU Cycles: %llu\n", endCycle - startCycle);

    return 0;
}

/*
============================================================================
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_1$ ./a.out
Process ID: 9442
CPU Cycles: 29276
============================================================================
*/