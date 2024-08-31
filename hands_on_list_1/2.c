/*
============================================================================
Name : 2.c
Author : Aman Bahuguna
Description : Write a simple program to execute in an infinite loop at the background. 
              Go to /proc directory and identify all the process related information 
              in the corresponding proc directory
Date: 25th Aug, 2024.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid;

    // Fork the process to create a child that will run in the background
    pid = fork();

    if (pid < 0) {
        // Fork failed
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        // Parent process exits, allowing child to run in the background
        printf("Parent process exiting, child PID: %d\n", pid);
        exit(EXIT_SUCCESS);
    }

    // Child process continues
    printf("Child process running in the background, PID: %d\n", getpid());

    // Infinite loop to keep the process running
    while (1) {
        char path[256];
        FILE *file;
        char buffer[256];

        // Build the path to the /proc/<pid>/status file
        snprintf(path, sizeof(path), "/proc/%d/status", getpid());

        // Open the status file
        file = fopen(path, "r");
        if (file == NULL) {
            perror("Failed to open /proc/<pid>/status");
            exit(EXIT_FAILURE);
        }

        // Print the contents of the status file
        printf("Process information:\n");
        while (fgets(buffer, sizeof(buffer), file) != NULL) {
            printf("%s", buffer);
        }
        fclose(file);

        // Sleep for a few seconds before repeating
        sleep(5);
    }

    return 0;
}

/*
Compile using gcc 2.c

To run use ./a.out & 
& at the end ensures that the program to run in background

To kill the background process, use the command: 
pkill a.out

*/
