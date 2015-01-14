#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int args, char* argv[])
{
	int data_processed, status;
	int file_pipes[2];
	const char some_data = argv[1];
	char *buffer;
	
	buffer = (char*) malloc(sizeof(some_data));
	pid_t fork_result;
	
	memset(buffer, '\0', sizeof(buffer));
	
	if (pipe(file_pipes) == 0)
	{
		fork_result = fork();
		if (fork_result == (pid_t)-1)
		{
			fprintf(stderr, "Fork failure");
			exit (EXIT_FAILURE);
		}
		
		if (fork_result == 0) //child
		{
			close(file_pipes[1]);
			sprintf (buffer, "%d", file_pipes[0]);
			(void)execl("pipe4", "pipe4", buffer, (char *)0);
			exit (EXIT_FAILURE);
		}
		else //parent
		{
			
			close(file_pipes[0]);
			
			data_processed = write (file_pipes[1], some_data, strlen(some_data));
			wait(&status);
			printf("Back in the parent of pipe3\n");
			printf("%d - wrote %d bytes\n", getpid(), data_processed);
		}
	}
	exit(EXIT_SUCCESS);
}
