/*
============================================================================
Name : 30c.c
Author : Aman Bahuguna
Description :  Write a program to create a shared memory.
               c) detach the shared memory
Date: 21th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <string.h>

#define SHM_SIZE 1024 // Size of shared memory

int main(void) {
    int shm_id;
    char *shared_memory;
    key_t key;

    // Generate a unique key for shared memory
    key = ftok(".", 'b');
    if (key == -1) {
        perror("ftok failed");
        return EXIT_FAILURE;
    }

    // Create or get the shared memory segment
    shm_id = shmget(key, SHM_SIZE, 0666 | IPC_CREAT);
    if (shm_id == -1) {
        perror("Failed to get shared memory");
        return EXIT_FAILURE;
    }

    // Attach to the shared memory segment
    shared_memory = shmat(shm_id, NULL, 0);
    if (shared_memory == (char *)-1) {
        perror("Failed to attach shared memory");
        return EXIT_FAILURE;
    }

    // Optionally, initialize or use the shared memory here
    strcpy(shared_memory, "Hello, shared memory!"); // Example usage

    // Detach from the shared memory
    if (shmdt(shared_memory) == -1) {
        perror("Failed to detach from shared memory");
        return EXIT_FAILURE;
    }

    printf("Successfully detached from shared memory.\n");

    return EXIT_SUCCESS;
}

/*
===========================================================================================
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ gcc 30c.c
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ ./a.out
Successfully detached from shared memory.
============================================================================================
*/
