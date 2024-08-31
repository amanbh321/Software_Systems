/*
============================================================================
Name : 25.c
Author : Aman Bahuguna
Description : Write a program to create three child processes. 
              The parent should wait for a particular child (use waitpid system call).
Date: 30th Aug, 2024.
============================================================================
*/

#include <unistd.h>    // For `fork` system call
#include <sys/types.h> // For process-related data types and `fork`
#include <sys/wait.h>  // For `waitpid` function
#include <stdio.h>     // For `printf` function

int main()
{
    pid_t processA, processB, processC, completedProcess;
    int status;

    // Create the first child process
    processA = fork();

    if (processA == 0)
    {
        // Code executed by the first child process
        printf("First child process (A) created.\n");
        printf("Child A is sleeping for 5 seconds...\n");
        sleep(5);
        printf("Child A has woken up!\n");
        _exit(0); // Terminate the first child process
    }
    else
    {
        // Code executed by the parent process
        processB = fork();

        if (processB == 0)
        {
            // Code executed by the second child process
            printf("Second child process (B) created.\n");
            printf("Child B is sleeping for 10 seconds...\n");
            sleep(10);
            printf("Child B has woken up!\n");
            _exit(0); // Terminate the second child process
        }
        else
        {
            // Code executed by the parent process
            processC = fork();

            if (processC == 0)
            {
                // Code executed by the third child process
                printf("Third child process (C) created.\n");
                printf("Child C is sleeping for 15 seconds...\n");
                sleep(15);
                printf("Child C has woken up!\n");
                _exit(0); // Terminate the third child process
            }
            else
            {
                // Parent process waits for the third child to finish
                completedProcess = waitpid(processC, &status, 0);

                if (completedProcess == processC)
                {
                    if (WIFEXITED(status))
                    {
                        printf("Child C exited with status: %d\n", WEXITSTATUS(status));
                    }
                    else
                    {
                        printf("Child C terminated abnormally.\n");
                    }
                }
            }
        }
    }

    return 0;
}


/*
============================================================================
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_1$ gcc 25.c
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_1$ ./a.out
First child process (A) created.
Child A is sleeping for 5 seconds...
Second child process (B) created.
Child B is sleeping for 10 seconds...
Third child process (C) created.
Child C is sleeping for 15 seconds...
Child A has woken up!
Child B has woken up!
Child C has woken up!
Child C exited with status: 0
============================================================================
*/