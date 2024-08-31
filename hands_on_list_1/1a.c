/*
============================================================================
Name : 1a.c
Author : Aman Bahuguna
Description : Create a soft link file using the `symlink` system call

Date: 25th Aug, 2024.
============================================================================
*/

#include <unistd.h>  // Needed for `symlink` and `write` system calls
#include <stdio.h>   // Needed for `perror` and `printf` functions

// argv[1] -> Source file path
// argv[2] -> Destination soft link path
int main(int argc, char *argv[])
{
    // Variables to hold the file paths
    char *sourcePath;    
    char *linkPath;      

    // Variable to store the status of symlink creation
    int result;         

    // Check if the correct number of arguments is provided
    if (argc != 3) {
        printf("Usage: %s <source_file_path> <soft_link_path>\n", argv[0]);
    } else {
        // Assign the arguments to the respective variables
        sourcePath = argv[1];
        linkPath = argv[2];

        // Attempt to create the symbolic link
        result = symlink(sourcePath, linkPath);

        // Check if the symlink was created successfully
        if (result == -1) {
            perror("Failed to create symbolic link");
        } else {
            printf("Symbolic link created successfully. Verify using `ll` or `ls -l`.\n");
        }
    }

    return 0;  // Return success
}

/*
===========================================================================================
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_1$ gcc 1a.c
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_1$ ./a.out example.txt example-soft
Symbolic link created successfully. Verify using `ll` or `ls -l`.
============================================================================================
*/