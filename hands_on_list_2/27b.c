/*
============================================================================
Name : 27b.c
Author : Aman Bahuguna
Description : Write a program to receive messages from the message queue.
              b) with IPC_NOWAIT as a flag
Date: 20th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>

struct message {
    long type;
    char text[80];
};

int main() {
    key_t messageKey;
    int queueId;
    struct message msg;

    // Prompt the user to input the key and message queue ID
    printf("Enter the message queue key (in hex, e.g., 0x61051b9f): ");
    scanf("%x", &messageKey);
    printf("Enter the message queue ID: ");
    scanf("%d", &queueId);

    // Verify if the provided key corresponds to the message queue ID
    if (msgget(messageKey, 0) != queueId) {
        printf("Error: The specified key and message queue ID do not match.\n");
        return EXIT_FAILURE;
    }

    // Attempt to receive a message from the queue without blocking
    if (msgrcv(queueId, &msg, sizeof(msg.text), 0, IPC_NOWAIT) == -1) {
        perror("Error receiving message");
        return EXIT_FAILURE;
    }

    // Output the received message
    printf("Received Message: %s\n", msg.text);
    return EXIT_SUCCESS;
}

/*
===========================================================================================
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ gcc 27b.c
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ ./a.out
Enter the message queue key (in hex, e.g., 0x61051b9f): 0x410537da
Enter the message queue ID: 1
Received Message: Hello from the message queue!
============================================================================================
*/
