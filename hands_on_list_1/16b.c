/*
============================================================================
Name : 16b.c
Author : Aman Bahuguna
Description : Write a program to perform mandatory locking.
              b. Implement read lock
Date: 29th Aug, 2024.
============================================================================
*/

#include <unistd.h>    // For `fcntl` and process-related functions
#include <fcntl.h>     // For file control operations like `fcntl` and `open`
#include <sys/types.h> // For system data types
#include <sys/stat.h>  // For file status and permission flags
#include <stdio.h>     // For `printf`

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Please provide a file name as an argument.\n");
        return 1;
    }

    char *filename = argv[1];
    struct flock fileLock;
    int fd = open(filename, O_RDONLY);

    if (fd == -1)
    {
        perror("Unable to open the file");
        return 1;
    }

    // Set up the lock structure for a read lock
    fileLock.l_type = F_RDLCK;    // Request a read lock
    fileLock.l_whence = SEEK_SET; // Lock starts at the beginning of the file
    fileLock.l_start = 0;         // Offset from `l_whence`
    fileLock.l_len = 0;           // Lock to EOF
    fileLock.l_pid = getpid();    // Process ID of the locking process

    // Check if the file is already locked
    if (fcntl(fd, F_GETLK, &fileLock) == -1)
    {
        perror("Failed to check lock status");
        close(fd);
        return 1;
    }

    if (fileLock.l_type == F_WRLCK)
    {
        printf("The file is already locked for writing by process %d.\n", fileLock.l_pid);
    }
    else if (fileLock.l_type == F_RDLCK)
    {
        printf("The file is already locked for reading by process %d.\n", fileLock.l_pid);
    }
    else
    {
        // Apply the read lock
        fileLock.l_type = F_RDLCK;
        if (fcntl(fd, F_SETLK, &fileLock) == -1)
        {
            perror("Failed to apply the read lock");
            close(fd);
            return 1;
        }
        printf("The file is now locked for reading.\n");
    }

    // close(fd); // Close the file descriptor after applying the lock

    return 0;
}

/*
=========================================================================
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_1$ gcc 16b.c
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_1$ ./a.out file5.txt
The file is now locked for reading.
==========================================================================
*/

