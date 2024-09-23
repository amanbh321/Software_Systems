/*
============================================================================
Name : 1c.c
Author : Aman Bahuguna
Description : Write a separate program (for each time domain) to set a interval 
              timer in 10sec and 10micro second
              c) ITIMER_PROF

Date: 15th Sep, 2024.
============================================================================
*/

#include <sys/time.h>  // for setitimer
#include <signal.h>    // for signal handling
#include <unistd.h>    // for _exit and pause
#include <stdio.h>     // for printf and perror

int main(int argc, char *argv[])
{
    struct itimerval timer; // Structure to hold timer values
    int result;             // To store the return value of setitimer

    // Ensure the correct number of arguments is passed
    if (argc != 2)
    {
        printf("Usage: Enter 1 for 10-second timer or 2 for 10-millisecond timer.\n");
        _exit(1);
    }

    // Configure the timer based on input
    if (argv[1][0] == '1')
    {
        // Set the timer for 10 seconds
        timer.it_value.tv_sec = 10;
        timer.it_value.tv_usec = 0;
    }
    else if (argv[1][0] == '2')
    {
        // Set the timer for 10 milliseconds
        timer.it_value.tv_sec = 0;
        timer.it_value.tv_usec = 10000;
    }
    else
    {
        printf("Invalid option! Use 1 for 10s or 2 for 10ms.\n");
        _exit(1);
    }

    // Disable repeating intervals; the timer will fire only once
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 0;

    // Set the profiling timer (measures both user and system CPU time)
    result = setitimer(ITIMER_PROF, &timer, NULL);
    if (result == -1)
    {
        perror("Failed to set timer");
    }

    // Keep the program running indefinitely to allow the timer to trigger
    while (1);

    return 0;
}


/*
===========================================================================================
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ gcc 1c.c
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ ./a.out 1
Profiling timer expired
============================================================================================
*/