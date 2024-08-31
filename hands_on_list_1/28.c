/*
============================================================================
Name : 28.c
Author : Aman Bahuguna
Description : Write a program to get maximum and minimum real time priority.
Date: 31th Aug, 2024.
============================================================================
*/

#include <sched.h> // For scheduling functions
#include <stdio.h> // For input/output functions

int main()
{
    int highestPriority, lowestPriority;

    // Retrieve the maximum priority for Round-Robin scheduling
    highestPriority = sched_get_priority_max(SCHED_RR);
    if (highestPriority == -1)
    {
        perror("Failed to get maximum priority");
    }
    else
    {
        printf("Maximum priority for Round-Robin scheduling: %d\n", highestPriority);
    }

    // Retrieve the minimum priority for Round-Robin scheduling
    lowestPriority = sched_get_priority_min(SCHED_RR);
    if (lowestPriority == -1)
    {
        perror("Failed to get minimum priority");
    }
    else
    {
        printf("Minimum priority for Round-Robin scheduling: %d\n", lowestPriority);
    }

    return 0;
}


/*
============================================================================
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_1$ gcc 28.c
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_1$ ./a.out
Maximum priority for Round-Robin scheduling: 99
Minimum priority for Round-Robin scheduling: 1
============================================================================
*/