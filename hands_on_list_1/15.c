/*
============================================================================
Name : 15.c
Author : Aman Bahuguna
Description : Write a program to display the environmental variable of the user (use environ).
Date: 28th Aug, 2024.
============================================================================
*/

#include <stdio.h> // Required for `printf`, `NULL`

extern char **environ; // External declaration for environment variables

int checkUserEnv(char *variable) {
    // Check if the environment variable starts with 'USER='
    return variable[0] == 'U' && variable[1] == 'S' && variable[4] == '=';
}

int main() {
    int i = 0;

    // Iterate through the environment variables
    while (environ[i] != NULL) {
        // If the variable is a user-related variable, print it
        if (checkUserEnv(environ[i])) {
            printf("%s\n", environ[i]);
        }
        i++;
    }

    return 0;
}

/*
============================================================================
Output :
USER=aman
============================================================================
*/