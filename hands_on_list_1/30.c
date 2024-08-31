/*
============================================================================
Name : 30.c
Author : Aman Bahuguna
Description : Write a program to run a script at a specific time using a Daemon process.
Date: 31th Aug, 2024.
============================================================================
*/

#include <time.h>      // For time manipulation functions
#include <stdio.h>     // For printf
#include <stdlib.h>    // For atoi
#include <sys/types.h> // For fork and setsid
#include <unistd.h>    // For fork, setsid, and chdir
#include <sys/stat.h>  // For umask

// Program to set a deadline based on command-line arguments and wait until it is reached
int main(int argc, char *argv[])
{
    time_t currentTime, deadlineTime; // Current time and target deadline in epoch format
    struct tm *deadlineInfo;          // Structure to hold user-readable deadline

    pid_t childProcess;

    // Ensure at least one argument is provided
    if (argc < 2) {
        printf("Usage: %s hour [minute [second]]\n", argv[0]);
        return 1;
    }

    // Get the current time
    time(&currentTime);
    deadlineInfo = localtime(&currentTime);

    // Set deadline time based on arguments
    deadlineInfo->tm_hour = atoi(argv[1]);
    deadlineInfo->tm_min = (argc > 2) ? atoi(argv[2]) : 0;
    deadlineInfo->tm_sec = (argc > 3) ? atoi(argv[3]) : 0;

    // Convert deadline to epoch time
    deadlineTime = mktime(deadlineInfo);

    // Create a child process
    childProcess = fork();

    if (childProcess == 0) {
        // Code executed by child process
        setsid();        // Create a new session and detach from terminal
        chdir("/");      // Change working directory to root
        umask(0);        // Set file mode creation mask to 0

        // Wait until the deadline
        do {
            time(&currentTime);
        } while (difftime(deadlineTime, currentTime) > 0);

        // Print message when deadline is reached
        printf("Time's up!\n");
        exit(0);
    }

    // Exit the parent process immediately
    return 0;
}

/*
============================================================================
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_1$ gcc 30.c
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_1$ ./a.out 21 48
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_1$ Time's up!
============================================================================
*/