/*
============================================================================
Name : 13_waitSignal.c
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
    printf("Process is waiting for SIGSTOP... (PID: %d)\n", getpid());

    // Infinite loop to keep the program running
    while (1) {
        pause(); // Wait for signals
    }

    return 0; // This line will not be reached
}



/*
===========================================================================================
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ gcc -o wait_signal 13_waitSignal.c
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ gcc -o send_signal 13_sendSignal.c
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ ./wait_signal
Process is waiting for SIGSTOP... (PID: 20315)

[1]+  Stopped                 ./wait_signal
============================================================================================
*/