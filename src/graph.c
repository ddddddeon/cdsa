#include <limits.h>
#include <malloc.h>
#include <stdbool.h>

#include "common.h"
#include "hash_map.h"
#include "linked_list.h"
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

void dijkstra(Vertex *v, Vertex *dest) {
    HashMap *shortest = hash_map_new();
    HashMap *shortest_previous = hash_map_new();
    HashMap *unvisited = hash_map_new();
    HashMap *visited = hash_map_new();

    // 1 -visit the starting vertex, making it "current"
    Vertex *curr = v;
    hash_map_set(shortest, curr->value, edge_new(curr, 0));

    // TODO change
    while (curr != NULL) {
        hash_map_set(visited, curr->value, (void *)1);
        hash_map_delete(&unvisited, curr->value);

        /*         printf("visited:\n"); */
        /*         hash_map_print_ptr(visited); */
        /*         printf("unvisited:\n"); */
        /*         hash_map_print_ptr(unvisited); */

        // 2 -check weights from current to each adjacent vertex
        Queue *adjacent_vertices = hash_map_to_queue(curr->adjacent_vertices);
        while (queue_size(adjacent_vertices) > 0) {
            Edge *edge = (Edge *)queue_dequeue(adjacent_vertices);
            hash_map_set(unvisited, edge->vertex->value, (void *)edge);

            Edge *shortest_so_far =
                (Edge *)hash_map_get(shortest, edge->vertex->value);

            // 3 - if the weight to and adjacent vertex is less than the weight
            // in the shortest_weights, or it isn't in the hashmap yet at all:
            //   - update shortest_weights_table
            //   - update shortest_previous_vertex with k = adjacent vertex, v =
            //     current vertex
            if (shortest_so_far == NULL ||
                edge->weight < shortest_so_far->weight) {
                hash_map_set(shortest, edge->vertex->value, (void *)edge);
                hash_map_set(shortest_previous, edge->vertex->value,
                             (void *)curr);
            }
        }
        queue_free(&adjacent_vertices);

        // 4 - visit whichever univisited vertex has the lowest weight from the
        // starting vertex, making it the current
        Queue *unvisited_vertices = hash_map_to_queue(unvisited);
        int min_weight_from_start = INT_MAX;

        if (queue_size(unvisited_vertices) == 0) {
            curr = NULL;
            continue;
        }

        while (queue_size(unvisited_vertices) > 0) {
            Edge *e = (Edge *)queue_dequeue(unvisited_vertices);
            Edge *from_start = hash_map_get(shortest, e->vertex->value);

            if (from_start != NULL &&
                from_start->weight < min_weight_from_start) {
                min_weight_from_start = from_start->weight;
                curr = e->vertex;
                continue;
            }
        }
        queue_free(&unvisited_vertices);

        curr = NULL;
        // repeat 2-4 until we've visited every vertex
    }

    // build the shortest path
    Queue *shortest_path = queue_new();
    Vertex *current = dest;

    while (current != v && current != NULL) {
        queue_enqueue(shortest_path, (void *)current->value);
        current = (Vertex *)hash_map_get(shortest_previous, current->value);
    }

    while (queue_size(shortest_path) > 0) {
        const char *dequeued = (const char *)queue_dequeue(shortest_path);
        printf("%s\n", dequeued);
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
