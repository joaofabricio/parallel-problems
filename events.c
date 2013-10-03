#include <pthread.h>
#include <time.h>

#include "utils.c"

#define WORK_SIZE 1000

typedef struct work_t {
	int value;
	int timestamp;
	void *next;
} work_t;

work_t *list;

work_t message;

pthread_mutex_t lock;

int manager_seq = 0;

int get_value() {
	return 1111;
}

int has_work() {
	return 1;
}

void send(work_t w) {
	pthread_mutex_lock(&lock);
	w.next = (void*) list;
	list = &w;
	message = w;
	pthread_mutex_unlock(&lock);
	printf("send %d\n", w.timestamp);
}

int max(int a, int b) {
	return a>b? a : b;
}

void work(void* arg) {
	int rx = 0;
	while (has_work()) {

		//receive
		rx = max(rx, message.timestamp);
		rx++;
		
		work_t temp;
		temp.value = get_value();

		temp.timestamp = rx;
		send(temp);
		rx++;

	}
	pthread_exit(NULL);
}

void start_threads(int nthreads) {
	list = NULL;
	int i;
	pthread_t threads[nthreads];
	for (i=0; i<nthreads; i++) {
		pthread_create(&threads[i], NULL, (void *) &work, NULL);
	}
	for (i=0; i<nthreads; i++)
		pthread_join(threads[i], NULL);
}
