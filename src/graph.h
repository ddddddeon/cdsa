#ifndef GRAPH_H
#define GRAPH_H

typedef struct Vertex Vertex;

Vertex *vertex_new(const char *value);
void vertex_connect(Vertex *v1, Vertex *v2);
void vertex_print(Vertex *v);

#endif /* !GRAPH_H */
