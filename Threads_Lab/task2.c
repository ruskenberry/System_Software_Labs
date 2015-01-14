#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
int array[20];
pthread_t threads[3];

void err_sys(char *str)
{
	printf("%s\n", str);
	exit (1);
}

void *threadOne(void *arg)
{
	printf("Inside thread One\n");
	int i, numbers;
	printf("How many test scores to you want to enter? ");
	scanf("%d", &numbers);
	printf("Please enter a series of test scores (MAX of 20):\n");
	for(i = 0; i < numbers; i++)
	{
		pthread_mutex_lock (&mutex1);
		scanf("%d", &array[i]);
		pthread_mutex_unlock (&mutex1);
	}
	
	pthread_exit(0);
	
}

void *threadTwo(void *arg)
{
	int tc;
	printf("Inside thread two!\n");
	if((tc = pthread_join(threads[0], NULL)) != 0)
		err_sys("Error joining Thread One");
	
	int average = 0, medium, i = 0;
	
	while(array[i] != '\0')
	{
		average += array[i];
		i++;
	}

	average = average / i;
	printf("The average is: %d\nThe medium is: %d\n", average, array[i/2]);
	
	pthread_exit(0);

}

void *threadThree(void *arg)
{
	int tc;
	printf("Inside thread three!\n");
	if((tc = pthread_join(threads[1], NULL)) != 0)
		err_sys("Error joining Thread One");
	
	int min = array[0], max = array[0], i = 0;
	
	while(array[i] != '\0')
	{
		if(min > array[i])
			min = array[i];
			
		if(max < array [i])
			max = array[i];
			i++;
	}

	printf("The min value is: %d\nThe max value is: %d\n", min, max);

	pthread_exit(0);
}

int main ()
{
	int tc;
		
	printf("In the main making threads\n");
	if((tc = pthread_create(&threads[0], NULL, threadOne, NULL) != 0))
		err_sys("Error making Thread One");

	if((tc = pthread_create(&threads[1], NULL, threadTwo, NULL) != 0))
		err_sys("Error making Thread Two");
	
	if((tc = pthread_create(&threads[2], NULL, threadThree, NULL) != 0))
		err_sys("Error making Thread Three");

	if((tc = pthread_join(threads[2], NULL)) != 0)
		err_sys("Error joining Thread Three");
	
	tc = 0;
	printf("The array were filled with the values of:\n");
	while( array[tc] != '\0')
	{
		printf("%i ", array[tc]);
		array[tc] = 0;
		tc++;
	}
	
	printf("\nThe array is now clear\n");	
	exit (0);
}
