/* ----------------------------------------------------------
   Program : ForkTest.c
   By      : T. Beutel
   Revised : B. Kasper, February 2015
   Description: This program demonstrates use of the fork()
   system call to create a child process and the way in which
   the parent and child execute.
   ---------------------------------------------------------- */

#include <stdlib.h>
#include <stdio.h>      // C standard I/O library
#include <unistd.h>     // essential POSIX API functions and constants
#include <sys/wait.h>

void flushInputBuffer(char *targetBuffer);

void delay (long n) {
    long t;
    for (t=0; t<n; t++)	/* for a long time... */
        ;	        /* ... do nothing!    */
}

int main() {
    int k;

    pid_t pid = fork();

    if (pid != 0) {	/* create child process */
        /* parent branch */
        printf("Parent Parent ID = %d\n", getppid());
        for (k=1; k<5; k++) {
            delay (1000000);	/* kill time */
            printf("Parent PID = %d\n", getpid());
        }

        int status;
        waitpid(pid, &status, 0);
    }
    else {
        /* child branch */
        printf("Child Parent ID = %d\n", getppid());
        for (k=1; k<5; k++) {
            delay (1000000);	/* kill time here too */
            printf("Child PID = %d\n", getpid());
        }

        // Try to avoid concurrency issues.
        delay (10000000);

        char input[2] = "C";
        while (input[0] != 'Q') {
            printf("Child paused, enter C to continue, or Q to quit: ");
            if (fgets(input, sizeof(input), stdin) != NULL) {
                // Clear out any extra characters in input buffer.
                flushInputBuffer(input);
            } else {
                // EOF is basically 'Q'.
                printf("Q\n");
                input[0] = 'Q';
            }
        }
    }

    exit(EXIT_SUCCESS);
}

void flushInputBuffer(char *targetBuffer) {
    if (targetBuffer != NULL && targetBuffer[2] != '\0') {
        char c;
        while ((c = getchar()) != '\n' && c != EOF);
    }
}
