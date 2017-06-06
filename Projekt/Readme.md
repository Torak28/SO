# Notatki

### Odpalenie wątku

```cpp
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


long long sum = 0;

//Wątek do wyliczanie sumy od  do N
void* sum_runner(void* arg){
	long long *limit_ptr = (long long*) arg;
	long long limit = *limit_ptr;

	for (long long i = 0; i <= limit; i++){
		sum += i;
	}

	//Jak zwrócić odp? W zmiennej globalnej
	pthread_exit(0);
}

int main(int argc, char const **argv)
{
	if (argc < 2){
		printf("Usage: %s <num 1>, <num 2> ... <num n>\n", argv[0] );	
		exit(-1);
	}
	long long limit = atoll(argv[1]);

	// Atrybuty
	pthread_attr_t attr;
	pthread_attr_init(&attr);

	//Thread ID
	pthread_t tid;


	pthread_create(&tid, &attr, sum_runner, &limit);

	//Czekamy na watek
	pthread_join(tid, NULL);
	printf("Sum is %lld\n", sum);

	return 0;
}
```

Jeden wątek z zasobem globalnym.

### We have to go deeper

```c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


struct sum_runner_struct{
	long long limit;
	long long answer;
};

//Wątek do wyliczanie sumy od  do N
void* sum_runner(void* arg){
	struct sum_runner_struct *arg_struct = (struct sum_runner_struct*) arg;

	long long sum = 0;
	for (long long i = 0; i <= arg_struct->limit; i++){
		sum += i;
	}

	arg_struct->answer = sum;
	pthread_exit(0);
}

int main(int argc, char const **argv)
{
	if (argc < 2){
		printf("Usage: %s <num 1>, <num 2> ... <num n>\n", argv[0] );	
		exit(-1);
	}
	int num_args = argc - 1;
	
	struct sum_runner_struct args[num_args];

	//Thread ID
	pthread_t tids[num_args];

	for (int i = 0; i < num_args; ++i){
		args[i].limit = atoll(argv[i + 1]);
		// Atrybuty
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_create(&tids[i], &attr, sum_runner, &args[i]);
	}
	
	for (int i = 0; i < num_args; ++i){
		//Czekamy na watek
		pthread_join(tids[i], NULL);
		printf("Sum for thread %d is %lld\n", i, args[i].answer);
	}

	return 0;
}
```

Troszke lepiej bo mam juz całą tablice wątków, ale nadal jest problem bo każdy wątek czeka na następny. TO jest wątek pierwszy czeka na drugi itp. itd.



