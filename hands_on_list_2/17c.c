/*
============================================================================
Name : 17c.c
Author : Aman Bahuguna
Description : Write a program to execute ls -l | wc.
              c) use fcntl
Date: 19th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int pipefds[2];
    pipe(pipefds); // Create a pipe

    if (fork() == 0) {
        // Child process for 'ls -l'
        close(pipefds[0]); // Close the read end
        fcntl(pipefds[1], F_DUPFD, STDOUT_FILENO); // Redirect stdout to pipe's write end
        close(pipefds[1]); // Close the original write end
        execlp("ls", "ls", "-l", NULL); // Execute 'ls -l'
    } 
    
    else {
        // Parent process for 'wc'
        close(pipefds[1]); // Close the write end
        fcntl(pipefds[0], F_DUPFD, STDIN_FILENO); // Redirect stdin to pipe's read end
        close(pipefds[0]); // Close the original read end
        execlp("wc", "wc", NULL); // Execute 'wc'
    }

    return 0;
}

/*
===========================================================================================
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ gcc 17c.c
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ ./a.out
total 88
-rw-rw-r-- 1 aman aman  1283 Sep 21 16:03 11.c
-rw-rw-r-- 1 aman aman  1415 Sep 21 16:09 12.c
-rw-rw-r-- 1 aman aman  1390 Sep 21 16:16 14.c
-rw-rw-r-- 1 aman aman  1521 Sep 21 16:22 15.c
-rw-rw-r-- 1 aman aman  1626 Sep 21 16:26 16.c
-rw-rw-r-- 1 aman aman  1698 Sep 21 18:44 17a.c
-rw-rw-r-- 1 aman aman  1362 Sep 21 18:51 17b.c
-rw-rw-r-- 1 aman aman  1420 Sep 21 18:53 17c.c
-rw-rw-r-- 1 aman aman  2108 Sep 21 15:13 1a.c
-rw-rw-r-- 1 aman aman  2125 Sep 21 15:16 1b.c
-rw-rw-r-- 1 aman aman  2173 Sep 21 15:19 1c.c
-rw-rw-r-- 1 aman aman  2345 Sep 21 15:38 2.c
-rw-rw-r-- 1 aman aman  1280 Sep 21 15:35 3.c
-rw-rw-r-- 1 aman aman  1458 Sep 21 15:47 4.c
-rw-rw-r-- 1 aman aman  2989 Sep 21 15:50 5.c
-rw-rw-r-- 1 aman aman  1196 Sep 21 15:52 6.c
-rw-rw-r-- 1 aman aman  1222 Sep 21 15:54 7.c
-rw-rw-r-- 1 aman aman  1565 Sep 21 15:59 9.c
-rwxrwxr-x 1 aman aman 16176 Sep 21 18:53 a.out
============================================================================================
*/