#include <pthread.h>
#include <time.h>

#include "utils.c"

#define WORK_SIZE 1000

typedef struct work_t {
	int value;
	int timestamp;
	void *next;
} work_t;

typedef struct message_t {
	int timestamp, new;
} message_t;

work_t *list;

message_t message;

pthread_mutex_t lock;

pthread_cond_t cond;

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
	if (w.timestamp > message.timestamp)
		message.timestamp = w.timestamp;
	message.new = 1;
	pthread_mutex_unlock(&lock);
	printf("send %d\n", w.timestamp);
	pthread_cond_broadcast(&cond);
}

int max(int a, int b) {
	return a>b? a : b;
}

int has_message() {
	return message.new;
}

void work(void* arg) {
	int rx = 0;
	message.new = 0;
	while (has_work()) {
		
		work_t temp;
		temp.value = get_value();

		temp.timestamp = rx;
		send(temp);
		rx++;

		//receive
		pthread_mutex_lock(&lock);
		if (!has_message()) 
			pthread_cond_wait(&cond, &lock);
		rx = max(rx, message.timestamp);
		message.new = 0;
		pthread_mutex_unlock(&lock);
		rx++;
	}
	pthread_exit(NULL);
}

void start_threads(int nthreads) {
	list = NULL;
	int i;
	pthread_t threads[nthreads];
	for (i=0; i<nthreads; i++) {
		pthread_create(&threads[i], NULL, (void *) &work, (void *) &i);
	}
	for (i=0; i<nthreads; i++)
		pthread_join(threads[i], NULL);
}
