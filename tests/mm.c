#include <assert.h>

#include "../mm.c"

void mm_test() {
	int m = 2, n = 4;
	int **m1, **m2, **e;

	m1 = malloc(2 * sizeof(int*));
	m1[0] = malloc(m * sizeof(int));
	m1[1] = malloc(m * sizeof(int));
	m1[0][0] = 5;
	m1[0][1] = 2;
	m1[1][0] = 3;
	m1[1][1] = 2;

	m2 = malloc(m * sizeof(int*));
	m2[0] = malloc(n * sizeof(int));
	m2[1] = malloc(n * sizeof(int));
	m2[0][0] = 0;
	m2[0][1] = 5;
	m2[0][2] = 1;
	m2[0][3] = 6;
	m2[1][0] = 2;
	m2[1][1] = -1;
	m2[1][2] = 4;
	m2[1][3] = -3;

	e = malloc(m * sizeof(int*));
	e[0] = malloc(n * sizeof(int));
	e[1] = malloc(n * sizeof(int));
	e[0][0] = 4;
	e[0][1] = 23;
	e[0][2] = 13;
	e[0][3] = 24;
	e[1][0] = 4;
	e[1][1] = 13;
	e[1][2] = 11;
	e[1][3] = 12;

	int** mat = mm(m1, m2, m, n);
	int i,j;
	for (i=0; i<m; i++) {
		for (j=0; j<2; j++) {
			assert(mat[i][j] == e[i][j]);
		}
	}
}

int main() {
	mm_test();
	return 0;
}
