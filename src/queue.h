#include <stdbool.h>
typedef struct Queue Queue;

Queue *queue_new();
void queue_enqueue(Queue *q, void *item);
void *queue_dequeue(Queue *q);
int queue_size(Queue *q);
void queue_print(Queue *q);
void queue_free(Queue **q);
