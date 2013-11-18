#include "../dijkstra.c"

void dijkstra_test() {

	vertex_t *a = malloc(sizeof(vertex_t));
	vertex_t *b = malloc(sizeof(vertex_t));
	vertex_t *c = malloc(sizeof(vertex_t));
	vertex_t *d = malloc(sizeof(vertex_t));
	vertex_t *e = malloc(sizeof(vertex_t));
	vertex_t *f = malloc(sizeof(vertex_t));

	a->edges = malloc(sizeof(edge_t) * 2);
	a->label = 0;
	a->n_edges = 2;
	b->edges = malloc(sizeof(edge_t) * 3);
	b->label = 1;
	b->n_edges = 3;
	c->edges = malloc(sizeof(edge_t) * 2);
	c->label = 2;
	c->n_edges = 2;
	d->edges = malloc(sizeof(edge_t) * 5);
	d->label = 3;
	d->n_edges = 5;
	e->edges = malloc(sizeof(edge_t) * 2);
	e->label = 4;
	e->n_edges = 2;
	f->edges = malloc(sizeof(edge_t) * 2);
	f->label = 5;
	f->n_edges = 2;

	(a->edges[0]).weight = 5;
	(a->edges[0]).vertex = b;
	(a->edges[1]).weight = 4;
	(a->edges[1]).vertex = d;

	(b->edges[0]).weight = 5;
	(b->edges[0]).vertex = a;
	(b->edges[1]).weight = 1;
	(b->edges[1]).vertex = c;
	(b->edges[2]).weight = 2;
	(b->edges[2]).vertex = d;

	(c->edges[0]).weight = 1;
	(c->edges[0]).vertex = b;
	(c->edges[1]).weight = 1;
	(c->edges[1]).vertex = d;

	(d->edges[0]).weight = 4;
	(d->edges[0]).vertex = a;
	(d->edges[1]).weight = 2;
	(d->edges[1]).vertex = b;
	(d->edges[2]).weight = 1;
	(d->edges[2]).vertex = c;
	(d->edges[3]).weight = 7;
	(d->edges[3]).vertex = e;
	(d->edges[4]).weight = 10;
	(d->edges[4]).vertex = f;

	(e->edges[0]).weight = 7;
	(e->edges[0]).vertex = d;
	(e->edges[1]).weight = 1;
	(e->edges[1]).vertex = f;

	(f->edges[0]).weight = 10;
	(f->edges[0]).vertex = d;
	(f->edges[1]).weight = 1;
	(f->edges[1]).vertex = e;

	vertex_t *ways = dijkstra(a, 6);

	#ifdef DEBUG
	int i;
	for (i=0; i<6; i++) {
		printf("caminho para %d: %d\n", i, ways[i].label);
	}
	#endif
}

int main() {
	dijkstra_test();
	return 0;
}
