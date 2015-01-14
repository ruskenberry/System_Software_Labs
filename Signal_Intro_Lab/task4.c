#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <ctype.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>

void err_sys(char *str)
{
	printf("%s\n", str);
	exit (1);
}

static void sig_usr(int); // signal handler


int main ()
{
	pid_t pid[2], pid2, parent_pid;
	int i, status;
	
	for (i = 0; i < 2; i++)
	{
		if((pid[i] = fork()) < 0)
			err_sys("Error Forking");
		
	}
	
	if(pid[0] == 0) // child 1
	{
		kill(getppid(), SIGUSR1);
		//signal(SIGUSR1, sig_usr);
		exit(0);
	}
	else if (pid[1] == 0) // child 2
	{
		sleep(1);
		kill(getppid(), SIGUSR2);
		exit(0);
	}
	else // parent process
	{
		
		signal(SIGUSR1, sig_usr);
		signal(SIGUSR2, sig_usr);
		
		pause();
		pause();
	
		exit(0);
	}
}

static void sig_usr(int signo)
{
	if (signo == SIGUSR1)
		printf("Hi Honey! Anything wrong?\n");
		
	if (signo == SIGUSR2)
		printf("Do you make trouble again?\n");
	
}
