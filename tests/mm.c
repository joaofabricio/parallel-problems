#include <assert.h>
#include <time.h>

#include "../mm.c"

void mm_exec(int m, int n, int p) {

        int **m1 = matrix_instance(p, m, 1);

	int **m2 = matrix_instance(m, n, 1);
	
	clock_t start = clock();
	int **r = mm(m1, m2, m, n);
	clock_t end = clock();
	float seconds = (float) end - start / CLOCKS_PER_SEC;
	printf("%f\n", seconds);

	int i,j;
        for (i=0; i<m; i++) {
                for (j=0; j<n; j++) {
                        assert(r[i][j] == n);
                }
        }
	
}

int main() {
	mm_exec(1000, 1000, 1000);
	return 0;
}


