#include "stack.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "common.h"

struct StackNode {
    int value;
    struct StackNode *next;
};

typedef struct StackNode StackNode;

struct Stack {
    StackNode *head;
    int length;
};

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

StackItem stack_pop(Stack *s) {
    ABORT_IF_NULL(s);

    StackItem item = {.exists = false, .value = 0};

    StackNode *head = s->head;
    if (head == NULL) {
        return item;
    }

    int popped = head->value;
    s->head = head->next;
    free(head);
    s->length--;

    item.exists = true;
    item.value = popped;
    return item;
}

StackItem stack_peek(Stack *s) {
    ABORT_IF_NULL(s);

    StackItem item = {.exists = false, .value = 0};

    if (s->head == NULL) {
        return item;
    }

    item.exists = true;
    item.value = s->head->value;
    return item;
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
