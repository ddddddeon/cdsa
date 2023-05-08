#include "queue.h"

#include <stdio.h>
#include <stdlib.h>

#include "common.h"

struct QueueNode {
    int value;
    struct QueueNode *next;
    struct QueueNode *prev;
};

typedef struct QueueNode QueueNode;

struct Queue {
    QueueNode *front;
    QueueNode *back;
    int size;
};

Queue *queue_new() {
    Queue *p = malloc(sizeof(Queue));
    p->front = NULL;
    p->back = NULL;
    p->size = 0;
    return p;
}

void queue_enqueue(Queue *q, int n) {
    ABORT_IF_NULL(q);
    QueueNode *node = malloc(sizeof(QueueNode));
    node->value = n;

    if (q->size == 0) {
        node->next = NULL;
        node->prev = NULL;
        q->front = node;
    } else {
        QueueNode *old_back = q->back;
        old_back->prev = node;
        node->next = old_back;
    }
    q->back = node;
    q->size++;
}

QueueItem queue_dequeue(Queue *q) {
    ABORT_IF_NULL(q);

    QueueItem item = {.exists = false, .value = 0};

    if (q->size == 0) {
        return item;
    }

    QueueNode *old_front = q->front;

    if (q->size > 1) {
        q->front = old_front->prev;
    }

    q->front->next = NULL;
    q->size--;
    if (q->size == 0) {
        q->back = NULL;
    }

    int value = old_front->value;
    free(old_front);

    item.exists = true;
    item.value = value;
    return item;
}

int queue_size(Queue *q) {
    ABORT_IF_NULL(q);
    return q->size;
}

void queue_print(Queue *q) {
    ABORT_IF_NULL(q);
    QueueNode *curr = q->back;
    printf("[ ");
    while (curr != NULL) {
        printf("%d ", curr->value);
        curr = curr->next;
    }
    printf("]\n");
}

void queue_free(Queue **q) {
    ABORT_IF_NULL(q);
    while ((*q)->size != 0) {
        queue_dequeue(*q);
    }

    *q = NULL;
    free(*q);
}
