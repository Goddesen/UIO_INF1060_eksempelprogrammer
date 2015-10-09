#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/ipc.h> 
#include <sys/msg.h> 

#include "msg.h"

struct text_message { 
    long mtype; 
    char mtext[MSGLEN]; 
}; 

int main(int argc, char **argv) 
{
    int msqID, len, ret_val;
    struct text_message msg; 

    if (argc != 4) {
        printf("Usage: msgsnd <key> <type> <text>\n");
        exit(EXIT_FAILURE);
    } 

    len = strlen(argv[3]); 
    if (len > MSGLEN-1) {
        printf("String too long\n");
        exit(EXIT_FAILURE);
    }

    /* Get the message queue, which may need to be created */ 
    msqID = msgget((key_t) atoi(argv[1]), IPC_CREAT | 0666); 
    if (msqID < 0) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    /* Build message */ 
    msg.mtype = atoi(argv[2]); 
    strcpy(msg.mtext, argv[3]);

    /* Place message on the queue */ 
    ret_val = msgsnd(msqID, (struct msgbuf*)&msg, len + 1, 0);
    if (ret_val < 0) { 
        perror("msgsnd"); 
        exit(EXIT_FAILURE);
    } 

    return EXIT_SUCCESS; 
}
