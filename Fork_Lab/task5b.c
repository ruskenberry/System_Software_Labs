#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <ctype.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

void err_sys(char *str)
{
	printf("%s\n", str);
	exit (1);
}

int main (int argc, char *argv[])
{
	pid_t child_pid, parent_pid, pid;
	int nbyte, fdRead, fdWrite1, fdWrite2, status;
	char Ach;
	
	if((fdRead = open(argv[1], O_RDONLY)) < 0)
		err_sys("Error opening file");
	
	printf("Fork program starting\n");
	pid = fork();
	if(pid < 0)
		err_sys("Fork failed");
		
	if(pid == 0) // This is the child process
	{
		
		if ((fdWrite1 = open("childWriteb.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR)) < 0)
			err_sys("Error opening / creating childWrite.txt");
		
		while((nbyte= read(fdRead, &Ach, 1) ==1))
		{
			//printf("Running the child\n");
			if(!isdigit(Ach))
				if(write(fdWrite1, &Ach, 1) < 0)
					err_sys("Write Error in Child");
		}
		printf("\nEnd of child process ID: %d\n", getpid());
	}
	else		// this is the parent process
	{
		wait(&status);
		if(lseek(fdRead,0,SEEK_SET) < 0)
			err_sys("Error seeking");
			
		if ((fdWrite2 = open("parentWriteb.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR)) < 0)
			err_sys("Error opening / creating parentWrite.txt");

		while((nbyte= read(fdRead, &Ach, 1) ==1))
		{
			//printf("Running the parent\n");
			if(isdigit(Ach))
				if(write(fdWrite2, &Ach, 1) < 0)
					err_sys("Write Error in Parent");
		}
		
		printf("\nEnd of parent process ID: %d\n", getpid());
	}
	
	close(fdRead);
	close(fdWrite1);
	close(fdWrite2);
	
	exit (0);
}
