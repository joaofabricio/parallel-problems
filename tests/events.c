#include <assert.h>

#include "../events.c"

void events_test() {
	int nthreads = 4;

	start_threads(nthreads);

	int i;
	for(i=0; i<WORK_SIZE; i++) {
		assert(work_vector[i] == WORK_SIZE);
	}
}

int main() {
	events_test();
	return 0;
}
