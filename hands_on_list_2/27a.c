/*
============================================================================
Name : 27a.c
Author : Aman Bahuguna
Description : Write a program to receive messages from the message queue.
              a) with 0 as a flag
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

    // Prompt user for the message queue key and ID
    printf("Enter the key (hex format, e.g., 0x61051b9f): ");
    scanf("%x", &messageKey);
    printf("Enter the message queue ID: ");
    scanf("%d", &queueId);

    // Check if the provided key and queue ID are valid
    if (msgget(messageKey, 0) != queueId) {
        printf("Error: The key and message queue ID do not correspond.\n");
        return EXIT_FAILURE;
    }

    // Receive a message from the queue with type 0 (any message type)
    if (msgrcv(queueId, &msg, sizeof(msg.text), 0, 0) == -1) {
        perror("Error receiving message");
        return EXIT_FAILURE;
    }

    // Output the received message
    printf("Received Message: %s\n", msg.text);
    return EXIT_SUCCESS;
}

/*
===========================================================================================
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ gcc 27a.c
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ ./a.out
Enter the key (hex format, e.g., 0x61051b9f): 0x410537da
Enter the message queue ID: 1
Received Message: Hello, this is a test message for the message queue!

aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ ipcs -q

------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages    
0xffffffff 0          aman       666        0            0           
0x410537da 1          aman       666        0            0  
============================================================================================
*/
