/*
============================================================================
Name : 17.c
Author : Aman Bahuguna
Description : Write a program to simulate online ticket reservation. Implement write lock
              Write a program to open a file, store a ticket number and exit. 
              Write a separate program, to open the file, implement write lock, 
              read the ticket number, increment the number and print the new ticket 
              number then close the file.
Date: 29th Aug, 2024.
============================================================================
*/

#include <sys/types.h> // For system data types used in system calls
#include <sys/stat.h>  // For file status and permission flags
#include <fcntl.h>     // For file control operations
#include <unistd.h>    // For read, write, lseek, and file locking
#include <stdio.h>     // For standard I/O operations

int main()
{
    char *filePath = "ticket-file.txt"; // File storing the ticket number

    int fd;
    ssize_t bytesRead, bytesWritten;
    off_t offset;
    int ticketNumber;
    struct flock lock;

    fd = open(filePath, O_CREAT | O_RDWR, S_IRWXU);

    if (fd == -1)
    {
        perror("Failed to open the file");
        return 1;
    }

    // Set up the lock structure
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0; // Lock the entire file
    lock.l_pid = getpid();

    if (fcntl(fd, F_GETLK, &lock) == -1)
    {
        perror("Unable to determine lock status");
        close(fd);
        return 1;
    }

    if (lock.l_type != F_UNLCK)
    {
        if (lock.l_type == F_WRLCK)
            printf("File %s is already locked for writing.\n", filePath);
        else if (lock.l_type == F_RDLCK)
            printf("File %s is already locked for reading.\n", filePath);

        close(fd);
        return 1;
    }

    // Apply a write lock on the file
    lock.l_type = F_WRLCK;
    if (fcntl(fd, F_SETLKW, &lock) == -1)
    {
        perror("Failed to lock the file");
        close(fd);
        return 1;
    }

    // Read the current ticket number from the file
    bytesRead = read(fd, &ticketNumber, sizeof(int));
    if (bytesRead == -1)
    {
        perror("Failed to read ticket number");
    }
    else if (bytesRead == 0)
    {
        // If file is empty, start ticket number from 1
        ticketNumber = 1;
    }
    else
    {
        // If reading was successful, increment the ticket number
        ticketNumber++;
    }

    // Reset file offset to the beginning
    offset = lseek(fd, 0, SEEK_SET);
    if (offset == -1)
    {
        perror("Failed to reset file position");
    }
    else
    {
        // Write the updated ticket number back to the file
        bytesWritten = write(fd, &ticketNumber, sizeof(int));
        if (bytesWritten == -1)
        {
            perror("Failed to update the ticket number");
        }
        else
        {
            printf("Your ticket number is: %d\n", ticketNumber);
        }
    }

    // Release the lock on the file
    lock.l_type = F_UNLCK;
    if (fcntl(fd, F_SETLKW, &lock) == -1)
    {
        perror("Failed to release the lock");
    }

    close(fd);
    return 0;
}

/*
=========================================================================
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_1$ gcc 17.c
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_1$ ./a.out
Your ticket number is: 1
==========================================================================
*/

