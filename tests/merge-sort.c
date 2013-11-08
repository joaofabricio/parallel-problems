#include <assert.h>
#include <stdio.h>

#include "../merge-sort.c"
#include "../utils.c"

void merge_sort_test() {
	unsigned int size = 1000000;
        int *arr = vector_instance_random(size);//{ 3, 1, 5, 2, 10, 8, 8, 15};
        int *ret = merge_sort(arr, 0, size);

	unsigned int i;
        for (i=0; i<size-1; i++) {
                assert(ret[i] <= ret[i+1]);
	}
}

void merge_test() {
	
	int arr1[] = { 1,2,5,6,8,10,12,15,16};
	int arr2[] = { 6,7,9,20,50,65,221,350,1234};

	int* arr =  merge(arr1, 9, arr2, 9);

	int i;
        for (i=0; i<18; i++) {
		assert(arr[i] <= arr[i+1]);
		//printf("%d\n",arr[i]);
	}
}

int main() {
	merge_test();
	merge_sort_test();
	return 0;
}

