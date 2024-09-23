/*
============================================================================
Name : 32b.c
Author : Aman Bahuguna
Description :  Write a program to implement semaphore to protect any critical section.
               b) protect shared memory from concurrent write access
Date: 22th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>
#include <string.h>

// Semaphore union for control operations
union semaphore_union {
    int value;
    struct semid_ds *buffer;
    unsigned short *array;
};

// Function to perform "P" (wait) operation on semaphore
void wait_semaphore(int sem_id) {
    struct sembuf semaphore_operation = {0, -1, 0};  // Decrease semaphore
    if (semop(sem_id, &semaphore_operation, 1) == -1) {
        perror("Failed to wait on semaphore");
    }
}

// Function to perform "V" (signal) operation on semaphore
void signal_semaphore(int sem_id) {
    struct sembuf semaphore_operation = {0, 1, 0};   // Increase semaphore
    if (semop(sem_id, &semaphore_operation, 1) == -1) {
        perror("Failed to signal semaphore");
    }
}

int main() {
    // Create keys for shared memory and semaphore
    key_t memory_key = ftok(".", 'M');  // Key for shared memory
    key_t semaphore_key = ftok(".", 'S');  // Key for semaphore

    // Create a semaphore and initialize its value to 1 (binary semaphore)
    int semaphore_id = semget(semaphore_key, 1, 0666 | IPC_CREAT);
    if (semaphore_id == -1) {
        perror("Failed to create or access semaphore");
        return 1;
    }

    // Initialize the semaphore to 1
    union semaphore_union sem_union;
    sem_union.value = 1;  // Binary semaphore
    if (semctl(semaphore_id, 0, SETVAL, sem_union) == -1) {
        perror("Failed to initialize semaphore");
        return 1;
    }

    // Create shared memory segment of size 1024 bytes
    int shared_memory_id = shmget(memory_key, 1024, 0666 | IPC_CREAT);
    if (shared_memory_id == -1) {
        perror("Failed to create shared memory");
        return 1;
    }

    // Attach the shared memory segment
    char *shared_memory_address = shmat(shared_memory_id, NULL, 0);
    if (shared_memory_address == (char *)-1) {
        perror("Failed to attach to shared memory");
        return 1;
    }

    // Simulate writing data to shared memory within a protected critical section
    for (int i = 0; i < 5; i++) {
        printf("Attempting to wait on semaphore...\n");
        wait_semaphore(semaphore_id);  // Enter critical section
        printf("Entered critical section.\n");

        snprintf(shared_memory_address, 1024, "Writing data entry: %d", i + 1);
        printf("Writing to shared memory: %s\n", shared_memory_address);

        usleep(100000);  // Simulate a shorter delay (0.1 seconds instead of 1 second)

        printf("Exiting critical section.\n");
        signal_semaphore(semaphore_id);  // Exit critical section

        usleep(100000);  // Short delay between iterations for testing
    }

    // Detach from shared memory
    if (shmdt(shared_memory_address) == -1) {
        perror("Failed to detach from shared memory");
    }

    return 0;
}


/*
===========================================================================================
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ gcc 32b.c
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ ./a.out
Attempting to wait on semaphore...
Entered critical section.
Writing to shared memory: Writing data entry: 1
Exiting critical section.
Attempting to wait on semaphore...
Entered critical section.
Writing to shared memory: Writing data entry: 2
Exiting critical section.
Attempting to wait on semaphore...
Entered critical section.
Writing to shared memory: Writing data entry: 3
Exiting critical section.
Attempting to wait on semaphore...
Entered critical section.
Writing to shared memory: Writing data entry: 4
Exiting critical section.
Attempting to wait on semaphore...
Entered critical section.
Writing to shared memory: Writing data entry: 5
Exiting critical section.
============================================================================================
*/
