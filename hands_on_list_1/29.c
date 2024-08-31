/*
============================================================================
Name : 29.c
Author : Aman Bahuguna
Description : Write a program to get scheduling policy and modify the 
              scheduling policy (SCHED_FIFO, SCHED_RR).
Date: 31th Aug, 2024.
============================================================================
*/

#include <sched.h>    // For scheduling functions like `sched_getscheduler` and `sched_setscheduler`
#include <sys/types.h> // For `getpid`
#include <unistd.h>    // For `getpid`
#include <stdio.h>     // For `printf` and `perror`

int main()
{
    int schedulingPolicy;
    pid_t processId = getpid(); // Retrieve the process ID
    schedulingPolicy = sched_getscheduler(processId); // Get the current scheduling policy
    struct sched_param schedulerParams;

    schedulerParams.sched_priority = 10; // Set a priority level

    // Check and change scheduling policy based on current policy
    switch (schedulingPolicy)
    {
    case SCHED_FIFO:
        printf("Current scheduling policy: FIFO\n");
        sched_setscheduler(processId, SCHED_RR, &schedulerParams); // Change to Round-Robin
        schedulingPolicy = sched_getscheduler(processId); // Retrieve updated policy
        printf("New scheduling policy: %d\n", schedulingPolicy);
        break;
    case SCHED_RR:
        printf("Current scheduling policy: Round-Robin\n");
        sched_setscheduler(processId, SCHED_FIFO, &schedulerParams); // Change to FIFO
        schedulingPolicy = sched_getscheduler(processId); // Retrieve updated policy
        printf("New scheduling policy: %d\n", schedulingPolicy);
        break;
    case SCHED_OTHER:
        printf("Current scheduling policy: Other\n");
        sched_setscheduler(processId, SCHED_RR, &schedulerParams); // Change to Round-Robin
        schedulingPolicy = sched_getscheduler(processId); // Retrieve updated policy
        printf("New scheduling policy: %d\n", schedulingPolicy);
        break;
    default:
        perror("Failed to retrieve or set scheduling policy");
    }

    return 0;
}


/*
============================================================================
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_1$ gcc 29.c
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_1$ ./a.out
Current scheduling policy: Other
New scheduling policy: 0
============================================================================
*/