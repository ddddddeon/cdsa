#ifndef CDSA_ARRAY_H
#define CDSA_ARRAY_H

#include <stddef.h>

typedef struct cdsa_array cdsa_array;

cdsa_array *cdsa_array_new(size_t len);
void cdsa_array_free();
size_t cdsa_array_size(cdsa_array *c);
void cdsa_array_display(cdsa_array *c);
int cdsa_array_get(cdsa_array *c, int i);
int cdsa_array_index_of(cdsa_array *c, int n);
int cdsa_array_insert(cdsa_array *c, int n);
int cdsa_array_insert_at(cdsa_array *c, int n, int i);
int cdsa_array_update_at(cdsa_array *c, int n, int i);
int cdsa_array_delete_at(cdsa_array *c, int i);
int cdsa_array_fill(cdsa_array *c, int n);
#endif /* CDSA_ARRAY_H */
