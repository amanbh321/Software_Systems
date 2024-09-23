/*
============================================================================
Name : 32c.c
Author : Aman Bahuguna
Description :  Write a program to implement semaphore to protect any critical section.
               d) remove the created semaphore
Date: 22th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int main() {
    int semaphore_id;
    key_t semaphore_key = ftok(".", 'X'); // Key for the semaphore

    // Create or retrieve the semaphore with 1 semaphore in the set
    semaphore_id = semget(semaphore_key, 1, 0666 | IPC_CREAT);
    if (semaphore_id == -1) {
        perror("Error creating or accessing semaphore");
        return 1;
    }

    printf("Semaphore created/accessed successfully.\n");

    // Remove the semaphore
    if (semctl(semaphore_id, 0, IPC_RMID) == -1) {
        perror("Error removing semaphore");
        return 1;
    }

    printf("Semaphore removed successfully.\n");
    return 0;
}


/*
===========================================================================================
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ gcc 32d.c
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ ./a.out
Semaphore created/accessed successfully.
Semaphore removed successfully.
============================================================================================
*/
