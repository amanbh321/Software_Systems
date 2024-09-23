/*
============================================================================
Name : 13_sendSignal.c
Author : Aman Bahuguna
Description : Write two programs: first program is waiting to catch SIGSTOP signal, the second program
              will send the signal (using kill system call). Find out whether the first program is able to catch
              the signal or not.
Date: 17th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main(void) {
    pid_t target_pid;

    printf("Enter the PID of the process to send SIGSTOP to: ");
    scanf("%d", &target_pid);

    // Send SIGSTOP to the target process
    if (kill(target_pid, SIGSTOP) == -1) {
        perror("Failed to send SIGSTOP");
        exit(EXIT_FAILURE);
    }

    printf("SIGSTOP sent to process %d.\n", target_pid);
    return 0;
}



/*
===========================================================================================
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ ./send_signal
Enter the PID of the process to send SIGSTOP to: 20315
SIGSTOP sent to process 20315.
============================================================================================
*/