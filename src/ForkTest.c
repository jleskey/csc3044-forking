/* ----------------------------------------------------------
   Program : ForkTest.c
   By      : T. Beutel
   Revised : B. Kasper, February 2015
   Description: This program demonstrates use of the fork()
   system call to create a child process and the way in which
   the parent and child execute.
   ---------------------------------------------------------- */

#include <stdio.h>      // C standard I/O library
#include <unistd.h>     // essential POSIX API functions and constants

void delay (long n) {
    long t;
    for (t=0; t<n; t++)	/* for a long time... */
        ;	        /* ... do nothing!    */
}

int main() {
    int k;

    if (fork() != 0) {	/* create child process */
        /* parent branch */
        printf("Parent Parent ID = %d\n", getppid());
        for (k=1; k<5; k++) {
            delay (1000000);	/* kill time */
            printf("Parent PID = %d\n", getpid());
        }
    }
    else {
        /* child branch */
        printf("Child Parent ID = %d\n", getppid());
        for (k=1; k<5; k++) {
            delay (1000000);	/* kill time here too */
            printf("Child PID = %d\n", getpid());
        }
    }
}
