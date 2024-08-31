/*
============================================================================
Name : 1b.c
Author : Aman Bahuguna
Description : Create a hard link file using the `link` system call

Date: 25th Aug, 2024.
============================================================================
*/

#include <unistd.h>  // Required for the `link` and `write` system calls
#include <stdio.h>   // Required for the `perror` and `printf` functions

// argv[1] -> Source file path
// argv[2] -> Destination hard link path
int main(int argc, char *argv[])
{
    // Variables to store the paths
    char *sourceFilePath;    
    char *hardLinkFilePath;  

    // Variable to hold the status of the link creation
    int linkStatus;          

    // Ensure that exactly two arguments are passed
    if (argc != 3) {
        printf("Usage: %s <source_file_path> <hard_link_path>\n", argv[0]);
    } else {
        // Assign the arguments to the respective variables
        sourceFilePath = argv[1];
        hardLinkFilePath = argv[2];

        // Attempt to create the hard link
        linkStatus = link(sourceFilePath, hardLinkFilePath);

        // Check if the hard link creation was successful
        if (linkStatus == -1) {
            perror("Failed to create hard link");
        } else {
            printf("Hard link created successfully. Verify using `ll` or `ls -l`.\n");
        }
    }

    return 0;  // Return success
}

/*
===========================================================================================
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_1$ gcc 1b.c
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_1$ ./a.out example.txt example-hard.txt
Hard link created successfully. Verify using `ll` or `ls -l`.
============================================================================================
*/