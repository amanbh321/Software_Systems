/*
============================================================================
Name : 9.c
Author : Aman Bahuguna
Description : Write a program to ignore a SIGINT signal then reset the default action of the SIGINT
              signal - Use signal system call.
Date: 16th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void ignore_signal(int signum) {
    printf("SIGINT signal is ignored. Press Ctrl+C...\n");
}

int main() {
    // Ignore SIGINT signal
    signal(SIGINT, SIG_IGN);
    printf("SIGINT signal is ignored for 5 seconds. Try pressing Ctrl+C...\n");
    sleep(5);

    // Reset SIGINT to default behavior
    signal(SIGINT, SIG_DFL);
    printf("SIGINT signal reset to default. Try pressing Ctrl+C again...\n");
    sleep(5);

    return 0;
}



/*
===========================================================================================
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ gcc 9.c
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ ./a.out
SIGINT signal is ignored for 5 seconds. Try pressing Ctrl+C...
SIGINT signal reset to default. Try pressing Ctrl+C again...
^C
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ ^C
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ ./a.out
SIGINT signal is ignored for 5 seconds. Try pressing Ctrl+C...
SIGINT signal reset to default. Try pressing Ctrl+C again...
============================================================================================
*/