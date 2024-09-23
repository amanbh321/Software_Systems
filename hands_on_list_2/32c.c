/*
============================================================================
Name : 32c.c
Author : Aman Bahuguna
Description :  Write a program to implement semaphore to protect any critical section.
               c) protect multiple pseudo resources ( may be two) using counting semaphore
Date: 22th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>

// Union for semaphore operations
union semctl_union {
    int value;                     // Value for SETVAL
    struct semid_ds *buf;         // Buffer for IPC_STAT, IPC_SET
    unsigned short *array;         // Array for GETALL, SETALL
};

// Function to perform "P" (wait) operation on the semaphore
void wait_semaphore(int sem_id) {
    struct sembuf operation = {0, -1, 0}; // Decrement semaphore
    if (semop(sem_id, &operation, 1) == -1) {
        perror("Error waiting on semaphore");
    }
}

// Function to perform "V" (signal) operation on the semaphore
void signal_semaphore(int sem_id) {
    struct sembuf operation = {0, 1, 0};  // Increment semaphore
    if (semop(sem_id, &operation, 1) == -1) {
        perror("Error signaling semaphore");
    }
}

int main() {
    int sem_id;
    key_t sem_key = ftok(".", 'R'); // Key for counting semaphore

    // Retrieve or create the counting semaphore
    sem_id = semget(sem_key, 1, 0666 | IPC_CREAT);
    if (sem_id == -1) {
        perror("Failed to create or access semaphore");
        return 1;
    }

    // Initialize the semaphore with a count of 2 (for two resources)
    union semctl_union sem_union;
    sem_union.value = 2; // Set the initial value to 2
    if (semctl(sem_id, 0, SETVAL, sem_union) == -1) {
        perror("Failed to initialize semaphore");
        return 1;
    }

    // Simulate accessing pseudo resources
    for (int i = 0; i < 5; i++) {
        wait_semaphore(sem_id); // Enter critical section
        printf("Accessing pseudo resource: %d\n", i + 1);
        usleep(500000); // Simulate a shorter delay (0.5 seconds)
        signal_semaphore(sem_id); // Exit critical section
    }

    return 0;
}


/*
===========================================================================================
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ gcc 32c.c
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ ./a.out
Accessing pseudo resource: 1
Accessing pseudo resource: 2
Accessing pseudo resource: 3
Accessing pseudo resource: 4
Accessing pseudo resource: 5
============================================================================================
*/
