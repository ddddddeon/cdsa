#ifndef TEST_ARRAY_H
#define TEST_ARRAY_H

#include <check.h>

#include "../src/array.h"
#include "test.h"

START_TEST(test_array_new) {
    TEST_INFO;
    Array* a = array_new(10);
    ck_assert_int_eq(array_size(a), 0);
    ck_assert_int_eq(array_cap(a), 10);

    array_free(&a);
    ck_assert_ptr_eq(a, NULL);
}
END_TEST

START_TEST(test_array_get_insert) {
    TEST_INFO;
    Array* a = array_new(10);
    array_insert(a, 1);
    array_insert(a, 2);
    array_insert(a, 3);
    array_insert(a, 1);
    array_insert(a, 2);
    array_insert(a, 3);
    array_insert(a, 1);
    array_insert(a, 2);
    array_insert(a, 3);
    array_insert(a, 1);

    ck_assert_int_eq(array_size(a), 10);
    ck_assert_int_eq(array_get(a, 0), 1);
    ck_assert_int_eq(array_get(a, 1), 2);

    array_free(&a);
}
END_TEST

START_TEST(test_array_avail) {
    TEST_INFO;
    Array* a = array_new(3);
    ck_assert_int_eq(array_avail(a), 3);

    array_insert(a, 10);
    ck_assert_int_eq(array_avail(a), 2);
}
END_TEST

START_TEST(test_array_insert_at) {
    TEST_INFO;
    Array* a = array_new(3);
    array_insert(a, 1);
    array_insert(a, 3);
    array_insert_at(a, 2, 1);

    ck_assert_int_eq(array_size(a), 3);
    ck_assert_int_eq(array_get(a, 1), 2);
    ck_assert_int_eq(array_get(a, 2), 3);

    array_free(&a);
}
END_TEST

START_TEST(test_array_expand) {
    TEST_INFO;
    Array* a = array_new(10);
    array_insert(a, 8);
    array_insert(a, 5);

    ck_assert_int_eq(array_cap(a), 10);
    array_expand(a);
    ck_assert_int_eq(array_get(a, 10), 0);
    ck_assert_int_eq(array_cap(a), 20);

    array_free(&a);

    Array* b = array_new(2);
    array_insert(b, 8);
    array_insert(b, 5);
    array_insert(b, 8);
    array_insert(b, 5);

    ck_assert_int_eq(array_cap(b), 4);
    ck_assert_int_eq(array_size(b), 4);

    array_insert(b, 4);
    ck_assert_int_eq(array_cap(b), 8);
    ck_assert_int_eq(array_size(b), 5);
}
END_TEST

START_TEST(test_array_delete_at) {
    TEST_INFO;
    Array* a = array_new(10);
    array_insert(a, 1);
    array_insert(a, 2);
    array_delete_at(a, 0);

    ck_assert_int_eq(array_size(a), 1);
    ck_assert_int_eq(array_get(a, 0), 2);

    array_free(&a);
}
END_TEST

START_TEST(test_array_update_at) {
    TEST_INFO;
    Array* a = array_new(10);
    array_insert(a, 1);
    array_insert(a, 2);
    array_insert(a, 3);
    array_update_at(a, 4, 1);
    array_update_at(a, 5, 2);

    ck_assert_int_eq(array_size(a), 3);
    ck_assert_int_eq(array_get(a, 1), 4);
    ck_assert_int_eq(array_get(a, 2), 5);

    array_free(&a);
}
END_TEST

START_TEST(test_array_fill) {
    TEST_INFO;
    Array* a = array_new(10);
    array_fill(a, 0);

    ck_assert_int_eq(array_get(a, 0), 0);
    ck_assert_int_eq(array_get(a, 5), 0);
    ck_assert_int_eq(array_get(a, 9), 0);

    array_free(&a);
}
END_TEST

START_TEST(test_array_index_of) {
    TEST_INFO;
    Array* a = array_new(5);
    array_fill(a, 0);
    array_update_at(a, 8, 4);
    int idx = array_index_of(a, 8);

    ck_assert_int_eq(idx, 4);

    array_free(&a);
}
END_TEST

START_TEST(test_array_max_value) {
    TEST_INFO;
    Array* a = array_new(5);
    array_insert(a, 10);
    array_insert(a, 20);
    array_insert(a, 5);

    ck_assert_int_eq(array_max_value(a), 20);

    array_free(&a);
}
END_TEST

START_TEST(test_array_has_duplicate) {
    TEST_INFO;
    Array* a = array_new(10);
    array_insert(a, 1);
    array_insert(a, 1);
    array_insert(a, 3);

    ck_assert(array_has_duplicate(a));

    array_free(&a);

    Array* b = array_new(10);
    array_insert(b, 1);
    array_insert(b, 2);
    array_insert(b, 3);

    ck_assert(!array_has_duplicate(b));
    array_free(&b);
}
END_TEST

START_TEST(test_array_reverse) {
    TEST_INFO;
    Array* a = array_new(3);

    array_insert(a, 3);
    array_insert(a, 5);
    array_insert(a, 8);
    array_reverse(a);

    ck_assert_int_eq(array_get(a, 0), 8);
    ck_assert_int_eq(array_get(a, 2), 3);
    array_free(&a);
}
END_TEST

START_TEST(test_array_copy) {
    TEST_INFO;
    Array* a = array_new(10);
    array_insert(a, 8);
    array_insert(a, 12);
    array_insert(a, 5);

    Array* b = array_copy(a);
    array_free(&a);

    ck_assert_int_eq(array_size(b), 3);
    ck_assert_int_eq(array_cap(b), 10);
    ck_assert_int_eq(array_get(b, 0), 8);
    ck_assert_int_eq(array_get(b, 2), 5);

    array_free(&b);
}
END_TEST

START_TEST(test_array_bubble_sort) {
    TEST_INFO;
    Array* a = array_new(10);
    array_insert(a, 8);
    array_insert(a, 5);
    array_insert(a, 10);
    array_insert(a, 1);
    array_insert(a, -1);
    array_insert(a, 3);
    array_insert(a, 2);

    array_bubble_sort(a);

    ck_assert_int_eq(array_get(a, 0), -1);
    ck_assert_int_eq(array_get(a, 1), 1);
    ck_assert_int_eq(array_get(a, 2), 2);
    ck_assert_int_eq(array_get(a, 6), 10);

    array_free(&a);
}
END_TEST

START_TEST(test_array_selection_sort) {
    TEST_INFO;
    Array* a = array_new(10);
    array_insert(a, 8);
    array_insert(a, 5);
    array_insert(a, 10);
    array_insert(a, 1);
    array_insert(a, -1);
    array_insert(a, 3);
    array_insert(a, 2);

    array_selection_sort(a);

    ck_assert_int_eq(array_get(a, 0), -1);
    ck_assert_int_eq(array_get(a, 1), 1);
    ck_assert_int_eq(array_get(a, 2), 2);
    ck_assert_int_eq(array_get(a, 6), 10);

    array_free(&a);
}
END_TEST

START_TEST(test_array_insertion_sort) {
    TEST_INFO;
    Array* a = array_new(10);
    array_insert(a, 8);
    array_insert(a, 5);
    array_insert(a, 10);
    array_insert(a, 1);
    array_insert(a, -1);
    array_insert(a, 3);
    array_insert(a, 2);

    array_insertion_sort(a);

    ck_assert_int_eq(array_get(a, 0), -1);
    ck_assert_int_eq(array_get(a, 1), 1);
    ck_assert_int_eq(array_get(a, 2), 2);
    ck_assert_int_eq(array_get(a, 6), 10);

    array_free(&a);
}
END_TEST

START_TEST(test_array_quicksort) {
    TEST_INFO;
    Array* a = array_new(10);
    array_insert(a, 8);
    array_insert(a, 5);
    array_insert(a, 10);
    array_insert(a, 1);
    array_insert(a, -1);
    array_insert(a, 3);
    array_insert(a, 2);

    array_quicksort(a, 0, array_size(a) - 1);

    ck_assert_int_eq(array_get(a, 0), -1);
    ck_assert_int_eq(array_get(a, 1), 1);
    ck_assert_int_eq(array_get(a, 2), 2);
    ck_assert_int_eq(array_get(a, 6), 10);

    array_free(&a);
}
END_TEST

Suite* array_suite(void) {
    Suite* suite;
    TCase* tc_core;
    suite = suite_create("Array");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_array_new);
    tcase_add_test(tc_core, test_array_get_insert);
    tcase_add_test(tc_core, test_array_insert_at);
    tcase_add_test(tc_core, test_array_expand);
    tcase_add_test(tc_core, test_array_avail);
    tcase_add_test(tc_core, test_array_delete_at);
    tcase_add_test(tc_core, test_array_update_at);
    tcase_add_test(tc_core, test_array_fill);
    tcase_add_test(tc_core, test_array_index_of);
    tcase_add_test(tc_core, test_array_max_value);
    tcase_add_test(tc_core, test_array_has_duplicate);
    tcase_add_test(tc_core, test_array_reverse);
    tcase_add_test(tc_core, test_array_copy);
    tcase_add_test(tc_core, test_array_bubble_sort);
    tcase_add_test(tc_core, test_array_selection_sort);
    tcase_add_test(tc_core, test_array_insertion_sort);
    tcase_add_test(tc_core, test_array_quicksort);

    suite_add_tcase(suite, tc_core);

    return suite;
}

#endif /* !TEST_ARRAY_H  */
