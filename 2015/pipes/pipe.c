#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MSGSIZE 20

char *msg = "hello";

int main()
{  
    char inbuf[MSGSIZE];
    int p[2];
    pid_t pid;

    /* open pipe */ 	
    if (pipe(p) == -1)
    {
        perror("pipe call error");
        exit(1);
    }

    pid = fork();
    switch(pid) {
        case -1:
            perror("error: fork call");
            exit(2);

        case 0: 
            close(p[0]); /* close the read end of the pipe */

            write(p[1], msg, MSGSIZE);
            printf("Child sent: %s\n", msg);
            break;

        default:
            close(p[1]);  /* close the write end of the pipe */

            read(p[0], inbuf, MSGSIZE);
            printf("Parent read: %s\n", inbuf);
            wait(0);
    }
    exit(0);
}
