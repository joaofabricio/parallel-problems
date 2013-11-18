#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "utils.c"

#define INFINITE 9999999

typedef struct edge_t {
	int weight;
	void* vertex;
} edge_t;

typedef struct vertex_t {
	int n_edges;
	int label;
	edge_t* edges;
} vertex_t;

typedef struct work_t {
	vertex_t *source, *vertex;
	int weight;
} work_t;

vertex_t *vertices;

int *distances;
vertex_t *ways;
pthread_mutex_t *locks;

void process_vertex(void* w) {
	work_t *work = (work_t*) w;
	vertex_t *v = work->vertex;

	#ifdef DEBUG
	if (work->source != NULL) {
		printf("source: %d, atual: %d, peso: %d, min: %d \n", work->source->label, v->label, work->weight, distances[v->label]);
		fflush(stdout);
	}
	#endif

	pthread_mutex_lock(&locks[v->label]);
	if (work->weight >= distances[v->label]) {
		#ifdef DEBUG
		printf("-----dead source: %d, atual: %d, peso: %d \n", work->source->label, v->label, work->weight);
		#endif
		pthread_mutex_unlock(&locks[v->label]);
		pthread_exit(NULL);
	}

	distances[v->label] = work->weight;
	ways[v->label] = work->source!=NULL? *(work->source): ways[v->label];
	pthread_mutex_unlock(&locks[v->label]);


	pthread_t sons[v->n_edges];
	int i;
	for (i=0; i<v->n_edges; i++) {
		edge_t edge = v->edges[i];

		if (work->source != edge.vertex) {
			work_t *next = malloc(sizeof(work_t));
			next->weight = work->weight + edge.weight;
			next->vertex = edge.vertex;
			next->source = work->vertex;

			pthread_create(&sons[i], NULL, (void*) process_vertex, (void*) next);
		}

	}
	for (i=0; i<v->n_edges; i++) {
		if (work->source != v->edges[i].vertex) {
			#ifdef DEBUG
			printf(">>>>join atual: %d, dest: %d<<<<<<<<<\n", v->label, ((vertex_t*)v->edges[i].vertex)->label);
			#endif
			pthread_join(sons[i], NULL);
			#ifdef DEBUG
			printf("***>finalizando atual: %d, dest: %d\n", v->label, ((vertex_t*)v->edges[i].vertex)->label);
			#endif
		}
	}
	pthread_exit(NULL);
}

vertex_t* dijkstra(vertex_t *source, int n_vertices) {

	distances = malloc(n_vertices * sizeof(int));
	int i;
	for (i=0; i<n_vertices; i++)
		distances[i] = INFINITE;

	ways = malloc(n_vertices * sizeof(vertex_t));
	locks = malloc(n_vertices * sizeof(pthread_mutex_t));

	pthread_t root;
	work_t *work = malloc(sizeof(work_t));
	work->weight = 0;
	work->vertex = source;
	work->source = NULL;
	pthread_create(&root, NULL, (void*)process_vertex, (void*)work);

	pthread_join(root, NULL);
	
	return ways;
}

