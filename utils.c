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

int* vector_instance_random(unsigned int l) {
	unsigned int i;
	int* ret = malloc(l * sizeof(int));
	srand(time(NULL));

        for (i=0; i<l; i++) {
		ret[i] = rand() % 2000;
        }
	return ret;
}

int* vector_instance(int l, int value) {
	int i;
	int *ret = malloc(l * sizeof(int));

	for (i=0; i<l; i++) {
		ret[i] = value;
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
