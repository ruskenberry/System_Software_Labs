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
	int n, int1, int2, count = 0;
	char line[MAXLINE]; /* read a string from stdin */
	//printf("Child\n");
	puts("press enter to continue:");
	while ( (n = read(STDIN_FILENO, line, MAXLINE)) > 0)
	{
		
		
		line[n] = '\0'; /* clear end of string character */
		/* chose first two string as two integer and save as integers*/
		if (sscanf(line, "%d%d", &int1, &int2) == 2)
		{
			/* write the result of sum to buffer*/
			sprintf(line, "%d\n", int1 + int2);
			n = strlen(line);
			/* write content of buffer to standard output*/
			if (write(STDOUT_FILENO, line, n) != n)
				err_sys("write error");
		}
		else
		/* if first two string are not integer */
		{
			if (write(STDOUT_FILENO, "invalid args\n", 13) != 13)
				err_sys("write error");
		}
		count ++;
		if(count == 1)
			break;
	}
		exit(0);
}
