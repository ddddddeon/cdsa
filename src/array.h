#ifndef ARRAY_H
#define ARRAY_H

#include <stddef.h>

typedef struct Array Array;

Array *array_new(size_t len);
void array_free(Array **c);
size_t array_size(Array *c);
void array_display(Array *c);
int array_get(Array *c, int i);
int array_index_of(Array *c, int n);
int array_insert(Array *c, int n);
int array_insert_at(Array *c, int n, int i);
int array_update_at(Array *c, int n, int i);
void array_delete_at(Array *c, int i);
int array_fill(Array *c, int n);

#endif /* ARRAY_H */
