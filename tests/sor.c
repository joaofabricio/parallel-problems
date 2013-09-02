#include <assert.h>

#include "../sor.c"

void sor_test() {
	int* m[3];// = {{1,1,1}, {1,1,1}, {1,1,1}};
	int i, j;
	
	for(i=0; i<3; i++) {
		m[i] = malloc(sizeof(int)*3);
		for (j=0;j<3;j++)
			m[i][j] =1;
	}

	int expected[3][3];// = {{1,1,1}, {1,2,1},{1,1,1}};
	for(i=0; i<3; i++) 
                for (j=0;j<3;j++)
                        expected[i][j] =1;
	expected[1][1] = 2;

	int** ret = sor(m, 3, 3, 2);

	for(i=0; i<3; i++) {
		for (j=0; j<3; j++) {
			assert(ret[i][j] == expected[i][j]);
		}
	}
}

int main () {
	sor_test();
	return 0;
}
