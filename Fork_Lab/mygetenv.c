#include <stdlib.h>
#include <string.h>
#include <stdio.h>

extern char **environ;

void err_sys(char *str)
{
	printf("%s\n", str);
	exit (1);
}

char* mygetenv(char* str)
{	
	char *user = str;
	char **env = environ;
	char envIndex;
	int i = 0;
	
	while (*env != NULL)
	{
		envIndex = env[0];
		while( envIndex != '=')
		{
			envIndex = *env[0]++;
			i++;
		}
	char *envName = (char*) malloc(i+1);
	strncpy(envName, *env -i, i-1);
	if(strcmp(user, envName) == 0)
		{
		char* envVar = (char*) malloc((strlen(*env)) + 1);
		strncpy(envVar, *env, strlen(*env));
		printf("%s\n", envVar);
		return envVar;
		}
	i = 0;
	env++;
	}
	err_sys("Error");
}

int main(int argc, char* argv[])
{
	char *userPath = argv[1];
	mygetenv(userPath);
	exit (0);
}

