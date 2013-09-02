#include "utils.c"

int** mm(int** m1, int** m2, int m, int n) {

	int i, j;

	int** res = matrix_instance(m, n);	

	for (i=0; i<m; i++) {
		for (j=0; j<n; j++) {
			res[i][j] = soma(m1, m2, i, j, m, n);	
		}
	}
	return res;
	
}

int soma(int** m1, int** m2, int i, int j, int m, int n) {
	int k, l, soma = 0;
	for (k=0; k<m; k++) {
		for (l=0; l<n; l++) {
			soma += m1[i][k]*m2[j][l];
		}
	}
	return soma;
}
