/*
============================================================================
Name : 16.c
Author : Aman Bahuguna
Description : Write a program to send and receive data from parent to child vice versa. 
              Use two way communication.
Date: 19th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int p2c[2], c2p[2];
    pid_t pid;

    const char *parent_msg = "Hello from parent";
    const char *child_msg = "Hello from child";
    char buffer[50];

    pipe(p2c);
    pipe(c2p);

    if ((pid = fork()) == 0) {
        // Child process
        close(p2c[1]); // Close unused write end
        read(p2c[0], buffer, sizeof(buffer));
        printf("Child received: %s\n", buffer);
        write(c2p[1], child_msg, strlen(child_msg) + 1);
        close(p2c[0]);
        close(c2p[1]);
    } 
    
    else {
        // Parent process
        close(p2c[0]); // Close unused read end
        write(p2c[1], parent_msg, strlen(parent_msg) + 1);
        read(c2p[0], buffer, sizeof(buffer));
        printf("Parent received: %s\n", buffer);
        close(p2c[1]);
        close(c2p[0]);
    }

    return 0;
}

/*
===========================================================================================
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ gcc 16.c
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ ./a.out
Child received: Hello from parent
Parent received: Hello from child
============================================================================================
*/