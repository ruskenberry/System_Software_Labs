#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void err_sys(char *str)
{
	printf("%s\n", str);
	exit (1);
}

int main (int argc, char *argv[])
{
	pid_t pid, ID;
	char *message;
	int n, slp;
	
	printf("fork program starting\n");
	pid = fork();
	switch(pid)
	{
		case -1:
			err_sys("fork failed");
			break;
		case 0:
			ID = getpid();
			message = "This is the child";
			n=atoi(argv[1]);
			slp=atoi(argv[3]);
			break;
		default:
			ID = getpid();
			message = "This is the parent";
			n=atoi(argv[2]);
			slp=atoi(argv[4]);
			break;
	}
	
	for(; n > 0; n--)
	{
		printf("ID is : %d ", ID);
		puts(message);
		sleep(slp);
	}
	
	exit (0);
}
