#include <pthread.h>

#define WORK_SIZE 100
int work_vector[WORK_SIZE];

pthread_mutex_t lock;

int manager_seq = 0;

int request_number() {
	pthread_mutex_lock(&lock);
	int num = manager_seq++;
	pthread_mutex_unlock(&lock);
	return num;
}

void work(void* arg) {
	int pass;
	pass = request_number();
	while (pass < WORK_SIZE) {
		work_vector[pass] = WORK_SIZE;
		pass = request_number();
	}
	pthread_exit(NULL);
}

void start_threads(int nthreads) {
	int i;
	pthread_t threads[nthreads];
	//threads = malloc(nthreads * sizeof(pthread_t));
	for (i=0; i<nthreads; i++) {
		pthread_create(&threads[i], NULL, (void *) &work, NULL);
	}
	for (i=0; i<nthreads; i++)
		pthread_join(threads[i], NULL);
}

