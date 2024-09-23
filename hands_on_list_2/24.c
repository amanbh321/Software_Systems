/*
============================================================================
Name : 24.c
Author : Aman Bahuguna
Description : Write a program to print the maximum number of files can be opened within a process 
              and size of a pipe (circular buffer).
Date: 20th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main() {
    // Generate a unique key for the message queue
    key_t msgKey = ftok("key.txt", 65);
    
    // Create the message queue and retrieve its ID
    int queueId = msgget(msgKey, 0666 | IPC_CREAT);
    
    // Output the key and message queue ID
    printf("Generated Key: %d\n", msgKey);
    printf("Message Queue Identifier: %d\n", queueId);
    
    return 0;
}

/*
===========================================================================================
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ gcc 24.c
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ ./a.out
Generated Key: 1090861018
Message Queue Identifier: 1
============================================================================================
*/
