#include "utils.c"

int** mm(int** m1, int** m2, int m, int n) {

	int i, j;

	int** res = matrix_instance(m, n);	

	for (i=0; i<m; i++) {
		for (j=0; j<n; j++) {
			int k;
			for (k=0; k<m; k++) {
				res[i][j] += m1[i][k]*m2[k][j];
			}
		}
	}
	return res;
	
}

