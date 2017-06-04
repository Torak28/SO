#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//Wątek do wyliczanie sumy od  do N
void* sum_runner(void* arg){
	long long *limit_ptr = (long long*) arg;
	long long limit = *limit_ptr;
	free(arg);

	long long sum = 0;
	for (long long i = 0; i <= limit; i++){
		sum += i;
	}

	//Dynamiczna alokacja na propsie
	long long *answer = malloc(sizeof(*answer));
	*answer = sum;

	//Jak zwrócić odp? W zmiennej globalnej
	pthread_exit(answer);
}

int main(int argc, char const **argv)
{
	if (argc < 2){
		printf("Usage: %s <num 1>, <num 2> ... <num n>\n", argv[0] );	
		exit(-1);
	}
	long long *limit = malloc(sizeof(*limit));
	*limit = atoll(argv[1]);

	// Atrybuty
	pthread_attr_t attr;
	pthread_attr_init(&attr);

	//Thread ID
	pthread_t tid;


	pthread_create(&tid, &attr, sum_runner, limit);


	long long *result;
	//Czekamy na watek
	pthread_join(tid, (void**)&result);
	printf("Sum is %lld\n", *result);
	free(result);

	return 0;
}