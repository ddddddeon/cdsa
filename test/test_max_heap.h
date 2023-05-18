#ifndef TEST_MAX_HEAP_H
#define TEST_MAX_HEAP_H

#include <check.h>

#include "../src/max_heap.h"
#include "test.h"

START_TEST(test_max_heap_new) {
    TEST_INFO;
    MaxHeap *h = max_heap_new(32);

    ck_assert_ptr_ne(h, NULL);

    max_heap_free(&h);
    ck_assert_ptr_eq(h, NULL);
}
END_TEST

START_TEST(test_max_heap_insert) {
    TEST_INFO;

    MaxHeap *h = max_heap_new(32);
    max_heap_insert(h, 10);
    max_heap_insert(h, 5);

    /*
               10
             5

     */

    ck_assert_int_eq(max_heap_top(h), 10);
    ck_assert_int_eq(max_heap_bottom(h), 5);

    max_heap_insert(h, 3);

    /*
            10
          5    3
    */

    max_heap_insert(h, 20);

    /*
            10
          5    3
        20


            10
          20   3
        5


            20
          10   3
        5
    */

    ck_assert_int_eq(max_heap_top(h), 20);
    ck_assert_int_eq(max_heap_bottom(h), 5);

    max_heap_insert(h, 2);
    ck_assert_int_eq(max_heap_bottom(h), 2);

    max_heap_free(&h);
}
END_TEST

START_TEST(test_max_heap_delete) {
    TEST_INFO;

    MaxHeap *h = max_heap_new(32);
    max_heap_insert(h, 10);
    max_heap_insert(h, 5);
    max_heap_insert(h, 3);
    max_heap_insert(h, 20);
    max_heap_insert(h, 2);

    int popped = max_heap_delete(h, 20);

    /*
             2
          10   3
        5


            10
          2    3
        5


            10
          5    3
        2
    */

    ck_assert_int_eq(popped, 20);
    ck_assert_int_eq(max_heap_top(h), 10);
    ck_assert_int_eq(max_heap_bottom(h), 2);

    max_heap_free(&h);
}
END_TEST

Suite *max_heap_suite(void) {
    Suite *suite;
    TCase *tc_core;

    suite = suite_create("Max Heap");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_max_heap_new);
    tcase_add_test(tc_core, test_max_heap_insert);
    tcase_add_test(tc_core, test_max_heap_delete);

    suite_add_tcase(suite, tc_core);

    return suite;
}

#endif /* TEST_MAX_HEAP_H */
