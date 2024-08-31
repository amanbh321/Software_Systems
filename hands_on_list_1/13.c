/*
============================================================================
Name : 13.c
Author : Aman Bahuguna
Description : Write a program to wait for a STDIN for 10 seconds using select. 
              Write a proper print statement to verify whether the data is available 
              within 10 seconds or not (check in $man 2 select).
Date: 27th Aug, 2024.
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/select.h>

int main() {
    fd_set readfds;  // Set of file descriptors to watch for input
    struct timeval timeout;
    int ret;

    // Clear the set and add STDIN (file descriptor 0)
    FD_ZERO(&readfds);
    FD_SET(STDIN_FILENO, &readfds);  // STDIN is file descriptor 0

    // Set the timeout to 10 seconds
    timeout.tv_sec = 10;
    timeout.tv_usec = 0;

    printf("Waiting for input on STDIN for 10 seconds...\n");

    // Use select to wait for input on STDIN
    ret = select(STDIN_FILENO + 1, &readfds, NULL, NULL, &timeout);

    if (ret == -1) {
        perror("select failed");
        return 1;
    } else if (ret == 0) {
        printf("No data received within 10 seconds.\n");
    } else {
        if (FD_ISSET(STDIN_FILENO, &readfds)) {
            printf("Data is available on STDIN!\n");
        }
    }

    return 0;
}

/*
===================================================================
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_1$ gcc 13.c
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_1$ ./a.out
Waiting for input on STDIN for 10 seconds...
No data received within 10 seconds.
====================================================================
*/