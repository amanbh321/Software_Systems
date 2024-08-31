/*
============================================================================
Name : 14.c
Author : Aman Bahuguna
Description : Write a program to find the type of a file.
              a. Input should be taken from command line.
              b. program should be able to identify any type of a file.
Date: 27th Aug, 2024.
============================================================================
*/

#include <sys/types.h> // Required for `stat` structure
#include <sys/stat.h>  // Required for `stat` system call
#include <unistd.h>    // Required for `fstat`, `write`, and `STDOUT_FILENO`
#include <fcntl.h>     // Required for `open` and `O_RDONLY`
#include <stdio.h>     // Required for `printf`

int main(int argc, char *argv[]) {
    struct stat fileStat;
    int fd;

    // Check if the filename is provided
    if (argc != 2) {
        printf("Please provide the file name as an argument.\n");
        return 1;
    }

    // Open the file in read-only mode
    fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("Failed to open the file");
        return 1;
    }

    // Retrieve the file status
    if (fstat(fd, &fileStat) == -1) {
        perror("Failed to get the file status");
        close(fd);
        return 1;
    }

    // Determine the type of file
    if (S_ISREG(fileStat.st_mode)) {
        write(STDOUT_FILENO, "This is a regular file.\n", 24);
    } else if (S_ISDIR(fileStat.st_mode)) {
        write(STDOUT_FILENO, "This is a directory.\n", 21);
    } else if (S_ISCHR(fileStat.st_mode)) {
        write(STDOUT_FILENO, "This is a character device file.\n", 33);
    } else if (S_ISBLK(fileStat.st_mode)) {
        write(STDOUT_FILENO, "This is a block device file.\n", 29);
    } else if (S_ISFIFO(fileStat.st_mode)) {
        write(STDOUT_FILENO, "This is a FIFO (named pipe).\n", 30);
    } else if (S_ISLNK(fileStat.st_mode)) {
        write(STDOUT_FILENO, "This is a symbolic link.\n", 25);
    } else if (S_ISSOCK(fileStat.st_mode)) {
        write(STDOUT_FILENO, "This is a socket.\n", 18);
    } else {
        write(STDOUT_FILENO, "Unknown file type.\n", 19);
    }

    close(fd);
    return 0;
}

/*
===================================================================
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_1$ gcc 14.c
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_1$ ./a.out file3.txt
This is a regular file.
====================================================================
*/