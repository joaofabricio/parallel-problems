#include <pthread.h>

#include "utils.c"

int** res;

/***********************************
 ***************P4******************
 ***********************************/
typedef struct work_4 {
	int ac, pr, pc;
	int end;
	void* next;
} work_4;

pthread_mutex_t lock_4;
pthread_cond_t cond_4;

work_4 *list_work_4 = NULL;

void add_work_4(work_4 w) {
	w.next = NULL;
        pthread_mutex_lock(&lock_4);
	if (list_work_4 == NULL)
		list_work_4 = &w;
	else
		list_work_4->next = (void*) &w;
        list_work_4->next = (void*) &w;
	pthread_cond_signal(&cond_4);
        pthread_mutex_unlock(&lock_4);
}

work_4 remove_work_4() {
        pthread_mutex_lock(&lock_4);
	if (list_work_4 == NULL)
		pthread_cond_wait(&cond_4, &lock_4);
        work_4 w = *list_work_4;
	if (w.end == 1)
		pthread_exit(NULL);
        list_work_4 = (work_4*)list_work_4->next;
        pthread_mutex_unlock(&lock_4);
	return w;
}

void p4(void* arg) {
	while (1) {
		work_4 w = remove_work_4();
		printf("armazenando os resultados de %d, %d \n", w.pr, w.pc);
		res[w.pr][w.pc] = w.ac;
	}
}

/***********************************
 ***************P3******************
 ***********************************/
typedef struct work_3 {
	int n, pr, pc;
	int* p;
	int end;
	void* next;
} work_3;

pthread_mutex_t lock_3;
pthread_cond_t cond_3;

work_3 *list_work_3 = NULL;

void add_work_3(work_3 w) {
	w.next = NULL;
	pthread_mutex_lock(&lock_3);
	if (list_work_3 == NULL)
		list_work_3 = &w;
	else
		list_work_3->next = (void*) &w;
	list_work_3->next = (void*) &w;
	pthread_cond_signal(&cond_3);
	pthread_mutex_unlock(&lock_3);
}

work_3 remove_work_3() {
	pthread_mutex_lock(&lock_3);
	if (list_work_3 == NULL)
		pthread_cond_wait(&cond_3, &lock_3);
	work_3 *w = list_work_3;
	if (w->end == 1)
		pthread_exit(NULL);
	list_work_3 = (work_3*)list_work_3->next;
	pthread_mutex_unlock(&lock_3);
	return *w;
}

void p3(void* arg) {
	while (1) {
		int i;
		work_3 w = remove_work_3();
		int ac = 0;
		printf("somando as multiplicações de %d, %d \n", w.pr, w.pc);
		for (i=0; i<w.n; i++) {
			ac += w.p[i];
		}
		printf("soma: %d \n", ac);
		work_4 w4;
		w4.ac = ac;
		w4.pr = w.pr;
		w4.pc = w.pc;
		add_work_4(w4);
	}
	pthread_exit(NULL);
}

/***********************************
 ***************P2******************
 ***********************************/
typedef struct work_2 {
	int *r, *c;
	int n, pr, pc;
	void* next;
	int end;
} work_2;

pthread_mutex_t lock_2;

pthread_cond_t cond_2;

work_2 *list_work_2 = NULL;

void add_work_2(work_2 w) {
	w.next = NULL;
	pthread_mutex_lock(&lock_2);
	if (list_work_2 == NULL)
		list_work_2 = &w;
	else
		list_work_2->next = (void*) &w;
	pthread_cond_signal(&cond_2);
	pthread_mutex_unlock(&lock_2);
}

work_2 remove_work_2() {
	pthread_mutex_lock(&lock_2);
	if (list_work_2 == NULL)
		pthread_cond_wait(&cond_2, &lock_2);
	work_2 *w = list_work_2;
	if (w->end == 1) {
		printf("terminando thread 2\n");
		pthread_exit(NULL);
	}
	list_work_2 = (work_2*) list_work_2->next;
	pthread_mutex_unlock(&lock_2);
	return *w;
}

void p2(void* arg) {
	while (1) {
		work_2 w = remove_work_2();
		int* p = malloc(w.n * sizeof(int));
		int i;
		printf("multiplicando linha %d por coluna %d \n",w.pr, w.pc);
		for (i=0; i<w.n; i++) {
			p[i] = w.r[i] * w.c[i];
		}

		work_3 w3;
		w3.p = p;
		w3.pr = w.pr;
		w3.pc = w.pc;
		w3.n = w.n;

		add_work_3(w3);
	}
}

/***********************************
 ***************P1******************
 ***********************************/
typedef struct work_1 {
	int m, n;
	int** m1;
	int** m2;
} work_1;

work_1 w1;

void p1(void* arg) {
	int i, j, k;

	int m = w1.m;
	int n = w1.n;

	for (i=0; i<n; i++) {
		int *r;
		r = malloc(n * sizeof(int));
		r = w1.m1[i];
		int *c;
		for (k=0; k<n; k++) {
			c = malloc(n * sizeof(int));
			for (j=0; j<m; j++) {
				c[j] = w1.m2[k][j];
			}

			work_2 w;
			w.r = r;
			w.c = c;
			w.n = n;
			w.pr = i;
			w.pc = k;

			printf("inserindo linha %d, coluna %d \n", i, k);
			add_work_2(w);
		}
	}
}


int** mm(int** m1, int** m2, int m, int n) {

	res = matrix_instance(m, n, 0);

	w1.m1 = m1;
	w1.m2 = m2;
	w1.m = m;
	w1.n = n;

	int nthreads = 4;
	pthread_t threads[nthreads];

	printf("iniciando thread 3\n");
	pthread_create(&threads[3], NULL, (void*) &p4, NULL);
	printf("iniciando thread 2\n");
	pthread_create(&threads[2], NULL, (void*) &p3, NULL);
	printf("iniciando thread 1\n");
	pthread_create(&threads[1], NULL, (void*) &p2, NULL);
	printf("iniciando thread 0\n");
	pthread_create(&threads[0], NULL, (void*) &p1, NULL);

	int i;
	for (i=0; i<nthreads; i++)
		pthread_join(threads[i], NULL);

	return res;
}
