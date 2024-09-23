/*
============================================================================
Name : 32a.c
Author : Aman Bahuguna
Description :  Write a program to implement semaphore to protect any critical section.
               a) rewrite the ticket number creation program using semaphore
Date: 22th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>

// Union to control semaphore settings
union semaphore_union {
    int value;
    struct semid_ds *buffer;
    unsigned short *array;
};

// Function to perform wait (P operation)
void wait_semaphore(int sem_id) {
    struct sembuf semaphore_operation = {0, -1, 0};  // Decrement semaphore
    semop(sem_id, &semaphore_operation, 1);
}

// Function to signal (V operation)
void signal_semaphore(int sem_id) {
    struct sembuf semaphore_operation = {0, 1, 0};  // Increment semaphore
    semop(sem_id, &semaphore_operation, 1);
}


int main() {
    int semaphore_id;
    key_t unique_key = ftok("/tmp", 'T');  // Generate a key for the semaphore

    // Access or create the semaphore
    semaphore_id = semget(unique_key, 1, 0666 | IPC_CREAT);
    if (semaphore_id == -1) {
        perror("Failed to access or create semaphore");
        return 1;
    }

    // Initialize the semaphore with a value of 1
    union semaphore_union semaphore_union;
    semaphore_union.value = 1;
    if (semctl(semaphore_id, 0, SETVAL, semaphore_union) == -1) {
        perror("Failed to initialize semaphore");
        return 1;
    }


    // Ticket generation process
    for (int i = 0; i < 5; i++) {
        wait_semaphore(semaphore_id);  // Enter critical section
        printf("Generating ticket number: %d\n", i + 1);
        usleep(100000);;  // Simulate ticket creation delay
        signal_semaphore(semaphore_id);  // Exit critical section
    }

    return 0;
}

/*
===========================================================================================
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ ipcs -s

------ Semaphore Arrays --------
key        semid      owner      perms      nsems     
0x41052728 0          aman       666        1         
0x42052728 1          aman       666        1         
0x9ef8c1f2 2          aman       644        1         
0xe0796443 3          aman       644        1         
0xee9c8269 4          aman       644        1         
0x54052728 5          aman       666        1         
0x43048aed 6          aman       644        6         
0x54056ac9 7          aman       666        1         
0x4466f20a 8          aman       644        8         
0x54050001 9          aman       666        1         

aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ gcc 32a.c
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ ./a.out
Generating ticket number: 1
Generating ticket number: 2
Generating ticket number: 3
Generating ticket number: 4
Generating ticket number: 5
============================================================================================
*/
