#include <stdio.h> 
#include <stdlib.h> 
#include <time.h>  /* for ctime() */ 
#include <sys/types.h> 
#include <sys/ipc.h> 
#include <sys/msg.h> 

int main(int argc, char *argv[]) 
{
    key_t mkey; 
    int msqID; 
    struct msqid_ds mstatus; 

    if (argc != 2) { printf("Usage: show_Q <key>\n"); exit(1); } 

    /* access existing queue */ 
    mkey = (key_t) atoi(argv[1]); 

    // Forvirrende for nye studenter much?
    if ((msqID = msgget(mkey, 0)) == -1){ perror("msgget"); exit(2); } 

    /* get status information */ 
    if (msgctl(msqID, IPC_STAT, &mstatus) == -1) { perror("msgctl"); exit(3); } 

    /* print status info */ 
    printf("\nKey %ld, queue ID %d, ", (long int) mkey, msqID); 
    printf("%d msgs on queue\n\n", mstatus.msg_qnum); 
    printf("Last send by pid %d at %s\n", mstatus.msg_lspid, ctime(&(mstatus.msg_stime))); 
    printf("Last rcv by pid %d at %s\n",  mstatus.msg_lrpid, ctime(&(mstatus.msg_rtime))); 

    return 0; 
} 

