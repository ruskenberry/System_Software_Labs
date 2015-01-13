#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

void err_sys(char *str)
{
	printf("%s\n", str);
	exit (1);
}

int main (int argc, char *argv[])
{
	pid_t child_pid;
	char *message;
	int n, slp, status;
	int exit_code;
	
	printf("This is the Child.c Program\n");
	
	message = argv[0];
	n = atoi(argv[1]);
	slp = atoi(argv[2]);
	
	exit_code = 37;
	//printf("hello");
	child_pid = getpid();
	//printf("hello");
	for(; n > 0; n--)
	{
		printf("%s in Child.c PID: %d\n", message, child_pid);
		sleep(slp);
	}
	printf("The called program has ended and is giving the exit code: %d\n",exit_code);
	exit (exit_code);
}
