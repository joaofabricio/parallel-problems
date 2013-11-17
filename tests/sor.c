#include <assert.h>

#include "../sor.c"
#include "../utils.c"

void sor_test() {

	int** m = matrix_instance(50, 50, 1);

	int** ret = sor(m, 50, 50, 5);

	int i,j;
	for(i=0; i<3; i++) {
		for (j=0; j<3; j++) {
			assert(ret[i][j] == 1);
		}
	}
}

int main () {
	sor_test();
	return 0;
}
