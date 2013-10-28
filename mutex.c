#include <stdio.h>
#include <pthread.h>

pthread_cond_t *cond_token;
pthread_mutex_t lock_token;
pthread_mutex_t *lock_work;
pthread_cond_t *cond_work;
int *interest;
int token;
int nthreads;

void receive_token(int id) {
	if (token == id) {
		return;
	} else {
		pthread_mutex_lock(&lock_token);
		pthread_cond_wait(&cond_token[id], &lock_token);
		pthread_mutex_unlock(&lock_token);
	}
}

void manager(void* ident) {
	int *p_id = (int *) ident;
	int id = *p_id;

	while (1) {
		receive_token(id);

		if (interest[id]) {
			pthread_mutex_lock(&lock_work[id]);
			pthread_cond_signal(&cond_work[id]);
			pthread_cond_wait(&cond_work[id], &lock_work[id]);
			pthread_mutex_unlock(&lock_work[id]);
		}
		pthread_mutex_lock(&lock_token);
		token = (token+1) % nthreads;
		pthread_cond_signal(&cond_token[token]);
		pthread_mutex_unlock(&lock_token);
	}
}

void executor(void* ident) {
	int *p_id = (int *) ident;
	int id = *p_id;

	while (1) {
		interest[id] = 1;

		pthread_mutex_lock(&lock_work[id]);
		pthread_cond_wait(&cond_work[id], &lock_work[id]);
		pthread_mutex_unlock(&lock_work[id]);

		//critical region
		#ifdef DEBUG
		printf("executando %d \n", id);
		fflush(stdout);
		#endif
		sleep(1);

		interest[id] = 0;
		pthread_cond_signal(&cond_work[id]);

		//non-critical region
	}
}

void mutex(int n_threads) {
	nthreads = n_threads;

	pthread_t threads[nthreads];
	pthread_t helpers[nthreads];

	cond_work = malloc(nthreads * sizeof(pthread_cond_t));
	lock_work = malloc(nthreads * sizeof(pthread_mutex_t));
	cond_token = malloc(nthreads * sizeof(pthread_cond_t));

	interest = malloc(nthreads * sizeof(int));

	token = 0;
	int i;

	for (i=0; i<nthreads; i++) {
		pthread_create(&threads[i], NULL, (void *) &executor, (void *) &i);
		pthread_create(&helpers[i], NULL, (void *) &manager, (void *) &i);
	}

	for (i=0; i<nthreads; i++)
		pthread_join(threads[i], NULL);
}

