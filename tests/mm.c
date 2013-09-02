#include <assert.h>

#include "../mm.c"

void mm_test() {
	int *m1[2], *m2[2], *exp[2];
	int i, j;
	for (i=0; i<2; i++) {
		m1[i] = malloc(2*sizeof(int));
		m2[i] = malloc(2*sizeof(int));
		exp[i] = malloc(2*sizeof(int));
		for (j=0; j<2; j++) {
			m1[i][j] = m2 [i][j] = 1;
			exp[i][j] = 2;
		}
	}

	int** m = mm(m1, m2, 2, 2);

	for (i=0; i<2; i++) {
		for (j=0; j<2; j++) {
			assert(m[i][j] == exp[i][j]);
		}
	}
}

int main() {
	mm_test();
	return 0;
}
