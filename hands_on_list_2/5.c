/*
============================================================================
Name : 5.c
Author : Aman Bahuguna
Description : Write a program to print the system limitation of
                a. maximum length of the arguments to the exec family of functions.
                b. maximum number of simultaneous process per user id.
                c. number of clock ticks (jiffy) per second.
                d. maximum number of open files
                e. size of a page
                f. total number of pages in the physical memory
                g. number of currently available pages in the physical memory.
Date: 15th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/resource.h>
#include <sys/sysinfo.h>

int main() {
    // Print the maximum length of the arguments for exec family functions
    long arg_max = sysconf(_SC_ARG_MAX);
    if (arg_max != -1) {
        printf("Max argument length for exec: %ld\n", arg_max);
    }

    // Print the maximum number of processes per user ID
    long max_procs = sysconf(_SC_CHILD_MAX);
    if (max_procs != -1) {
        printf("Max processes per user: %ld\n", max_procs);
    }

    // Print the number of clock ticks per second (jiffies)
    long clock_ticks = sysconf(_SC_CLK_TCK);
    if (clock_ticks != -1) {
        printf("Clock ticks per second: %ld\n", clock_ticks);
    }

    // Get the limit for the maximum number of open files
    struct rlimit file_limit;
    if (getrlimit(RLIMIT_NOFILE, &file_limit) == 0) {
        printf("Max open files: Soft limit = %ld, Hard limit = %ld\n", 
                (long)file_limit.rlim_cur, (long)file_limit.rlim_max);
    } else {
        perror("Unable to get file limits");
    }

    // Print the size of a memory page
    long page_size = sysconf(_SC_PAGESIZE);
    if (page_size != -1) {
        printf("Page size: %ld bytes\n", page_size);
    }

    // Get system memory information
    struct sysinfo mem_info;
    if (sysinfo(&mem_info) == 0) {
        long total_pages = mem_info.totalram / page_size;
        long available_pages = mem_info.freeram / page_size;
        printf("Total physical memory pages: %ld\n", total_pages);
        printf("Available physical memory pages: %ld\n", available_pages);
    } else {
        perror("Unable to retrieve memory information");
    }

    return 0;
}



/*
===========================================================================================
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ gcc 5.c
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_2$ ./a.out
Max argument length for exec: 2097152
Max processes per user: 13078
Clock ticks per second: 100
Max open files: Soft limit = 1048576, Hard limit = 1048576
Page size: 4096 bytes
Total physical memory pages: 855798
Available physical memory pages: 50098
============================================================================================
*/