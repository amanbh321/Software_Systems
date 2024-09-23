/*
============================================================================
Name : 2.c
Author : Aman Bahuguna
Description : Write a program to print the system resource limits. Use getrlimit system call.
Date: 15th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <sys/resource.h>
#include <stdlib.h>

void show_limit(int resource, const char *resource_name) {
    struct rlimit limit;

    if (getrlimit(resource, &limit) == 0) {
        printf("%s:\n", resource_name);
        printf("Soft limit: %ld\n", (long)limit.rlim_cur);
        printf("Hard limit: %ld\n", (long)limit.rlim_max);
        printf("----------------------------\n");
    } else {
        perror("Failed to get limit");
    }
}

int main() {
    show_limit(RLIMIT_CPU, "CPU Time Limit");
    show_limit(RLIMIT_FSIZE, "Max File Size");
    show_limit(RLIMIT_DATA, "Max Data Segment Size");
    show_limit(RLIMIT_STACK, "Max Stack Size");
    show_limit(RLIMIT_RSS, "Max Resident Set Size");
    show_limit(RLIMIT_NPROC, "Max Number of Processes");
    show_limit(RLIMIT_NOFILE, "Max Open File Descriptors");
    show_limit(RLIMIT_MEMLOCK, "Max Locked Memory");
    show_limit(RLIMIT_AS, "Max Address Space");

    return 0;
}


/*
============================================================================================
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ gcc 2.c
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ ./a.out
CPU Time Limit:
Soft limit: -1
Hard limit: -1
----------------------------
Max File Size:
Soft limit: -1
Hard limit: -1
----------------------------
Max Data Segment Size:
Soft limit: -1
Hard limit: -1
----------------------------
Max Stack Size:
Soft limit: 8388608
Hard limit: -1
----------------------------
Max Resident Set Size:
Soft limit: -1
Hard limit: -1
----------------------------
Max Number of Processes:
Soft limit: 13078
Hard limit: 13078
----------------------------
Max Open File Descriptors:
Soft limit: 1048576
Hard limit: 1048576
----------------------------
Max Locked Memory:
Soft limit: 438165504
Hard limit: 438165504
----------------------------
Max Address Space:
Soft limit: -1
Hard limit: -1
----------------------------
============================================================================================
*/