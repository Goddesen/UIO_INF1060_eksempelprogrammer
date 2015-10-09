#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/ipc.h> 
#include <sys/msg.h> 
 
#define MSGLEN 100 
 
struct text_message { 
  long mtype; 
  char mtext[MSGLEN]; 
}; 

int main(int argc, char *argv[]) 
{ int msqID, len; 
  struct text_message mesg; 
 
  if (argc != 4) { printf("Usage: msgsnd <key> <type> <text>\n"); exit(1); } 

  len = strlen(argv[3]); 
  if (len > MSGLEN-1) { printf("String too long\n"); exit(1); } 

  /* get the message queue, which may need to be created */ 
  msqID = msgget((key_t) atoi(argv[1]), IPC_CREAT | 0666); 
  if (msqID == -1) { perror("msgget"); exit(1); } 
 
  /* build message */ 
  mesg.mtype = atoi(argv[2]); 
  strcpy(mesg.mtext, argv[3]);

  /* place message on the queue */ 
  if (msgsnd(msqID, (struct msgbuf *) &mesg, len+1, 0) == -1) { 
    perror("msgsnd"); 
    exit(1); 
  } 

  return 0; 
}
