#include "cdsa.h"

#include <stdio.h>

int main(int argc, char* argv[]) {
    cdsa_array *a = cdsa_array_new(10);
    cdsa_array_insert(a, 1);
    cdsa_array_insert(a, 2);
    cdsa_array_insert_at(a, 3, 1);
    cdsa_array_insert_at(a, 5, 0);
    cdsa_array_update_at(a, 8, 1);
    cdsa_array_delete_at(a, 1);
    cdsa_array_delete_at(a, 2);
    cdsa_array_delete_at(a, 2);
    cdsa_array_delete_at(a, 2);
    cdsa_array_display(a);
    printf("%zu\n", cdsa_array_size(a));
    cdsa_array_fill(a, 0);
    cdsa_array_display(a);
    cdsa_array_update_at(a, 100, 5);
    cdsa_array_display(a);
    cdsa_array_free(a);
}
