#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct edge_t {
	int weight;
	void* vertex;
} edge_t;

typedef struct vertex_t {
	int n_edges;
	int label;
	edge_t* edges;
	void *next;
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

	if (work->weight >= distances[v->label]) {
		pthread_exit(NULL);
	}

	pthread_mutex_lock(&locks[v->label]);
	distances[v->label] = work->weight;
	ways[v->label] = *(work->source);
	pthread_mutex_unlock(&locks[v->label]);


	pthread_t sons[v->n_edges];
	int i;
	for (i=0; i<v->n_edges; i++) {
		edge_t edge = v->edges[i];

		if (work->source != edge.vertex) {
			work_t *next = malloc(sizeof(work_t));
			next->weight = work->weight + edge.weight;
			next->vertex = edge.vertex;
			next->source = work->source;

			pthread_create(sons[i], NULL, (void*) process_vertex, (void*) next);
		}

	}
	for (i=0; i<v->n_edges; i++)
		pthread_join(sons[i], NULL);
}

vertex_t* dijkstra(vertex_t *source, int n_vertices) {

	distances = malloc(n_vertices * sizeof(int));
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

