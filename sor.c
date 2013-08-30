#include <stdlib.h>

int** sor(int** m, int l, int c) {

	int** ret = malloc(l * sizeof(int));

	int i, j;
	
	for (i=0; i<l; i++) {
		ret[i] = malloc(c * sizeof(int));
		for (j=0; j<c; j++) {
			ret[i] = m[i];
		}
	}

	for (i=1; i<l-1; i++) {
		for (j=1; j<c-1; j++) {
			int norte = m[i-1][j];
			int sul = m[i+1][j];
			int leste = m[i][j+1];
			int oeste = m[i][j-1];

			ret[i][j] = norte+sul+leste+oeste;
		}
	}

	return ret;

}
