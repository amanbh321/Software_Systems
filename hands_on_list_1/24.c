/*
============================================================================
Name : 24.c
Author : Aman Bahuguna
Description : Write a program to create an orphan process
Date: 30th Aug, 2024.
============================================================================
*/

#include <sys/types.h> // For process-related system calls like `fork`
#include <unistd.h>    // For system calls like `fork`, `getpid`, and `sleep`
#include <stdio.h>     // For `printf`

int main()
{
    pid_t processId;

    // Create a new process
    processId = fork();

    if (processId > 0)
    {
        // This block is executed by the parent process
        printf("Parent Process ID: %d\n", getpid());
        printf("Parent will sleep for 10 seconds...\n");
        sleep(10); // Parent process sleeps for 10 seconds
        printf("Parent process terminating...\n");
        _exit(0); // Immediately terminate the parent process
        // Note: The parent process terminates while the child is still sleeping
    }
    else if (processId == 0)
    {
        // This block is executed by the child process
        printf("Child Process ID: %d\n", getpid());
        printf("Child will sleep for 20 seconds...\n");
        sleep(20); // Child process sleeps for 20 seconds
        printf("Child process has woken up!\n");
    }
    else
    {
        // Handle fork failure
        fprintf(stderr, "Failed to create a new process.\n");
        return 1;
    }

    return 0;
}


/*
============================================================================
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_1$ gcc 24.c
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_1$ ./a.out
Parent Process ID: 10988
Parent will sleep for 10 seconds...
Child Process ID: 10989
Child will sleep for 20 seconds...
Parent process terminating...
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_1$ Child process has woken up!
============================================================================
*/