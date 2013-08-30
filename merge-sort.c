#include <stdlib.h>

#include "utils.c"

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

int* merge_sort(int* arr, int b, int e) {
	if (b >= e-1) {
		int* v = malloc(sizeof(int));
		v[0] = arr[b];
		return v;
	} else {

		int div = b+((e-b)/2);

		int* arr1 = malloc((div-b)*sizeof(int));
		int* arr2 = malloc((e-div)*sizeof(int));

		arr1 = merge_sort(arr, b, div);
		arr2 = merge_sort(arr, div, e);

		return merge(arr1, div-b, arr2, (e-div));
	}
}
