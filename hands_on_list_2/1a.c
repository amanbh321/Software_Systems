/*
============================================================================
Name : 1a.c
Author : Aman Bahuguna
Description : Write a separate program (for each time domain) to set a interval 
              timer in 10sec and 10micro second
              a) ITIMER_REAL

Date: 15th Sep, 2024.
============================================================================
*/

#include <sys/time.h>  // for setitimer
#include <signal.h>    // for signal handling
#include <unistd.h>    // for pause and _exit
#include <stdio.h>     // for printf and perror

void main(int argc, char *argv[])
{
    struct itimerval timer; // Timer configuration structure
    int result;             // To store the return value of setitimer

    // Ensure the program receives one argument
    if (argc != 2)
    {
        printf("Usage: Pass 1 for a 10s timer, or 2 for a 10ms timer\n");
        _exit(0);
    }

    // Check the argument and set the timer accordingly
    if (argv[1][0] == '1')
    {
        // Configure for a 10-second timer
        timer.it_value.tv_sec = 10;
        timer.it_value.tv_usec = 0;
    }
    else if (argv[1][0] == '2')
    {
        // Configure for a 10-millisecond timer
        timer.it_value.tv_sec = 0;
        timer.it_value.tv_usec = 10000;
    }
    else
    {
        printf("Invalid input. Pass 1 for 10s, or 2 for 10ms timer.\n");
        _exit(0);
    }

    // No repeat intervals; the timer fires only once
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 0;

    // Set the timer and check for errors
    result = setitimer(ITIMER_REAL, &timer, NULL);
    if (result == -1)
    {
        perror("Failed to set the timer");
    }

    // Infinite loop to keep the program running and receiving signals
    while(1);
}

/*
===========================================================================================
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ gcc 1a.c
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ ./a.out 1
Alarm clock
============================================================================================
*/