/*
============================================================================
Name : 31b.c
Author : Aman Bahuguna
Description :  Write a program to create a semaphore and initialize value to the semaphore.
               b) create a counting semaphore 
Date: 22th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int main() {
    int semaphore_id;
    key_t unique_key;

    struct sembuf sem_operation;
    union semun {
        int value;
        struct semid_ds *buffer;
        unsigned short *array;
    } semaphore_union;

    // Generate a unique key for the semaphore
    unique_key = ftok(".", 'B');

    // Create a semaphore set with one counting semaphore
    semaphore_id = semget(unique_key, 1, 0666 | IPC_CREAT);
    if (semaphore_id == -1) {
        perror("Error creating semaphore");
        return 1;
    }

    // Set the semaphore's initial value (e.g., 5 for counting)
    semaphore_union.value = 5; // Modify this value as needed
    if (semctl(semaphore_id, 0, SETVAL, semaphore_union) == -1) {
        perror("Error setting semaphore value");
        return 1;
    }

    printf("Counting semaphore initialized with value 5.\n");
    printf("Semaphore Identifier: %d\n", semaphore_id);

    return 0;
}

/*
===========================================================================================
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ gcc 31b.c
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ ./a.out
Counting semaphore initialized with value 5.
Semaphore Identifier: 1
============================================================================================
*/
