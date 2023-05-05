#include <stdbool.h>
typedef struct Queue Queue;

typedef struct {
    bool exists;
    int value;
} QueueItem;

Queue *queue_new();
void queue_enqueue(Queue *q, int n);
QueueItem queue_dequeue(Queue *q);
int queue_length(Queue *q);
void queue_print(Queue *q);
void queue_free(Queue **q);
