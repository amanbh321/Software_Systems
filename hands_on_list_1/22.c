/*
============================================================================
Name : 22.c
Author : Aman Bahuguna
Description : Write a program, open a file, call fork, and then write to the file 
              by both the child as well as the parent processes. Check output of the file.
Date: 30th Aug, 2024.
============================================================================
*/

#include <unistd.h>    // For `fork` system call
#include <sys/types.h> // For data types used in system calls like `fork` and `open`
#include <sys/stat.h>  // For file permissions used with `open`
#include <fcntl.h>     // For `open` system call

int main()
{
    const char *filePath = "sample.txt";
    pid_t processId;
    int fileDesc;

    // Open the file for writing, create it if it doesn't exist, and append to it
    fileDesc = open(filePath, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);

    // Fork a new process
    processId = fork();

    if (processId > 0) 
    {
        // Parent process writes to the file
        write(fileDesc, "Parent\n", 7);
    }
    else if (processId == 0) 
    {
        // Child process writes to the file
        write(fileDesc, "Child\n", 6);
    }

    // Close the file descriptor
    close(fileDesc);

    return 0;
}


/*
============================================================================
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_1$ gcc 22.c
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_1$ ./a.out
============================================================================
*/