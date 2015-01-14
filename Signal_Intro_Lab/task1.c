/* Charlie Rusk
 * Lab 7: task1.c
 * Alarm using sigaction, Modify alarm.c to use sigaction rather than the old
 * fashioned signal methodology
 */

#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

static int alarm_fired = 0;

void ding(int signum)
{
	alarm_fired = 1;
	printf("DING\n");
}

void handler(int signum){
  	
	alarm_fired = 1;
}

int main()
{
	pid_t pid;
	struct sigaction action;
	action.sa_handler = &ding;
	printf("alarm application starting\n");
	sigset_t mask;
	
	sigaction(SIGALRM, &action, NULL);
	sigemptyset(&action.sa_mask);
	action.sa_flags =0;
	pid = fork();
	
	switch(pid) {
	case -1:
		/* Failure */
		perror("fork failed");
		exit(1);
	case 0:
		/* child */
		sleep(5);
		printf("child %d killed\n", getpid());
		kill(getpid(), SIGALRM);
		exit(0);
	}
	
	/* Parent Process */
	printf("waiting for alarm to go off\n");
	
	pause();
	
	printf("done\n");
	exit(0);
}
