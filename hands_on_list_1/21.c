/*
============================================================================
Name : 21.c
Author : Aman Bahuguna
Description : Write a program, call fork and print the parent and child process id.
Date: 30th Aug, 2024.
============================================================================
*/

#include <sys/types.h> // For data types used in system calls like `fork` and `getpid`
#include <unistd.h>    // For system calls like `fork` and `getpid`
#include <stdio.h>     // For `printf` function

int main()
{
    pid_t parentPid, forkResult;

    // Get and print the parent process ID
    parentPid = getpid();
    printf("Parent process ID: %d\n", parentPid);

    // Create a new child process
    forkResult = fork();

    // If forkResult is not zero, we are in the parent process
    if (forkResult > 0)
    {
        printf("Created child process with ID: %d\n", forkResult);
    }

    return 0;
}


/*
============================================================================
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_1$ gcc 21.c
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_1$ ./a.out
Parent process ID: 10077
Created child process with ID: 10078
============================================================================
*/