#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>

#define SHMSZ     27

int main()
{
    int shmid;
    key_t key;
    char *shm, *s;

    key = 5678; /* selected key by server */

    /* Locate the segment. */
    shmid = shmget(key, SHMSZ, 0666);
    if (shmid < 0)
    {
        perror("shmget");
        exit(1);
    }

    /* Now we attach the segment to our data space. */
    shm = shmat(shmid, NULL, 0);
    if (shm == (char *) -1)
    {
        perror("shmat");
        exit(1);
    }

    /* read what the server put in the memory. */

    for (s = shm; *s != '\0'; s++)
        putchar(*s);

    putchar('\n');

    /* change the first character in segment to '*' */
    *shm = '*';

    return 0;
}
