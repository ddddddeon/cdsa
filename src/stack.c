#include <stdio.h>
#include <stdlib.h>

#include "common.h"

struct StackNode {
    int value;
    struct StackNode *next;
};

typedef struct StackNode StackNode;

typedef struct {
    StackNode *head;
    int length;
} Stack;

Stack *stack_new() {
    Stack *p = malloc(sizeof(Stack));
    p->head = NULL;
    p->length = 0;
    return p;
}
void stack_push(Stack *s, int n) {
    ABORT_IF_NULL(s);
    StackNode *node = malloc(sizeof(StackNode));
    node->value = n;

    if (s->head == NULL) {
        node->next = NULL;
        s->head = node;
    } else {
        StackNode *head = s->head;
        node->next = head;
        s->head = node;
    }
    s->length++;
}

int stack_pop(Stack *s) {
    ABORT_IF_NULL(s);
    StackNode *head = s->head;
    if (head == NULL) {
        return -1;
    }

    int popped = head->value;
    s->head = head->next;
    free(head);
    s->length--;
    return popped;
}
int stack_peek(Stack *s) {
    ABORT_IF_NULL(s);
    return s->head->value;
}

void stack_print(Stack *s) {
    ABORT_IF_NULL(s);
    StackNode *curr = s->head;

    printf("[ ");
    while (curr != NULL) {
        printf("%d ", curr->value);
        curr = curr->next;
    }
    printf("]\n");
}

int stack_length(Stack *s) {
    ABORT_IF_NULL(s);
    return s->length;
}

void stack_free(Stack **s) {
    ABORT_IF_NULL(*s);
    while ((*s)->length != 0) {
        stack_pop(*s);
    }

    (*s)->head = NULL;
    free(*s);
    *s = NULL;
}
