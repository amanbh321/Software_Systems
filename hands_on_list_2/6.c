/*
============================================================================
Name : 6.c
Author : Aman Bahuguna
Description : Write a simple program to create three threads.
Date: 15th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <pthread.h>

void* simple_thread(void* arg) {
    printf("This is thread number %d\n", *(int*)arg);
    return NULL;
}

int main() {
    pthread_t threads[3];
    int thread_ids[3];

    // Create three threads
    for (int i = 0; i < 3; i++) {
        thread_ids[i] = i + 1;
        pthread_create(&threads[i], NULL, simple_thread, &thread_ids[i]);
    }

    // Wait for all threads to finish
    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}



/*
===========================================================================================
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ gcc 6.c
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ ./a.out
This is thread number 1
This is thread number 2
This is thread number 3
============================================================================================
*/