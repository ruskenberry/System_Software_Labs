#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAXLINE 256

void err_sys(char *str)
{
	printf("%s\n", str);
	exit (1);
}

int main(void)
{
	int n, fd1[2], fd2[2];
	pid_t pid;
	char line[MAXLINE];
	
	if (pipe(fd1) < 0 || pipe(fd2) < 0) /* create two pipe */
		err_sys("pipe error");
		
	if ( (pid = fork()) < 0) /* create a child */
		err_sys("fork error");
		
	else if (pid > 0) /* for parent */
	{ 
		close(fd1[0]); /* since the first pipe is used for std output */
		close(fd2[1]); /* since the second pipe is used for std input */
		//puts("Please enter country > ");
		while (fgets(line, MAXLINE, stdin) != NULL) /* read from standard input */
		{
			//printf("Numbers\n");
			n = strlen(line);
			puts("Enter two numbers to send to child:");
			if (write(fd1[1], line, n) != n) /* write to the first pipe */
				err_sys("write error to pipe");
				
			if ( (n = read(fd2[0], line, MAXLINE)) < 0) /* read from the second pipe */
				err_sys("read error from pipe");
			
			if (n == 0)
			{
				err_sys("child closed pipe");
				break;
			}
			
			line[n] = '\0'; /* null terminate */
			
			if (fputs(line, stdout) == EOF) /* write to standard output*/
				err_sys("fputs error");
		} 
	
		if (ferror(stdin))
			err_sys("fgets error on stdin");
	
		exit(0);
	}
	else
	{ 
		/* child */
		close(fd1[1]); /*since first pipe is used for std input */
		close(fd2[0]); /*since second pipe is used for std output */
		if (execl("child", (char *) 0) < 0)
			err_sys("execl error");
	}
}
