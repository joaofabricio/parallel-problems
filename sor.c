#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define NTHREADS 5

int lines, columns;

int** m;

pthread_barrier_t barrier;

typedef struct work_t {
	int** m;
	int** ret;
	int lines, columns, id;
} work_t;

void worker(void *w) {

	work_t *work = (work_t*) w;

	int id = work->id;

	#ifdef DEBUG
	printf("initializing thread %d\n", id);
	#endif

	int begin_col, end_col;
	int begin_lin, end_lin;

	begin_lin = work->lines/NTHREADS * id;
	end_lin = work->lines/NTHREADS * (id+1);
	begin_col = work->columns/NTHREADS * id;
	end_col = work->columns/NTHREADS * (id+1);

	int i, j;
	for (i=begin_lin+1; i<end_lin-1; i++) {
		for (j=begin_col+1; j<end_col-1; j++) {
			int up = work->m[i-1][j];
			int down = work->m[i+1][j];
			int left = work->m[i][j-1];
			int right = work->m[i][j+1];

			work->ret[i][j] = (up+down+left+right)/4;
		}
	}
	pthread_barrier_wait(&barrier);
}

int** sor(int** m, int l, int c, int n) {

	int** ret = malloc(l * sizeof(int));

	int i, j, k;

	for (i=0; i<l; i++) {
		ret[i] = malloc(c * sizeof(int));
		for (j=0; j<c; j++) {
			ret[i] = m[i];
		}
	}

	pthread_t threads[NTHREADS];

	for (i=0; i<n; i++) {
		pthread_barrier_init(&barrier, NULL, NTHREADS);
		for (k=0; k<NTHREADS; k++) {
			work_t *work = malloc(sizeof(work_t));
			work->id = k;
			work->lines = l;
			work->columns = c;
			work->m = m;
			work->ret = ret;
			pthread_create(&threads[k], NULL, (void*) worker, (void*) work);
		}
		for (k=0; k<NTHREADS; k++)
			pthread_join(threads[k], NULL);
		pthread_barrier_destroy(&barrier);
	}



	return ret;
}

