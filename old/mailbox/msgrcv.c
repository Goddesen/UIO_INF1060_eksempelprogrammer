#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/ipc.h> 
#include <sys/msg.h> 
#include <errno.h> 
 
#define MSGLEN 100 
struct text_message { 
  long mtype; 
  char mtext[MSGLEN]; 
}; 

int main(int argc, char *argv[]) 
{  
  int msqID; 
  struct text_message mesg; 
 
  if (argc != 3) { printf("Usage: msgrcv <key> <type>\n"); exit(1); } 

  /* get the existing message queue */ 
  msqID = msgget((key_t)atoi(argv[1]), 0); 
  if (msqID == -1) { perror("msgget"); exit(1); }
 
  /* read message of the specified type; do not block */ 
  if (msgrcv(msqID, (struct msgbuf *) &mesg, MSGLEN, atoi(argv[2]), IPC_NOWAIT) == -1) 
  { 
    if (errno == ENOMSG) printf("No suitable message\n"); 
    else                 printf("msgrcv() error\n"); 
  } 
  else 
    printf("[%ld] %s\n", mesg.mtype, mesg.mtext); 

  return 0; 
}
