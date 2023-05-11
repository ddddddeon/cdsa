#ifndef ARRAY_H
#define ARRAY_H

#include <stdbool.h>
#include <stddef.h>

typedef struct Array Array;

Array *array_new(size_t len);
Array *array_copy(Array *c);
void array_free(Array **c);
size_t array_size(Array *c);
size_t array_cap(Array *c);
void array_print(Array *c);
int array_avail(Array *c);
int array_get(Array *c, int i);
int array_index_of(Array *c, int n);
int array_max_value(Array *c);
bool array_has_duplicate(Array *c);
int array_insert(Array *c, int n);
int array_insert_at(Array *c, int n, int i);
int array_update_at(Array *c, int n, int i);
void array_delete_at(Array *c, int i);
int array_fill(Array *c, int n);
void array_reverse(Array *c);
void array_bubble_sort(Array *c);
void array_selection_sort(Array *c);
void array_insertion_sort(Array *c);

#endif /* ARRAY_H */
