#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define MAX_LEVEL 4

pthread_mutex_t lock_pairs;

typedef struct task_t {
	int *arr;
	unsigned int begin, end;
	int level;
} task_t;

int* merge(int* arr1, unsigned int l1, int* arr2, unsigned int l2) {
        unsigned int i, i1, i2;
        i1 = i2 = 0;
        int* ret = malloc((l1+l2)*sizeof(int));
        for (i=0; i<(l1+l2); i++) {
                if (i2 >= l2 || (arr1[i1] < arr2[i2] && i1 < l1)) {
                        ret[i] = arr1[i1];
                        i1++;
                } else {
                        ret[i] = arr2[i2];
                        i2++;
                }
        }
        return ret;
}

void merge_manager(void* task_arg) {
	task_t *task = (task_t *) task_arg;
	int* arr = task->arr;
	unsigned int begin = task->begin;
	unsigned int end = task->end;
	//print_array(arr, end-begin);

	if (begin < end-1) {

		unsigned int div = begin + round((end-begin)/2);
		#ifdef DEBUG
		printf("begin: %d, end: %d, div: %d\n", begin, end, div);
		fflush(stdout);
		#endif

		pthread_t t1, t2;
		task_t *task_1 = malloc(sizeof(task_t));
		task_1->arr = arr;
		task_1->begin = begin;
		task_1->end = div;
		task_1->level = task->level+1;
		//merge_manager((void*) task_1);
		//pthread_create(&t1, NULL, (void*) &merge_manager, (void*) task_1);

                task_t *task_2 = malloc(sizeof(task_t));
                task_2->arr = arr;
                task_2->begin = div;
                task_2->end = end;
		task_2->level = task->level+1;
                //merge_manager((void*) task_2);
                //pthread_create(&t2, NULL, (void*) &merge_manager, (void*) task_2);

                //pthread_join(t1, NULL);
                //pthread_join(t2, NULL);

	//	printf("retorno t1: ");
	//	print_array(task_1->arr, task_1->end-task_1->begin);
	//	fflush(stdout);

	//	printf("retorno t2: ");
	//	print_array(task_2->arr, task_2->end-task_2->begin);
	//	fflush(stdout);

		if (task->level < MAX_LEVEL) {
			pthread_create(&t1, NULL, (void*) &merge_manager, (void*) task_1);
			pthread_create(&t2, NULL, (void*) &merge_manager, (void*) task_2);

			pthread_join(t1, NULL);
			pthread_join(t2, NULL);
		} else {
			merge_manager((void*) task_1);
			merge_manager((void*) task_2);
		}


		task->arr =  merge(task_1->arr, div-begin, task_2->arr, end-div);
//		print_array(task->arr, end-begin);

		//return merged;
		//pthread_create(t1, work)
		//return merge(arr1, div-task.begin, arr2, (task.end-div));
	} else {
		int* array = malloc(sizeof(int));
		array[0] = task->arr[begin];
		task->arr = array;
	}

}


int* merge_sort(int* arr, unsigned int b, unsigned int e) {
	task_t *task = malloc(sizeof(task_t));
	task->begin = b;
	task->end = e;
	task->arr = arr;
	task->level = 0;
	pthread_t t;
	pthread_create(&t, NULL, (void*) &merge_manager, (void*) task);
	pthread_join(t, NULL);
	return task->arr;
}
