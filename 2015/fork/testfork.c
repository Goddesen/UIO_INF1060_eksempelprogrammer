#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define WHOAMI "/usr/bin/whoami"

int main(void)
{
	pid_t pid, n;
	int status = 0;

	pid = fork();
	if (pid == -1) {
		printf("Failure\n");
		exit(EXIT_FAILURE);
	}

	if (pid != 0) {
		/* Parent */
		printf("parent PID=%d, child PID=%d\n",
				(int)getpid(), (int)pid);
		printf("parent going to sleep (wait)...\n");

		n = wait(&status);

		printf("returned child PID=%d, status=%d\n",
				(int)n, WEXITSTATUS(status));
		return EXIT_SUCCESS;
	}

	/* Child */
	printf("child PID=%d\n", (int)getpid());
	printf("executing %s:\n", WHOAMI);

	// The following two functions perform the same task
	//execve(WHOAMI, NULL, NULL);
	system(WHOAMI);

	return 145;
}
