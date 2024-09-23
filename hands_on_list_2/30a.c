/*
============================================================================
Name : 30a.c
Author : Aman Bahuguna
Description :  Write a program to create a shared memory.
               a) write some data to the shared memory
Date: 21th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <stdlib.h>

int main() {
    // Create a unique key for shared memory using ftok
    key_t key = ftok("sharedfile", 'A');
    if (key == -1) {
        perror("Error generating key");
        exit(EXIT_FAILURE);
    }

    // Allocate a shared memory segment of size 1024 bytes
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    if (shmid == -1) {
        perror("Error creating shared memory");
        exit(EXIT_FAILURE);
    }
    printf("Shared memory segment created with ID: %d\n", shmid);

    // Attach to the shared memory
    char *shmaddr = (char *)shmat(shmid, NULL, 0);
    if (shmaddr == (char *)-1) {
        perror("Error attaching to shared memory");
        exit(EXIT_FAILURE);
    }

    // Get user input to store in shared memory
    printf("Enter data to store in shared memory: ");
    fgets(shmaddr, 1024, stdin);

    // Display the data written to shared memory
    printf("Data written to shared memory: %s\n", shmaddr);

    // Detach from the shared memory after writing
    if (shmdt(shmaddr) == -1) {
        perror("Error detaching shared memory");
        exit(EXIT_FAILURE);
    }

    return 0;
}

/*
===========================================================================================
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ gcc 30a.c
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ ./a.out
Shared memory segment created with ID: 393237
Enter data to store in shared memory: 25
Data written to shared memory: 25
============================================================================================
*/
