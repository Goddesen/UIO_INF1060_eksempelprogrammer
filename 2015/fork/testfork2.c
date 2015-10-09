#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

int main(void)
{
    pid_t pid, i, j, product;

    pid = fork();
    if (pid == -1)
    {
        printf("Failure\n");
        exit(1);
    }

    if (pid != 0) /* Parent */
    {
        printf("parent PID=%d, child PID = %d\n", (int) getpid(), (int) pid);
        printf("parent going to sleep...\n");

        sleep(1);

        kill(pid, SIGKILL);

        printf("killed child PID = %d\n", (int) pid);
        return 0;

    }
    else /* Child */
    {
        printf("child PID=%d\n", (int) getpid());

        i = 0;
        printf("Linje %d: ", i);
        while (1) {
            i++;      

            product = 1;
            for (j = 1 ; j <= 100 ; j++)
            {
                product *= j;
            }


            printf("#");
            if ((i % 60) == 0)
            {
                printf("\nLinje %d: ", i);
            }

        }
        exit(0); /* Will never be executed */
    }
}
