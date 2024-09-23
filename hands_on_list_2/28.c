/*
============================================================================
Name : 28.c
Author : Aman Bahuguna
Description : Write a program to change the exiting message queue permission. (use msqid_ds structure
Date: 21th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main() {
    key_t key;
    int msgid;
    struct msqid_ds queue_info;

    // Prompt user to enter a key
    printf("Enter the message queue key (integer): ");
    scanf("%d", &key);

    // Access the message queue with the provided key
    msgid = msgget(key, 0);
    if (msgid == -1) {
        perror("Failed to access the message queue");
        exit(EXIT_FAILURE);
    }

    // Retrieve current message queue permissions
    if (msgctl(msgid, IPC_STAT, &queue_info) == -1) {
        perror("Error getting message queue info");
        exit(EXIT_FAILURE);
    }
    printf("Current permissions: %o\n", queue_info.msg_perm.mode);

    // Modify the permissions (e.g., owner/group can read and write)
    queue_info.msg_perm.mode = 0660;

    // Apply the new permissions
    if (msgctl(msgid, IPC_SET, &queue_info) == -1) {
        perror("Error setting new message queue permissions");
        exit(EXIT_FAILURE);
    }

    // Confirm the changes
    if (msgctl(msgid, IPC_STAT, &queue_info) == -1) {
        perror("Error verifying updated message queue permissions");
        exit(EXIT_FAILURE);
    }
    printf("Updated permissions: %o\n", queue_info.msg_perm.mode);

    return 0;
}

/*
===========================================================================================
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ gcc 28.c
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ ./a.out
Enter the message queue key (integer): 0x410537da
Error getting message queue info: Permission denied
============================================================================================
*/
