#include <assert.h>
#include <stdio.h>

#include "../merge-sort.c"

void merge_sort_test() {
        int arr[] = { 3, 1, 5, 2, 10, 8, 8, 15};
        int ret = *(int*) merge_sort(arr, 0, 8);

	int i;
        for (i=0; i<7; i++) {
                assert((&ret)[i] <= (&ret)[i+1]);
	}
}

void merge_test() {
	
	int arr1[] = {51, 10, 5, 40};
	int arr2[] = {3, 8, 5, 1};

	int arr =  *(int*) merge(arr1, 4, arr2, 4);

	int i;
        for (i=0; i<7; i++) {
                assert((&arr)[i] <= (&arr)[i+1]);
	}
}

int main() {
	merge_test();
	merge_sort_test();
	return 0;
}

