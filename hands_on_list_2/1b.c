/*
============================================================================
Name : 1b.c
Author : Aman Bahuguna
Description : Write a separate program (for each time domain) to set a interval 
              timer in 10sec and 10micro second
              b. ITIMER_VIRTUAL

Date: 15th Sep, 2024.
============================================================================
*/

#include <sys/time.h>  // for setitimer
#include <signal.h>    // for signal handling
#include <unistd.h>    // for _exit and pause
#include <stdio.h>     // for printf and perror

int main(int argc, char *argv[])
{
    struct itimerval timer; // Timer structure
    int result;             // Stores the return value of setitimer

    // Check if the correct number of arguments is provided
    if (argc != 2)
    {
        printf("Usage: Enter 1 for 10-second timer or 2 for 10-millisecond timer.\n");
        _exit(1);
    }

    // Set the timer values based on input
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
        printf("Invalid input! Use 1 for 10s or 2 for 10ms.\n");
        _exit(1);
    }

    // No repeat intervals; timer will fire once
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 0;

    // Set the virtual timer (counts CPU time used by the process)
    result = setitimer(ITIMER_VIRTUAL, &timer, NULL);
    if (result == -1)
    {
        perror("Error in setting the timer");
    }

    // Keep the program running indefinitely
    while (1);

    return 0;
}


/*
===========================================================================================
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ gcc 1b.c
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ ./a.out 2
Virtual timer expired
============================================================================================
*/