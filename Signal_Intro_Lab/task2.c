#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void handler(int sig)
{
	printf("SIGNAL RECIEVED: %d\n", sig);
	(void) signal(SIGINT,SIG_DFL);
}
int
main() {

	struct sigaction action;
	action.sa_handler = handler;
	sigemptyset(&action.sa_mask);
	action.sa_flags = 0;
	
	sigaction(SIGINT, &action, 0);

	while(1)
	{
		printf("HELLO WORLD!\n");
		sleep(1);
	}
}

