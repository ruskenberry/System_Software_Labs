#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
	int data_processed;
	int file_pipes[2];
	const char some_data [] ="123";
	//char buffer [BUFSIZ +1];
	char *buffer;
	
	const int READ_END = 0;
	const int WRITE_END = 1;
	
	//memset(buffer, '\0', sizeof(some_data));
	buffer = (char*) malloc(sizeof(some_data));	
	if (pipe(file_pipes) == 0)
	{
		data_processed = write(file_pipes[WRITE_END], some_data, strlen(some_data));
	
		printf("Wrote %d bytes\n", data_processed);
		
		buffer = (char*) malloc (sizeof(data_processed));
		
		strcpy(buffer,some_data);
	
		data_processed = read(file_pipes[READ_END], buffer, sizeof(buffer));
	
		printf("Read %d btyes: %s\n", data_processed, buffer);
	
		exit(EXIT_SUCCESS);
	}
	
	exit(EXIT_SUCCESS);
}
