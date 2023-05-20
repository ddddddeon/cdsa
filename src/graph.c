#include <malloc.h>
#include <stdbool.h>

#include "common.h"
#include "hash_map.h"
#include "queue.h"

#define MAX_VISITED 2048

struct Vertex {
    const char *value;
    int n_edges;
    HashMap *adjacent_vertices;
};

typedef struct Vertex Vertex;

typedef struct {
    Vertex *vertex;
    int weight;
} Edge;

Edge *edge_new(Vertex *vertex, int weight) {
    Edge *p = malloc(sizeof(Edge));
    p->vertex = vertex;
    p->weight = weight;
    return p;
}

Vertex *vertex_new(const char *value) {
    Vertex *v = malloc(sizeof(Vertex));
    v->value = value;
    v->n_edges = 0;
    v->adjacent_vertices = hash_map_new();
    return v;
}

void vertex_connect(Vertex *v1, Vertex *v2, int weight) {
    ABORT_IF_NULL(v1);
    ABORT_IF_NULL(v2);

    Edge *edge_forward = edge_new(v2, weight);
    Edge *edge_back = edge_new(v1, weight);
    // undirected graph; connections go both ways

    hash_map_set(v1->adjacent_vertices, v2->value, edge_forward);
    hash_map_set(v2->adjacent_vertices, v1->value, edge_back);
}

void vertex_print(Vertex *v) {
    ABORT_IF_NULL(v);
    printf("%s -> [ ", v->value);

    Queue *q = hash_map_to_queue(v->adjacent_vertices);

    while (queue_size(q) > 0) {
        Edge *edge = (Edge *)queue_dequeue(q);
        Vertex *vertex = edge->vertex;
        printf("%s (%d) ", vertex->value, edge->weight);
    }

    printf("]\n");
}

void vertex_dfs_traverse(Vertex *v, HashMap *seen) {
    ABORT_IF_NULL(v);
    const char *seen_value = "seen";

    if (hash_map_get(seen, v->value) != NULL) {
        return;
    }

    hash_map_set(seen, v->value, (void *)seen_value);

    printf("%s\n", v->value);

    Queue *q = hash_map_to_queue(v->adjacent_vertices);

    while (queue_size(q) > 0) {
        Edge *edge = (Edge *)queue_dequeue(q);
        Vertex *vertex = edge->vertex;
        vertex_dfs_traverse(vertex, seen);
    }
}

void vertex_dfs_print(Vertex *v) {
    ABORT_IF_NULL(v);
    HashMap *seen = hash_map_new();
    vertex_dfs_traverse(v, seen);
}

void vertex_bfs_print(Vertex *v) {
    ABORT_IF_NULL(v);
    HashMap *seen = hash_map_new();
    Queue *q = queue_new();

    const char *seen_value = "seen";
    hash_map_set(seen, v->value, (void *)seen_value);
    queue_enqueue(q, v);

    while (queue_size(q) > 0) {
        Vertex *curr = queue_dequeue(q);
        printf("%s\n", curr->value);

        Queue *items = hash_map_to_queue(curr->adjacent_vertices);

        while (queue_size(items) > 0) {
            Edge *edge = (Edge *)queue_dequeue(items);
            Vertex *vertex = edge->vertex;
            if (hash_map_get(seen, vertex->value) == NULL) {
                hash_map_set(seen, vertex->value, (void *)seen_value);
                queue_enqueue(q, vertex);
            }
        }
    }
}

void vertex_dfs_free(Vertex **v, HashMap *seen) {
    ABORT_IF_NULL(v);

    const char *seen_value = "seen";

    if (hash_map_get(seen, (*v)->value) != NULL) {
        return;
    }

    hash_map_set(seen, (*v)->value, (void *)seen_value);

    Queue *q = hash_map_to_queue((*v)->adjacent_vertices);

    while (queue_size(q) > 0) {
        Edge *edge = (Edge *)queue_dequeue(q);
        Vertex *vertex = edge->vertex;
        vertex_dfs_free(&vertex, seen);
    }

    free(*v);
    *v = NULL;
}

void vertex_free(Vertex **v) {
    ABORT_IF_NULL(v);
    HashMap *seen = hash_map_new();
    vertex_dfs_free(v, seen);
}
