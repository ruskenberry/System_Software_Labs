#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

void err_sys(char *str)
{
	printf("%s\n", str);
	exit (1);
}

void *sumCalc(void *arg)
{
	int intVar = atoi(arg);
	int sum = 0, i = 0;
	while (i <= intVar)
	{
		sum += i;
		i++;
	}
	printf("In sum thread which is :%i\n", sum);
	
}

void *factCalc(void *arg)
{
	int var = atoi(arg);
	int fact = 1, i = 1;
	while (i <= var)
	{
		fact *= i;
		i++;
	}
	printf("In fact thread which is :%i\n", fact);

}

int main (int argc, char *argv [])
{
	if(argc > 2 || argc < 1)
		err_sys("Invalid arguments");
		
	pthread_t threads[2];
	
	int i, tc;
	
	printf("In the main making threads\n");
	if((tc = pthread_create(&threads[0], NULL, sumCalc, argv[1])) != 0)
		err_sys("Error making Sum Thread");
		
	if((tc = pthread_create(&threads[1], NULL, factCalc, argv[1])) != 0)
		err_sys("Error making Factorial Thread");
		
	if((tc = pthread_join(threads[0], NULL)) != 0)
		err_sys("Error joining Sum Thread");
	
	if((tc = pthread_join(threads[1], NULL)) != 0)
		err_sys("Error joining Fact Thread");
	
	exit (0);
}
