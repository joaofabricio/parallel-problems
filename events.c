#include <pthread.h>
#include <time.h>

#include "utils.c"

#define WORK_SIZE 200

typedef struct work_t {
	int** value;
	clock_t time;
	void *next;
} work_t;

work_t *w;

pthread_mutex_t lock;

int manager_seq = 0;

void work(void* arg) {
	int** mm(int** m1, int** m2, int m, int n) {

		int i;

		int** res = matrix_instance(m, n, 0);

		for (i=0; i<m; i++) {
			int j;
			for (j=0; j<n; j++) {
				int k;
				for (k=0; k<m; k++) {
					res[i][j] += m1[i][k]*m2[k][j];
				}
			}
		}
		return res;

	}

	work_t temp;
	temp.value = mm(matrix_instance(WORK_SIZE, WORK_SIZE, 0), 
			matrix_instance(WORK_SIZE, WORK_SIZE, 0),
			WORK_SIZE,
			WORK_SIZE);
	temp.time = clock();

	pthread_mutex_lock(&lock);
	temp.next = (void*) w;
	w = &temp;
	pthread_mutex_unlock(&lock);

	pthread_exit(NULL);
}

void start_threads(int nthreads) {
	w = NULL;
	int i;
	pthread_t threads[nthreads];
	//threads = malloc(nthreads * sizeof(pthread_t));
	for (i=0; i<nthreads; i++) {
		pthread_create(&threads[i], NULL, (void *) &work, NULL);
	}
	for (i=0; i<nthreads; i++)
		pthread_join(threads[i], NULL);
}

