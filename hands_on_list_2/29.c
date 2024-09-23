/*
============================================================================
Name : 29.c
Author : Aman Bahuguna
Description :  Write a program to remove the message queue.
Date: 21th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>

int main() {
    // Generate a unique key for the message queue
    key_t key = ftok("queuefile", 'A');
    if (key == -1) {
        perror("Error generating key");
        exit(EXIT_FAILURE);
    }

    // Get the message queue ID using the generated key
    int msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("Error accessing message queue");
        exit(EXIT_FAILURE);
    }

    // Remove the message queue
    if (msgctl(msgid, IPC_RMID, NULL) == -1) {
        perror("Error removing message queue");
        exit(EXIT_FAILURE);
    }

    printf("Message queue has been successfully removed.\n");

    return 0;
}

/*
===========================================================================================
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ gcc 29.c
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ ./a.out
Message queue has been successfully removed.
============================================================================================
*/
