#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void err_sys(char *str)
{
	printf("%s\n", str);
	exit (1);
}

void nothing(int sig)
{

	if (signal(SIGQUIT, SIG_DFL) == SIG_ERR) {
		fprintf(stderr, "can't reset SIGQUIT\n");
		exit(1);
	}

}

int main ()
{
	struct sigaction sact;
	int ismember = 0, i;
	sigset_t new_set, old_set, pendmask; // signal set
	sigemptyset( &sact.sa_mask); // clear the sigaction struc mask
	sact.sa_flags = 0; // flag is set 0 to ignore option
	sact.sa_handler = nothing; // function to catch signal
	sigaction(SIGINT, &sact, NULL); // change the action for SIGINT
	sigaction(SIGQUIT, &sact, 0); // change the action for SIGQUIT
	sigemptyset( &new_set ); // clear signal sets: block all signal
	sigaddset(&new_set, SIGQUIT); // make unblock for SIGQUIT
	sigprocmask(SIG_BLOCK, &new_set, &old_set); //signal is blocked
	
	for(i = 0; i <=5 ; i++)
	{
		printf("%d\n",i);
		sleep(1);
	}
	
	printf("\n=> Checking if any signals are pending...\n");
	if (sigpending(&pendmask) < 0) {
		printf("sigpending error\n");
		exit(1);
	}
	
	ismember = sigismember(&pendmask, SIGQUIT);
	if (ismember < 0) {
		printf("sigismember error\n");
		exit(1);
	} else if (ismember == 1) {
		printf("Pending SIGQUIT found.\n");
	}
	
	printf("Unblocking the SIGQUIT signal\n");
	sigprocmask(SIG_SETMASK, &old_set, NULL); // unblocks signal
	
	for(i = 0; i <=5 ; i++)
	{
		printf("%d\n",i);
		sleep(1);
	}
	
	
	exit (0);
}
