/*
============================================================================
Name : 9.c
Author : Aman Bahuguna
Description : Write a program to print the following information about a given file.
             a. inode
             b. number of hard links
             c. uid
             d. gid
             e. size
             f. block size
             g. number of blocks
             h. time of last access
             i. time of last modification
             j. time of last change
Date: 26th Aug, 2024.
============================================================================
*/

#include <sys/stat.h>  // For stat()
#include <unistd.h>    // For stat()
#include <stdio.h>     // For printf() and perror()
#include <time.h>      // For ctime()

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    struct stat fileInfo;
    int result = stat(filename, &fileInfo);

    if (result == -1) {
        perror("Unable to retrieve file status");
        return 1;
    }

    printf("Inode Number: %ld\n", fileInfo.st_ino);
    printf("Hard Links: %ld\n", fileInfo.st_nlink);
    printf("User ID: %d\n", fileInfo.st_uid);
    printf("Group ID: %d\n", fileInfo.st_gid);
    printf("File Size: %ld bytes\n", fileInfo.st_size);
    printf("Block Size: %ld bytes\n", fileInfo.st_blksize);
    printf("Total Blocks: %ld\n", fileInfo.st_blocks);

    // Convert epoch timestamps to human-readable form
    printf("Last Access Time: %s", ctime(&fileInfo.st_atim.tv_sec));
    printf("Last Modification Time: %s", ctime(&fileInfo.st_mtim.tv_sec));
    printf("Last Status Change Time: %s", ctime(&fileInfo.st_ctim.tv_sec));

    return 0;
}

/*
============================================================================
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_1$ gcc 9.c
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_1$ ./a.out file3.txt
Inode Number: 2524910
Hard Links: 1
User ID: 1000
Group ID: 1000
File Size: 80 bytes
Block Size: 4096 bytes
Total Blocks: 8
Last Access Time: Sat Aug 31 21:33:54 2024
Last Modification Time: Sat Aug 31 21:33:54 2024
Last Status Change Time: Sat Aug 31 21:33:54 2024
==============================================================================
*/