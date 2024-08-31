/*
============================================================================
Name : 10.c
Author : Aman Bahuguna
Description : Write a program to open a file with read write mode, 
              write 10 bytes, move the file pointer by 10 bytes (use lseek) and write again 10 bytes.
              a. check the return value of lseek
              b. open the file with od and check the empty spaces in between the data.
Date: 26th Aug, 2024.
============================================================================
*/

#include <fcntl.h>     // For open()
#include <unistd.h>    // For close(), lseek(), and write()
#include <stdio.h>     // For perror() and printf()

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    int fd = open(filename, O_RDWR);
    if (fd == -1) {
        perror("Failed to open file");
        return 1;
    }

    off_t newOffset = lseek(fd, 10, SEEK_SET);
    if (newOffset == -1) {
        perror("Failed to seek in file");
        close(fd);
        return 1;
    }

    ssize_t bytesWritten = write(fd, "ABCDEFGHIJ", 10);
    if (bytesWritten == -1) {
        perror("Failed to write to file");
        close(fd);
        return 1;
    }

    newOffset = lseek(fd, 10, SEEK_CUR);
    if (newOffset == -1) {
        perror("Failed to seek in file");
        close(fd);
        return 1;
    }

    bytesWritten = write(fd, "ABCDEFGHIJ", 10);
    if (bytesWritten == -1) {
        perror("Failed to write to file");
        close(fd);
        return 1;
    }

    printf("New file offset: %ld\n", (long)newOffset);
    close(fd);
    return 0;
}

/*
=======================================================================
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_1$ gcc 10.c
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_1$ ./a.out file3.txt
New file offset: 30
========================================================================
*/