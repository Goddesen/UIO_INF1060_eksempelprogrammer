#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/ipc.h> 
#include <sys/msg.h> 
#include <errno.h> 

#include "msg.h"

struct text_message { 
    long mtype; 
    char mtext[MSGLEN]; 
}; 

int main(int argc, char **argv) 
{  
    int msqID, ret_val;
    struct text_message msg; 

    if (argc != 3) {
        printf("Usage: %s <key> <type>\n", argv[0]);
        exit(EXIT_FAILURE);
    } 

    /* Get the existing message queue */ 
    msqID = msgget((key_t) atoi(argv[1]), 0); 
    if (msqID < 0) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    /* Read message of the specified type; do not block */ 
    ret_val = msgrcv(msqID, (struct msgbuf *)&msg,
		     MSGLEN, atoi(argv[2]), IPC_NOWAIT);
    if (ret_val < 0) { 
        if (errno == ENOMSG)
            printf("No suitable message\n");
        else
            printf("msgrcv() error\n");
	exit(EXIT_FAILURE);
    }

    printf("[%ld] %s\n", msg.mtype, msg.mtext); 

    return EXIT_SUCCESS; 
}
