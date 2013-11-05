#include <stdlib.h>
#include <pthread.h>

typedef struct task_t {
	int *arr;
	int begin, end;
	void *next;
} task_t;

int* merge(int* arr1, int l1, int* arr2, int l2) {
        int i, i1, i2;
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
	int begin = task->begin;
	int end = task->end;

	if (begin < end-1) {

		int div = begin + ((end-begin)/2);

		pthread_t t1, t2;
		task_t *task_1 = malloc(sizeof(task_t));
		task_1->arr = arr;
		task_1->begin = begin;
		task_1->end = div;
		//int* arr1 = merge_manager((void*) task_1);
		pthread_create(&t1, NULL, (void*) &merge_manager, (void*) task_1);

		task_t *task_2 = malloc(sizeof(task_t));
		task_2->arr = arr;
		task_2->begin = div;
		task_2->end = end;
		//int* arr2 = merge_manager((void*) task_2);
		pthread_create(&t2, NULL, (void*) &merge_manager, (void*) task_2);

		pthread_join(t1, NULL);
		pthread_join(t2, NULL);

		task->arr =  merge(task_1->arr, div-begin, task_2->arr, end-div);
		//return merged;
		//pthread_create(t1, work)
		//return merge(arr1, div-task.begin, arr2, (task.end-div));
	}

}


int* merge_sort(int* arr, int b, int e) {
	task_t *task = malloc(sizeof(task_t));
	task->begin = b;
	task->end = e;
	task->arr = arr;
	pthread_t t;
	pthread_create(&t, NULL, (void*) &merge_manager, (void*) task);
	pthread_join(t, NULL);
	return task->arr;
}
