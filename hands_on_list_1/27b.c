/*
============================================================================
Name : 27b.c
Author : Aman Bahuguna
Description : Write a program to execute `ls -Rl` by the following system calls 
              2. `execlp` 
Date: 31th Aug, 2024.
============================================================================
*/

#include <unistd.h>  // Required for the `execlp` function
#include <stdio.h>   // Required for the `printf` function

int main()
{
    // Define the command and its arguments
    char *cmd_name = "ls";
    char *cmd_options = "-Rl";
    char *target_dir = ".";  // Directory to run the `ls` command on

    // Display output header
    printf("============ OUTPUT USING execlp =============\n");

    // Execute the `ls` command with options and target directory
    execlp(cmd_name, cmd_name, cmd_options, target_dir, NULL);

    // If execlp fails, this line will execute
    printf("Failed to execute command\n");

    return 0;
}


/*
============================================================================
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_1$ gcc 27b.c 
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_1$ ./a.out 
============ OUTPUT USING execlp =============
.:
total 192
-rw-rw-r-- 1 aman aman  2024 Aug 31 21:37 10.c
-rw-rw-r-- 1 aman aman  3360 Aug 31 21:38 11.c
-rw-rw-r-- 1 aman aman  2325 Aug 31 21:39 12.c
-rw-rw-r-- 1 aman aman  1706 Aug 31 21:40 13.c
-rw-rw-r-- 1 aman aman  2466 Aug 31 21:41 14.c
-rw-rw-r-- 1 aman aman  1094 Aug 31 18:49 15.c
-rw-rw-r-- 1 aman aman  2460 Aug 31 19:07 16a.c
-rw-rw-r-- 1 aman aman  2521 Aug 31 19:07 16b.c
-rw-rw-r-- 1 aman aman  3533 Aug 31 19:17 17.c
-rw-rw-r-- 1 aman aman  1406 Aug 31 19:16 19.c
-rw-rw-r-- 1 aman aman  1808 Aug 31 21:45 1a.c
-rw-rw-r-- 1 aman aman  1833 Aug 31 21:46 1b.c
-rw-rw-r-- 1 aman aman  1891 Aug 31 21:28 1c.c
-rw-rw-r-- 1 aman aman  1371 Aug 31 19:19 20.c
-rw-rw-r-- 1 aman aman  1272 Aug 31 19:22 21.c
-rw-rw-r-- 1 aman aman  1551 Aug 31 19:26 22.c
-rw-rw-r-- 1 aman aman  1611 Aug 31 19:31 23.c
-rw-rw-r-- 1 aman aman  1997 Aug 31 19:37 24.c
-rw-rw-r-- 1 aman aman  3207 Aug 31 19:38 25.c
-rw-rw-r-- 1 aman aman  1645 Aug 31 19:50 26.c
-rwxrwxr-x 1 aman aman 16000 Aug 31 19:48 26.out
-rw-rw-r-- 1 aman aman  3756 Aug 31 22:00 27a.c
-rw-rw-r-- 1 aman aman  1828 Aug 31 22:02 27b.c
-rw-rw-r-- 1 aman aman  1861 Aug 31 21:55 27c.c
-rw-rw-r-- 1 aman aman  1779 Aug 31 21:56 27d.c
-rw-rw-r-- 1 aman aman  1797 Aug 31 21:58 27e.c
-rw-rw-r-- 1 aman aman  1491 Aug 31 21:49 28.c
-rw-rw-r-- 1 aman aman  2421 Aug 31 19:57 29.c
-rw-rw-r-- 1 aman aman  1972 Aug 31 21:27 2.c
-rw-rw-r-- 1 aman aman  2435 Aug 31 21:48 30.c
-rw-rw-r-- 1 aman aman  1025 Aug 31 21:28 3.c
-rw-rw-r-- 1 aman aman  1781 Aug 31 21:29 4.c
-rw-rw-r-- 1 aman aman  1845 Aug 31 21:31 5.c
-rw-rw-r-- 1 aman aman   912 Aug 31 21:31 6.c
-rw-rw-r-- 1 aman aman  1889 Aug 31 21:33 7.c
-rw-rw-r-- 1 aman aman  1617 Aug 31 21:35 8.c
-rw-rw-r-- 1 aman aman  2339 Aug 31 21:36 9.c
-rwxrwxr-x 1 aman aman 16000 Aug 31 22:03 a.out
-rw------- 1 aman aman    26 Aug 31 21:37 example_dup.txt
-rw-r--r-- 2 aman aman     0 Aug 31 21:27 example-hard.txt
lrwxrwxrwx 1 aman aman    11 Aug 31 21:44 example-soft -> example.txt
-rw-r--r-- 2 aman aman     0 Aug 31 21:27 example.txt
-rw------- 1 aman aman    17 Aug 31 21:32 file1.txt
-rw------- 1 aman aman    17 Aug 31 21:32 file2.txt
-rw------- 1 aman aman    80 Aug 31 21:37 file3.txt
-rw------- 1 aman aman     0 Aug 31 21:30 file4.txt
-rw------- 1 aman aman     0 Aug 31 21:30 file5.txt
prwx------ 1 aman aman     0 Aug 31 21:25 mymkfifo
prwx------ 1 aman aman     0 Aug 31 21:25 mymknod-fifo
============================================================================
*/