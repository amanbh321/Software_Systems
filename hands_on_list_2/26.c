/*
============================================================================
Name : 26.c
Author : Aman Bahuguna
Description : Write a program to send messages to the message queue. Check $ipcs -q
Date: 20th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

struct message {
    long type;
    char text[100];
};

int main() {
    // Create a unique key for the message queue
    key_t key = ftok("key.txt", 65);
    // Create or access the message queue
    int queueId = msgget(key, 0666 | IPC_CREAT);

    struct message msg;
    msg.type = 1; // Set message type

    // Prompt the user for a message
    printf("Enter your message: ");
    fgets(msg.text, sizeof(msg.text), stdin); // Use sizeof to prevent overflow

    // Send the message to the queue
    msgsnd(queueId, &msg, strlen(msg.text) + 1, 0); // +1 to include the null terminator

    printf("Message has been sent to the queue.\n");

    return 0;
}

/*
===========================================================================================
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ gcc 26.c
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ ./a.out
Enter your message: Hello, this is a test message for the message queue!
Message has been sent to the queue.
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ ipcs -q

------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages    
0xffffffff 0          aman       666        0            0           
0x410537da 1          aman       666        67           3    
============================================================================================
*/
