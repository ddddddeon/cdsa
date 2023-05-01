#include <stdio.h>

#include "cdsa.h"
#include "third_party/hk/src/log.h"

int main(int argc, char* argv[]) {
    Array* a = array_new(10);
    array_insert(a, 1);
    array_insert(a, 2);
    array_insert_at(a, 3, 1);
    array_insert_at(a, 5, 0);
    array_update_at(a, 8, 1);
    array_display(a);
    printf("%d\n", array_get(a, 2));
    printf("%d\n", array_index_of(a, 8));
    array_delete_at(a, 1);
    array_delete_at(a, 2);
    array_delete_at(a, 2);
    array_delete_at(a, 2);
    array_display(a);
    printf("%zu\n", array_size(a));
    array_fill(a, 0);
    array_display(a);
    array_update_at(a, 100, 5);
    array_display(a);
    array_free(a);
}
