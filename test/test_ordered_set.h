#ifndef TEST_ORDERED_SET_H
#define TEST_ORDERED_SET_H

#include <check.h>

#include "../src/ordered_set.h"
#include "test.h"

START_TEST(test_ordered_set_new) {
    TEST_INFO;
    OrderedSet *o = ordered_set_new(10);
    ck_assert_ptr_ne(o, NULL);

    ck_assert_int_eq(ordered_set_size(o), 0);
    ck_assert_int_eq(ordered_set_cap(o), 10);

    ordered_set_free(&o);
    ck_assert_ptr_eq(o, NULL);
}
END_TEST

START_TEST(test_ordered_set_insert) {
    TEST_INFO;
    OrderedSet *o = ordered_set_new(10);
    ordered_set_insert(o, 12);
    ordered_set_insert(o, 6);
    ordered_set_insert(o, 24);
    ordered_set_insert(o, 0);

    ck_assert_int_eq(ordered_set_size(o), 4);
    ck_assert_int_eq(ordered_set_get(o, 0), 0);
    ck_assert_int_eq(ordered_set_get(o, 1), 6);
    ck_assert_int_eq(ordered_set_get(o, 2), 12);
    ck_assert_int_eq(ordered_set_get(o, 3), 24);

    ordered_set_free(&o);
}
END_TEST

START_TEST(test_ordered_set_copy) {
    TEST_INFO;
    OrderedSet *o = ordered_set_new(10);
    ordered_set_insert(o, 12);
    ordered_set_insert(o, 24);
    ordered_set_insert(o, 6);

    OrderedSet *o2 = ordered_set_copy(o);

    ck_assert_int_eq(ordered_set_cap(o2), 10);
    ck_assert_int_eq(ordered_set_size(o2), 3);
    ck_assert_int_eq(ordered_set_get(o2, 0), 6);
    ck_assert_int_eq(ordered_set_get(o2, 2), 24);

    ordered_set_free(&o);
    ordered_set_free(&o2);
}
END_TEST

START_TEST(test_ordered_set_delete) {
    TEST_INFO;
    OrderedSet *o = ordered_set_new(4);
    ordered_set_insert(o, 12);
    ordered_set_insert(o, 6);
    ordered_set_insert(o, 24);
    ordered_set_insert(o, 0);

    ordered_set_delete(o, 12);
    ordered_set_delete(o, 0);
    ordered_set_delete(o, 24);

    ck_assert_int_eq(ordered_set_size(o), 1);
    ck_assert_int_eq(ordered_set_get(o, 0), 6);

    ordered_set_free(&o);
}
END_TEST

START_TEST(test_ordered_set_delete_at) {
    TEST_INFO;
    OrderedSet *o = ordered_set_new(4);
    ordered_set_insert(o, 12);
    ordered_set_insert(o, 6);
    ordered_set_insert(o, 24);
    ordered_set_insert(o, 0);

    ordered_set_delete_at(o, 3);
    ordered_set_delete_at(o, 1);
    ordered_set_delete_at(o, 0);

    ck_assert_int_eq(ordered_set_size(o), 1);
    ck_assert_int_eq(ordered_set_get(o, 0), 12);

    ordered_set_free(&o);
}
END_TEST

START_TEST(test_ordered_set_index_of) {
    TEST_INFO;
    OrderedSet *o = ordered_set_new(10);
    ordered_set_insert(o, 5);
    ordered_set_insert(o, 4);
    ordered_set_insert(o, 6);
    ordered_set_insert(o, 3);
    ordered_set_insert(o, 2);
    ordered_set_insert(o, 9);
    ordered_set_insert(o, 8);
    ordered_set_insert(o, 10);
    ordered_set_insert(o, 0);

    ck_assert_int_eq(ordered_set_index_of(o, 0), 0);
    ck_assert_int_eq(ordered_set_index_of(o, 10), 8);
}
END_TEST

Suite *ordered_set_suite(void) {
    Suite *suite;
    TCase *tc_core;

    suite = suite_create("Ordered Set");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_ordered_set_new);
    tcase_add_test(tc_core, test_ordered_set_insert);
    tcase_add_test(tc_core, test_ordered_set_delete_at);
    tcase_add_test(tc_core, test_ordered_set_delete);
    tcase_add_test(tc_core, test_ordered_set_copy);
    tcase_add_test(tc_core, test_ordered_set_index_of);

    suite_add_tcase(suite, tc_core);

    return suite;
}

#endif /* !TEST_ORDERED_SET_H */
