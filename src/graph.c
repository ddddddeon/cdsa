#include <malloc.h>

#define MAX_EDGES 256

struct Vertex {
    const char *value;
    int n_edges;
    struct Vertex *adjacent_vertices[MAX_EDGES];
};

typedef struct Vertex Vertex;

Vertex *vertex_new(const char *value) {
    Vertex *v = malloc(sizeof(Vertex));
    v->value = value;
    v->n_edges = 0;
    return v;
}

void vertex_connect(Vertex *v1, Vertex *v2) {
    if (v1->n_edges >= MAX_EDGES || v2->n_edges >= MAX_EDGES) {
        printf("cannot connect vertices! max edge limit reached\n");
        return;
    }

    v1->adjacent_vertices[v1->n_edges++] = v2;
    v2->adjacent_vertices[v2->n_edges++] = v1;
}

void vertex_print(Vertex *v) {
    printf("%s -> [ ", v->value);
    for (int i = 0; i < v->n_edges; i++) {
        printf("%s, ", v->adjacent_vertices[i]->value);
    }
    printf("]\n");
}
