/*
============================================================================
Name : 31a.c
Author : Aman Bahuguna
Description :  Write a program to create a semaphore and initialize value to the semaphore.
               a) create a binary semaphore 
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

    // Create a unique key for the semaphore
    unique_key = ftok(".", 'A');
    
    // Request a semaphore set containing one semaphore
    semaphore_id = semget(unique_key, 1, 0666 | IPC_CREAT);
    if (semaphore_id == -1) {
        perror("Failed to create semaphore");
        return 1;
    }

    // Set the semaphore's initial value to 1 (binary semaphore)
    semaphore_union.value = 1;
    if (semctl(semaphore_id, 0, SETVAL, semaphore_union) == -1) {
        perror("Failed to set semaphore value");
        return 1;
    }

    printf("Binary semaphore successfully created and initialized to 1.\n");
    printf("Semaphore Identifier: %d\n", semaphore_id);

    return 0;
}

/*
===========================================================================================
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ gcc 31a.c
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ ./a.out
Binary semaphore successfully created and initialized to 1.
Semaphore Identifier: 0
============================================================================================
*/
