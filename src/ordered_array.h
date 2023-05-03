#ifndef ORDERED_ARRAY_H
#define ORDERED_ARRAY_H

#include <stddef.h>

typedef struct OrderedArray OrderedArray;

OrderedArray *ordered_array_new(size_t len);
void ordered_array_free(OrderedArray **c);
size_t ordered_array_size(OrderedArray *c);
void ordered_array_print(OrderedArray *c);
int ordered_array_get(OrderedArray *c, int i);
int ordered_array_index_of(OrderedArray *c, int n);
int ordered_array_insert(OrderedArray *c, int n);
void ordered_array_delete_at(OrderedArray *c, int i);

#endif /* ORDERED_ORDERED_ARRAY_H */
