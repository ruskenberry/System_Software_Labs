#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;

char * mygetenv(char * var)
{
	char **p = environ;
	while(*p != NULL)
	{
	if(strncmp(*p,var,strlen(var)) == 0)
	{
		*p += strlen(var) + 1;
		return *p;
	}
	*p++;
	}
	return "NOT FOUND";
}
int main(int argc, char*argv[])
{
	printf("%s\n", mygetenv(argv[1]));
	return 0;
}
