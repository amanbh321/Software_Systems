/*
============================================================================
Name : 5.c
Author : Aman Bahuguna
Description : Write a program to create five new files with infinite loop. 
              Execute the program in the background and 
              check the file descriptor table at /proc/pid/fd
Date: 25th Aug, 2024.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define NUM_FILES 5 // Number of files to create or open

int main() {
    int fileDescriptors[NUM_FILES]; // Array to hold file descriptors
    const char *fileNames[NUM_FILES] = {
        "file1.txt", "file2.txt", "file3.txt", "file4.txt", "file5.txt"
    };

    while (1) {
        // Open or create each file with read-write permissions
        for (int index = 0; index < NUM_FILES; ++index) {
            fileDescriptors[index] = open(fileNames[index], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);

            if (fileDescriptors[index] == -1) {
                perror("Failed to open or create file");
                exit(EXIT_FAILURE);
            }
            printf("Opened/Created '%s' with file descriptor %d\n", fileNames[index], fileDescriptors[index]);
        }

        sleep(10); // Pause execution to observe the result
    }

    return 0;
}

/*
============================================================================
After running the progtram in background, process id can be found by:
ps aux | grep create_files

Navigate to the /proc/<pid>/fd directory, where <pid> is the PID of our process:
ls -l /proc/<pid>/fd

This will list the file descriptors currently opened by the process. 
We see descriptors corresponding to file1.txt, file2.txt, etc.
============================================================================
*/
