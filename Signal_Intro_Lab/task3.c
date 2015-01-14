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

int main ()
{
	pid_t pid;
	int status, fdWrite1, nread, fd2;
	char buf[128];


	if ((fdWrite1 = open("foo.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR)) < 0)
			err_sys("Error opening / creating foo.txt");
			
	printf("Fork program starting\n");
	pid = fork();
	if(pid < 0)
		err_sys("Fork failed");
		
	if(pid == 0) // This is the child process
	{
		if(write(fdWrite1, "Hi, Mom", 7) != 7)
			err_sys("Write to foo error");
		
		
		//printf("\nEnd of child process ID: %d\n", getpid());
		//printf("\nFile descriptor in child : %d", fdWrite1);
		exit(0);
		
	}
	else		// this is the parent process
	{
		wait(&status);
		//printf("\nFile descriptor in parent: %d", fdWrite1);
		lseek(fdWrite1,0,SEEK_SET);
		
		nread = read(fdWrite1, buf,8);
		
		//printf("\nFile buf read : %d", nread);
		write(1,"My son said ", 13);
		write(1, buf, nread);
		//write(1, buf, 7);
		
		//printf("\nEnd of parent process ID: %d\n", getpid());
	}
	
	//close(fdRead);
	close(fdWrite1);
	//close(fdWrite2);
	
	exit (0);
}
