#include <assert.h>
#include <stdio.h>

#include "../events.c"

void events_test() {
	int nthreads = 4;

	start_threads(nthreads);

	int i;
	for(i=0; i<WORK_SIZE; i++) {
		//assert(work_vector[i] == WORK_SIZE);
	}
	
	work_t *temp = w;
	while (temp != NULL) {
		printf("time: %f\n", (float) temp->time);
		temp = temp->next;
	}
}

int main() {
	events_test();
	return 0;
}
