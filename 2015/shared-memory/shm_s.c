#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SHMSZ     27

int main()
{
    int shmid;
    key_t key;
    char c, *shm, *s;

    key = 5678; /* selected key */

    /* Create the segment.*/
    shmid = shmget(key, SHMSZ, IPC_CREAT | 0666);
    if (shmid < 0)
    {
        perror("shmget");
        exit(1);
    }

    /* Now we attach the segment to our data space.*/
    shm = shmat(shmid, NULL, 0);
    if (shm == (void *) -1)
    {
        perror("shmat");
        exit(1);
    }

    /* put some things into the memory */
    //s = shm;
    for ( s = shm, c = 'a'; c <= 'z'; c++)
    {
        *s = c;
        s++;
    }

    *s = '\0';

    /* wait until first character is changed to '*' */
    while (*shm != '*')
        sleep(1);

    return 0;
}
