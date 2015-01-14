#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main (int argc, char *argv[])
{
	int data_processed;
	char buffer[BUFSIZ + 1];
	int file_descriptor, child_write;
	
	memset(buffer, '\0', sizeof(buffer));
	sscanf(argv[1], "%d %d", &file_descriptor, &child_write);
	data_processed = read(file_descriptor, buffer, BUFSIZ);
	
	printf("%d - In Child read %d bytes: %s\n", getpid(), data_processed, buffer);
	
	data_processed = write(child_write, "Hi, Mom", 8);
	printf("%d - In Child write %d bytes\n", getpid(), data_processed);
	
	exit(EXIT_SUCCESS);
}
