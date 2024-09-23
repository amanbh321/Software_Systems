/*
============================================================================
Name : 30b.c
Author : Aman Bahuguna
Description :  Write a program to create a shared memory.
               b) attach with O_RDONLY and check whether you are able to overwrite. 
Date: 21th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <stdlib.h>

int main() {
    // Generate a key using ftok
    key_t key = ftok("sharedfile", 'A');

    if (key == -1) {
        perror("Error generating key");
        exit(EXIT_FAILURE);
    }

    // Get the shared memory segment ID
    int shmid = shmget(key, 1024, 0666);
    if (shmid == -1) {
        perror("Error accessing shared memory");
        exit(EXIT_FAILURE);
    }

    // Attach to the shared memory in read-only mode
    char *shmaddr = (char *)shmat(shmid, NULL, SHM_RDONLY);
    if (shmaddr == (char *)-1) {
        perror("Error attaching to shared memory in read-only mode");
        exit(EXIT_FAILURE);
    }

    // Attempt to overwrite the memory in read-only mode (should not work)
    printf("Attempting to modify shared memory in read-only mode...\n");
    if (strcpy(shmaddr, "Attempted overwrite") == NULL) {
        printf("Failed to write to shared memory in read-only mode.\n");
    } 
    else {
        printf("Data after write attempt: %s\n", shmaddr);
    }

    // Print the current content of shared memory
    printf("Current data in shared memory: %s\n", shmaddr);

    // Detach from the shared memory
    if (shmdt(shmaddr) == -1) {
        perror("Error detaching from shared memory");
        exit(EXIT_FAILURE);
    }

    return 0;
}

/*
===========================================================================================
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ gcc 30b.c
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ ./a.out
Attempting to modify shared memory in read-only mode...
Segmentation fault (core dumped)
============================================================================================
*/
