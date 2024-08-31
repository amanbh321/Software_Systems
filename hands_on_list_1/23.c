/*
============================================================================
Name : 23.c
Author : Aman Bahuguna
Description : Write a program to create a Zombie state of the running program.
Date: 30th Aug, 2024.
============================================================================
*/

#include <sys/types.h> // For data types used with `fork`
#include <unistd.h>    // For `fork`, `getpid`, `sleep`, and `_exit`
#include <stdio.h>     // For `printf`

int main()
{
    pid_t pid;

    // Create a new process
    pid = fork();

    if (pid > 0)
    {
        // Code executed by the parent process
        printf("Parent Process ID: %d\n", getpid());
        printf("Parent going to sleep for 10 seconds...\n");
        sleep(10); // Parent process sleeps for 10 seconds
        printf("Parent has woken up!\n");
    }
    else if (pid == 0)
    {
        // Code executed by the child process
        printf("Child Process ID: %d\n", getpid());
        printf("Child process exiting...\n");
        _exit(0); // Child process exits immediately
    }
    else
    {
        // Fork failed
        printf("Fork failed to create a new process.\n");
    }

    return 0;
}


/*
============================================================================
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_1$ gcc 23.c
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_1$ ./a.out
Parent Process ID: 10624
Parent going to sleep for 10 seconds...
Child Process ID: 10625
Child process exiting...
Parent has woken up!
============================================================================
*/