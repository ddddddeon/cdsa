typedef struct Queue Queue;

Queue *queue_new();
void queue_enqueue(Queue *q, int n);
int queue_dequeue(Queue *q);
void queue_print(Queue *q);
void queue_free(Queue **q);
