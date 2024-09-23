/*
============================================================================
Name : 7.c
Author : Aman Bahuguna
Description : Write a simple program to print the created thread ids
Date: 15th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <pthread.h>

#include <stdio.h>
#include <pthread.h>

void* print_thread_id(void* arg) {
    // Get and print the thread ID
    printf("Thread ID: %lu\n", pthread_self());
    return NULL;
}

int main() {
    pthread_t threads[3];

    // Create three threads
    for (int i = 0; i < 3; i++) {
        pthread_create(&threads[i], NULL, print_thread_id, NULL);
    }

    // Wait for all threads to finish
    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}



/*
===========================================================================================
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ gcc 7.c
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ ./a.out
Thread ID: 139895465047744
Thread ID: 139895456655040
Thread ID: 139895448262336
============================================================================================
*/