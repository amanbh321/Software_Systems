/*
============================================================================
Name : 16a.c
Author : Aman Bahuguna
Description : Write a program to perform mandatory locking.
              a. Implement write lock
Date: 29th Aug, 2024.
============================================================================
*/

#include <unistd.h>    // For `fcntl` and `getpid`
#include <fcntl.h>     // For `fcntl` and file operations
#include <sys/types.h> // For data types used in system calls
#include <sys/stat.h>  // For file permission and status flags
#include <stdio.h>     // For `printf`

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Please provide a file name as an argument.\n");
        return 1;
    }

    char *filename = argv[1];
    struct flock lock;
    int fd = open(filename, O_RDWR);

    if (fd == -1)
    {
        perror("Failed to open the file");
        return 1;
    }

    // Initialize the lock structure
    lock.l_type = F_WRLCK;    // Request a write lock
    lock.l_whence = SEEK_SET; // Start the lock from the beginning of the file
    lock.l_start = 0;         // Lock the entire file
    lock.l_len = 0;           // Length 0 means lock to EOF
    lock.l_pid = getpid();    // Locking process ID

    // Check the current lock status
    if (fcntl(fd, F_GETLK, &lock) == -1)
    {
        perror("Failed to retrieve lock status");
        close(fd);
        return 1;
    }

    if (lock.l_type == F_UNLCK)
    {
        // No lock is set, so we can apply the write lock
        lock.l_type = F_WRLCK;
        if (fcntl(fd, F_SETLK, &lock) == -1)
        {
            perror("Failed to apply write lock");
            close(fd);
            return 1;
        }
        printf("File is now locked for writing.\n");
    }
    else if (lock.l_type == F_WRLCK)
    {
        printf("File is already locked for writing by process %d.\n", lock.l_pid);
    }
    else if (lock.l_type == F_RDLCK)
    {
        printf("File is already locked for reading by process %d.\n", lock.l_pid);
    }

    // close(fd); // Close the file descriptor after locking

    return 0;
}

/*
=========================================================================
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_1$ gcc 16a.c
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_1$ ./a.out file2.txt
File is now locked for writing.
==========================================================================
*/

