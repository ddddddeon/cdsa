#ifndef STACK_H
#define STACK_H

typedef struct Stack Stack;

Stack *stack_new();
void stack_push(Stack *s, int n);
int stack_pop(Stack *s);
int stack_peek(Stack *s);
void stack_print(Stack *s);
void stack_free(Stack **s);

#endif /* STACK_H */
