#include <stdio.h>
#include <stdlib.h>

int** matrix_instance(int l, int c, int value) {
	int i, j;
	int** ret = malloc(l * sizeof(int*));

        for (i=0; i<l; i++) {
                ret[i] = malloc(c * sizeof(int));
		for (j=0; j<c; j++) {
			ret[i][j] = value;
		}
        }
	return ret;
}


void print_array(int* arr, int l) {
        int i;
        for (i=0; i<l; i++) {
                printf("%d ", arr[i]);
        }
        printf("\n");
}
