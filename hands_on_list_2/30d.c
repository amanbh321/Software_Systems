/*
============================================================================
Name : 30d.c
Author : Aman Bahuguna
Description :  Write a program to create a shared memory.
               d) remove the shared memory
Date: 21th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1024 // Size of shared memory

int main(void) {
    int shm_id;
    key_t key;

    // Generate a unique key for the shared memory
    key = ftok(".", 'b');
    if (key == -1) {
        perror("Failed to generate key");
        return EXIT_FAILURE;
    }

    // Access the shared memory segment
    shm_id = shmget(key, SHM_SIZE, 0666);
    if (shm_id == -1) {
        perror("Error accessing shared memory");
        return EXIT_FAILURE;
    }

    // Remove the shared memory segment
    if (shmctl(shm_id, IPC_RMID, NULL) == -1) {
        perror("Failed to remove shared memory");
        return EXIT_FAILURE;
    }

    printf("Shared memory segment successfully removed.\n");

    return EXIT_SUCCESS;
}

/*
===========================================================================================
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ gcc 30d.c
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ ./a.out
Shared memory segment successfully removed.
============================================================================================
*/
