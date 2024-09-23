/*
============================================================================
Name : 25.c
Author : Aman Bahuguna
Description : Write a program to print a message queue's (use msqid_ds and ipc_perm structures)
                a. access permission
                b. uid, gid
                c. time of last message sent and received
                d. time of last change in the message queue
                d. size of the queue
                f. number of messages in the queue
                g. maximum number of bytes allowed
                h. pid of the msgsnd and msgrcv
Date: 20th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>

int main() {
    // Generate a unique key for the message queue
    key_t msgKey = ftok("key.txt", 65);
    // Create or access the message queue
    int queueId = msgget(msgKey, 0666 | IPC_CREAT);

    struct msqid_ds queueInfo;
    // Retrieve information about the message queue
    msgctl(queueId, IPC_STAT, &queueInfo);

    // Display access permissions
    printf("Access Permissions: %o\n", queueInfo.msg_perm.mode);
    
    // Display user and group IDs
    printf("User ID: %d, Group ID: %d\n", queueInfo.msg_perm.uid, queueInfo.msg_perm.gid);
    
    // Display times of last messages sent and received
    printf("Last Message Sent: %s", ctime(&queueInfo.msg_stime));
    printf("Last Message Received: %s", ctime(&queueInfo.msg_rtime));
    printf("Last Change Time: %s", ctime(&queueInfo.msg_ctime));
    
    // Display queue statistics
    printf("Size of Queue: %lu bytes\n", queueInfo.__msg_cbytes);
    printf("Number of Messages in Queue: %lu\n", queueInfo.msg_qnum);
    printf("Maximum Bytes Allowed: %lu\n", queueInfo.msg_qbytes);
    
    // Display PIDs of last message send and receive operations
    printf("PID of Last Msgsnd: %d\n", queueInfo.msg_lspid);
    printf("PID of Last Msgrcv: %d\n", queueInfo.msg_lrpid);

    return 0;
}

/*
===========================================================================================
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ gcc 25.c
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ ./a.out
Access Permissions: 666
User ID: 1000, Group ID: 1000
Last Message Sent: Thu Jan  1 05:30:00 1970
Last Message Received: Thu Jan  1 05:30:00 1970
Last Change Time: Sat Sep 21 19:22:45 2024
Size of Queue: 0 bytes
Number of Messages in Queue: 0
Maximum Bytes Allowed: 16384
PID of Last Msgsnd: 0
PID of Last Msgrcv: 0
============================================================================================
*/
