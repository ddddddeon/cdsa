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
    LinkedList *adjacent_vertices;
};

typedef struct Vertex Vertex;

Vertex *vertex_new(const char *value) {
    Vertex *v = malloc(sizeof(Vertex));
    v->value = value;
    v->n_edges = 0;
    v->adjacent_vertices = linked_list_new();
    return v;
}

void vertex_connect(Vertex *v1, Vertex *v2) {
    ABORT_IF_NULL(v1);
    ABORT_IF_NULL(v2);

    // undirected graph; connections go both ways
    linked_list_insert_end(v1->adjacent_vertices, v2);
    linked_list_insert_end(v2->adjacent_vertices, v1);
}

void vertex_print(Vertex *v) {
    ABORT_IF_NULL(v);
    printf("%s -> [ ", v->value);
    for (int i = 0; i < linked_list_size(v->adjacent_vertices); i++) {
        // terrible; linked_list_get has to iterate to i each time
        Vertex *a = (Vertex *)linked_list_get(v->adjacent_vertices, i);
        printf("%s ", a->value);
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

    for (int i = 0; i < linked_list_size(v->adjacent_vertices); i++) {
        vertex_dfs_traverse((Vertex *)linked_list_get(v->adjacent_vertices, i),
                            seen);
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

        for (int i = 0; i < linked_list_size(curr->adjacent_vertices); i++) {
            Vertex *vertex =
                (Vertex *)linked_list_get(curr->adjacent_vertices, i);

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

    for (int i = 0; i < linked_list_size((*v)->adjacent_vertices); i++) {
        Vertex *vertex = (Vertex *)linked_list_get((*v)->adjacent_vertices, i);
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
