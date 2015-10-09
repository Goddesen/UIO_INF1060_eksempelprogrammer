#include <stdio.h>
#include <stdlib.h>
#include <time.h> /* for ctime() */
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main(int argc, char **argv)
{
	key_t mkey;
	int msqID, ret_val;
	struct msqid_ds mstatus;

	if (argc != 2) {
		printf("Usage: %s <key>\n", argv[0]);
		exit(1);
	}

	/* Access existing queue */
	mkey = (key_t) atoi(argv[1]);

	msqID = msgget(mkey, 0);
	if (msqID == -1) {
		perror("msgget");
		exit(2);
	}

	/* Get status information */
	ret_val = msgctl(msqID, IPC_STAT, &mstatus);
	if (ret_val == -1) {
		perror("msgctl");
		exit(3);
	}

	/* Print status info */
	printf("\nKey %ld, queue ID %d, ",    (long) mkey, msqID);
	printf("%d msgs on queue\n\n",        (int)  mstatus.msg_qnum);
	printf("Last send by pid %d at %s\n",
	       mstatus.msg_lspid, ctime(&(mstatus.msg_stime)));
	printf("Last rcv by pid %d at %s\n",
	       mstatus.msg_lrpid, ctime(&(mstatus.msg_rtime)));

	return EXIT_SUCCESS;
}
