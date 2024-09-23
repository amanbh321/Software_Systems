/*
============================================================================
Name : 11.c
Author : Aman Bahuguna
Description : Write a program to ignore a SIGINT signal then reset the default action of 
              the SIGINT signal - use sigaction system call.
Date: 17th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main() {
    struct sigaction act;

    // Ignore SIGINT (Ctrl+C)
    act.sa_handler = SIG_IGN;
    sigaction(SIGINT, &act, NULL);
    printf("SIGINT is ignored for 5 seconds. Press Ctrl+C...\n");
    sleep(5);

    // Reset SIGINT to default action
    act.sa_handler = SIG_DFL;
    sigaction(SIGINT, &act, NULL);
    printf("SIGINT is now reset to default. Press Ctrl+C again...\n");
    sleep(5);

    return 0;
}

/*
===========================================================================================
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ gcc 11.c
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ ./a.out
SIGINT is ignored for 5 seconds. Press Ctrl+C...
^C
SIGINT is now reset to default. Press Ctrl+C again...
^C
============================================================================================
*/