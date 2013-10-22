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

message_t* message;

pthread_mutex_t lock;

pthread_cond_t cond;

int nthreads;

int manager_seq = 0;

int get_value() {
	return 1111;
}

int has_work() {
	return 1;
}

void send(work_t w) {
//fazer uma lista para cada thread
//caixa de mensagens para cada
//gerente de mensagens
	int i;
	pthread_mutex_lock(&lock);
	w.next = (void*) list;
	list = &w;
	for(i=0; i<nthreads; i++) {
		if (w.timestamp > message[i].timestamp)
			message[i].timestamp = w.timestamp;
		message[i].new = 1;
	}
	pthread_mutex_unlock(&lock);
	printf("send %d\n", w.timestamp);
	pthread_cond_broadcast(&cond);
}

int max(int a, int b) {
	return a>b? a : b;
}

int has_message(int id) {
	return message[id].new;
}

void work(void* arg) {
	int *p_id = (int*) arg;
	int id = *p_id;
	int rx = 0;
	while (has_work()) {
		
		//receive
		pthread_mutex_lock(&lock);
		if (!has_message(id)) 
			pthread_cond_wait(&cond, &lock);
		message[id].new = 0;
		pthread_mutex_unlock(&lock);
		rx = max(rx, message[id].timestamp);
		rx++;

		work_t temp;
		temp.value = get_value();

		temp.timestamp = rx;
		send(temp);
		rx++;

	}
	pthread_exit(NULL);
}

void start_threads(int n_threads) {
	nthreads = n_threads;
	list = NULL;
	int i;
	message = malloc(nthreads*sizeof(message_t));
	pthread_t threads[nthreads];
	for (i=0; i<nthreads; i++) {
		pthread_create(&threads[i], NULL, (void *) &work, (void *) &i);
	}
	work_t w;
	w.timestamp = 0;
	w.value = 111;
	send(w);
	for (i=0; i<nthreads; i++)
		pthread_join(threads[i], NULL);
}
