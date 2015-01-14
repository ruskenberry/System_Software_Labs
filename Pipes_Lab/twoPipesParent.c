#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{	
	const int WRITE_END = 1, READ_END = 0;
	int data_processed, status;
	int file_pipes[2], fd_pipe[2];
	const char some_data [] = "Hi There, Kiddo";
	char buffer[BUFSIZ + 1];
	
	pid_t fork_result;
	
	memset(buffer, '\0', sizeof(buffer));
	
	pipe(fd_pipe);
	
	if (pipe(file_pipes) == 0)
	{
		fork_result = fork();
		if (fork_result == (pid_t) - 1)
		{
			fprintf(stderr, "Fork failure");
			exit (EXIT_FAILURE);
		}
		
		if (fork_result == 0) //child
		{
			close(file_pipes[WRITE_END]);
			close(fd_pipe[READ_END]);
			
			sprintf (buffer, "%d %d", file_pipes[READ_END], fd_pipe[WRITE_END]);
			(void)execl("twoPipesChild", "twoPipesChild", buffer, (char *)0);
			exit (EXIT_FAILURE);
		}
		else //parent
		{
			
			close(file_pipes[READ_END]);
			close(fd_pipe[WRITE_END]);
			
			data_processed = write (file_pipes[WRITE_END], some_data, strlen(some_data));
			printf("%d - In Parent wrote %d bytes\n", getpid(), data_processed);
			
			wait(&status);
			
			data_processed = read(fd_pipe[READ_END], buffer, BUFSIZ);
			printf("%d - In Parent read %d bytes: %s\n", getpid(), data_processed, buffer);
		}
	}
	exit(EXIT_SUCCESS);
}
