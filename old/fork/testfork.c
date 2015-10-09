#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void)
{
  pid_t pid, n;
  int status = 0;
  
  if ((pid = fork()) == -1) {printf("Failure\n"); exit(1);}
  
  if (pid != 0) { /* Parent */
    printf("parent PID=%d, child PID = %d\n", (int)getpid(), (int)pid);
    printf("parent going to sleep (wait)...\n");
    n = wait(&status);
    printf("returned child PID = %d, status = %d\n", (int)n, WEXITSTATUS(status));
    return 0;
  } else { /*Child */
    printf("child PID=%d\n", (int)getpid());
    printf("executing /store/bin/whoami:\n");
    //execve("/store/bin/whoami", NULL, NULL);
    system("/store/bin/whoami");
    return 145;
  }
}
