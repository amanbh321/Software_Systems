/*
============================================================================
Name : 26.c
Author : Aman Bahuguna
Description : Write a program to execute an executable program.
              a. use some executable program
              b. pass some input to an executable program. (for example execute an executable of $./a.out name)
Date: 31th Aug, 2024.
============================================================================
*/

#include <unistd.h> // For `execl` function

int main()
{
    const char *programPath = "a.out";
    const char *fileName = "25.c";

    // Replace the current process image with a new process image
    execl(programPath, programPath, fileName, NULL);

    // If execl returns, an error occurred
    perror("execl failed");
    return 1;
}


/*
============================================================================
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_1$ gcc 25.c
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_1$ gcc -o 26.out 26.c
26.c: In function ‘main’:
26.c:23:5: warning: implicit declaration of function ‘perror’ [-Wimplicit-function-declaration]
   23 |     perror("execl failed");
      |     ^~~~~~
aman@aman-HP-Laptop-15s-gr0xxx:~/Desktop/hands_on_list_1$ ./26.out
First child process (A) created.
Child A is sleeping for 5 seconds...
Second child process (B) created.
Child B is sleeping for 10 seconds...
Third child process (C) created.
Child C is sleeping for 15 seconds...
Child A has woken up!
Child B has woken up!
Child C has woken up!
Child C exited with status: 0
============================================================================
*/