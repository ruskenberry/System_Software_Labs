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
	pid_t pid, ID;
	char *message;
	int n, slp, status;
	
	printf("fork program starting\n");
	pid = fork();
	switch(pid)
	{
		case -1:
			err_sys("fork failed");
			break;
		case 0:
			message = "This is the child (message)";
			if(execl("child",message,argv[1],argv[3], NULL) <0)
				printf("exec Error\n");

			break;
		default:
			ID = getpid();
			message = "This is the parent";
			n=atoi(argv[2]);
			slp=atoi(argv[4]);
			pid = getpid();
			break;
	}
	wait(&status);
	for(; n > 0; n--)
	{		
		printf("%s PID: %d\n", message, ID);
		
		sleep(slp);
	}
	
	exit (0);
}
