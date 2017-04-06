#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

static void sigusr1(int signo) {
    fprintf(stderr, "Process %d got SIGCHLD signal, forking..\n", getpid());
    pid_t p2 = fork();
    if (p2 != 0)
    {
        fprintf(stderr, "p1 process id is %d\n", getpid());
        wait(NULL); // wait for immediate child
    }
    else
    {   // child
        pid_t p3 = fork();
        if (p3 != 0) 
        {
            fprintf(stderr, "p2 process id is %d\n", getpid());
        }
        else
        {   // grandchild
            fprintf(stderr, "p3 process id is %d\n", getpid());
        }
        exit(0);  // both child and grandchild terminate normally

    }
}

int main()
{
    fprintf(stderr, "Running main process as PID=%d\n", getpid());
    if (sigaction(SIGUSR1, &(struct sigaction){.sa_handler = sigusr1}, NULL) < 0)
    	return 1;

    for (;;) 
        pause(); // and hang waiting for signals

}
