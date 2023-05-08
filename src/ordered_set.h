#ifndef ORDERED_SET_H
#define ORDERED_SET_H

#include <stddef.h>

typedef struct OrderedSet OrderedSet;

OrderedSet *ordered_set_new(size_t len);
OrderedSet *ordered_set_copy(OrderedSet *c);
void ordered_set_free(OrderedSet **c);
size_t ordered_set_size(OrderedSet *c);
size_t ordered_set_cap(OrderedSet *c);
void ordered_set_print(OrderedSet *c);
int ordered_set_get(OrderedSet *c, int i);
int ordered_set_index_of(OrderedSet *c, int n);
int ordered_set_insert(OrderedSet *c, int n);
void ordered_set_delete(OrderedSet *c, int n);
void ordered_set_delete_at(OrderedSet *c, int i);

#endif /* ORDERED_ORDERED_SET_H */
