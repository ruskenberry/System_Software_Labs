#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#define MAXLINE 256

void err_sys(char *str)
{
	printf("%s\n", str);
	exit (1);
}

int main()
{
	int n, fd[2], status;
	
	pid_t pid;
	
	char line[MAXLINE];
	
	if(pipe(fd) < 0)
		err_sys("Error making pipe");
		
	if ( (pid = fork()) < 0 )
		err_sys("Error forking");
	
	else if (pid > 0) //parent
	{
		close(fd[0]);
		printf("Enter two integers: ");
		scanf("%c", line);
		
		write(fd[1], line, MAXLINE);
 		wait(NULL);
	}
	else // child	
	{
			
		close(fd[1]);
		printf("Inside Child");
		read(fd[0], line, MAXLINE);
		write(1, line, MAXLINE);		
	}
	
	exit (0);
}
