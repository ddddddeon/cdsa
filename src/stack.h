#ifndef STACK_H
#define STACK_H

#include <stdbool.h>

typedef struct Stack Stack;

typedef struct {
    bool exists;
    int value;
} StackItem;

Stack *stack_new();
void stack_push(Stack *s, int n);
StackItem stack_pop(Stack *s);
StackItem stack_peek(Stack *s);
void stack_print(Stack *s);
void stack_free(Stack **s);

#endif /* STACK_H */
