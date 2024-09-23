/*
============================================================================
Name : 12.c
Author : Aman Bahuguna
Description : Write a program to create an orphan process. Use kill system call to send 
              SIGKILL signal to the parent process from the child process.
Date: 17th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int main() {
    pid_t pid = fork();

    if (pid > 0) {
        // Parent process
        printf("Parent is running. Waiting for child to send SIGKILL...\n");
        sleep(10); // Parent sleeps
    } else if (pid == 0) {
        // Child process
        printf("Child is sending SIGKILL to parent.\n");
        kill(getppid(), SIGKILL); // Child kills parent
        printf("Child is now an orphan.\n");
        sleep(5); // Child sleeps after orphaning
    } else {
        printf("Fork failed!\n");
    }

    return 0;
}

/*
===========================================================================================
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ gcc 12.c
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ ./a.out
Parent is running. Waiting for child to send SIGKILL...
Child is sending SIGKILL to parent.
Child is now an orphan.
Killed
============================================================================================
*/