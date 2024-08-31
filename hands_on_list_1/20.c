/*
============================================================================
Name : 20.c
Author : Aman Bahuguna
Description : Find out the priority of your running program. 
              Modify the priority with nice command.
Date: 29th Aug, 2024.
============================================================================
*/

#include <unistd.h> // For `nice` system call
#include <stdio.h>  // For `printf`
#include <stdlib.h> // For `atoi` to convert string to int

int main(int argc, char *argv[])
{
    int currentPriority, adjustment;

    if (argc != 2)
    {
        printf("Please provide an integer value to adjust the current nice value.\n");
        return 1;
    }

    adjustment = atoi(argv[1]); // Convert argument to integer
    currentPriority = nice(0);  // Get the current priority

    printf("Initial priority: %d\n", currentPriority);

    currentPriority = nice(adjustment); // Adjust the priority by the specified amount

    printf("Adjusted priority: %d\n", currentPriority);

    return 0;
}


/*
============================================================================
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_1$ gcc 20.c
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_1$ ./a.out file4.txt
Initial priority: 0
Adjusted priority: 0
============================================================================
*/