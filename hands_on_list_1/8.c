/*
============================================================================
Name : 8.c
Author : Aman Bahuguna
Description : Write a program to open a file in read only mode, 
              read line by line and display each line as it is read.
              Close the file when end of file is reached.
Date: 26th Aug, 2024.
============================================================================
*/

#include <fcntl.h>     // For open()
#include <unistd.h>    // For read(), write(), and close()
#include <stdio.h>     // For perror() and printf()

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("Failed to open file");
        return 1;
    }

    char ch;
    ssize_t bytesRead;
    while ((bytesRead = read(fd, &ch, 1)) == 1) {
        if (ch == '\n') {
            write(STDOUT_FILENO, "\n\n", 2);
        } else {
            write(STDOUT_FILENO, &ch, 1);
        }
    }

    if (bytesRead == -1) {
        perror("Error reading file");
    }

    write(STDOUT_FILENO, "\n", 1);
    close(fd);
    return 0;
}

/*
============================================================================
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_1$ gcc 8.c
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_1$ ./a.out file3.txt
Hello, My name is Aman.

I am 1st year M.Tech student at IIITB.

Nice to meet you!
==============================================================================
*/
