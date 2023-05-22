#ifndef GRAPH_H
#define GRAPH_H

typedef struct Vertex Vertex;

Vertex *vertex_new(const char *value);
void vertex_connect(Vertex *v1, Vertex *v2, int weight);
void vertex_print(Vertex *v);
void vertex_dfs_print(Vertex *v);
void vertex_bfs_print(Vertex *v);
void vertex_free(Vertex **v);
void dijkstra(Vertex *v, Vertex *dest);

#endif /* !GRAPH_H */
