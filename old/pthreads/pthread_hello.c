#include <stdio.h>
#include <sys/types.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>


#define MAX_THREAD 100

typedef struct { int id; } parm;

void *hello(void *arg)
{
	parm *p = (parm *) arg;
	printf("Hello from thread %d (thread id = %lu, process PID = %d)\n",
	       p->id, pthread_self(), getpid());
	return (NULL);  /* will perform a pthread_exit() */
}

int main(int argc, char* argv[]) {
	int n,i;
	pthread_t *threads;
	parm *p;

	if (argc != 2)
	{
		printf ("Usage: %s n\n  where n is the number of threads\n",argv[0]);
		exit(1);
	}

	n = atoi(argv[1]);

	if ((n < 1) || (n > MAX_THREAD))
	{
		printf ("ERROR: The no of thread should between 1 and %d.\n",MAX_THREAD);
		exit(1);
	}

	printf("\nProcess %d starting %d threads\n", getpid(), n);
	
	threads = (pthread_t *) malloc(n*sizeof(*threads));

	p = (parm *) malloc(sizeof(parm)*n);
	/* Start up thread */

	for (i=0; i<n; i++)
	{
		p[i].id=i;
		pthread_create(&threads[i], NULL, hello, (void *)(p+i));
	}

	/* Synchronize the completion of each thread. */

	for (i=0; i<n; i++)
	{
		pthread_join(threads[i],NULL);
	}
	free(p);
	
	printf("Process %d is finished\n\n", getpid());

}
