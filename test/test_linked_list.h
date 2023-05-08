#ifndef TEST_LINKED_LIST_H
#define TEST_LINKED_LIST_H

#include <check.h>

#include "../src/linked_list.h"
#include "test.h"

START_TEST(test_linked_list_new) {
    TEST_INFO;
    LinkedList *l = linked_list_new();

    ck_assert_ptr_ne(l, NULL);

    linked_list_free(&l);

    ck_assert_ptr_eq(l, NULL);
}
END_TEST

START_TEST(test_linked_list_insert_end) {
    TEST_INFO;
    LinkedList *l = linked_list_new();
    linked_list_insert_end(l, 0);
    linked_list_insert_end(l, 1);

    ck_assert_int_eq(linked_list_size(l), 2);
    ck_assert_int_eq(linked_list_last(l), 1);
    ck_assert_int_eq(linked_list_first(l), 0);
}
END_TEST

START_TEST(test_linked_list_insert_beginning) {
    TEST_INFO;
    LinkedList *l = linked_list_new();
    linked_list_insert_beginning(l, 0);
    linked_list_insert_beginning(l, 1);

    ck_assert_int_eq(linked_list_size(l), 2);
    ck_assert_int_eq(linked_list_last(l), 0);
    ck_assert_int_eq(linked_list_first(l), 1);
}
END_TEST

START_TEST(test_linked_list_insert_at) {
    TEST_INFO;
    LinkedList *l = linked_list_new();
    linked_list_insert_end(l, 0);
    linked_list_insert_end(l, 1);
    linked_list_insert_end(l, 2);
    linked_list_insert_at(l, 4, 0);
    linked_list_insert_at(l, 5, 1);
    linked_list_insert_at(l, 6, 5);

    ck_assert_int_eq(linked_list_size(l), 6);
    ck_assert_int_eq(linked_list_first(l), 4);
    ck_assert_int_eq(linked_list_last(l), 6);
}
END_TEST

START_TEST(test_linked_list_update_at) {
    TEST_INFO;
    LinkedList *l = linked_list_new();
    linked_list_insert_end(l, 0);
    linked_list_insert_end(l, 1);
    linked_list_insert_end(l, 2);

    linked_list_update_at(l, 4, 0);
    linked_list_update_at(l, 5, 1);
    linked_list_update_at(l, 6, 2);

    ck_assert_int_eq(linked_list_size(l), 3);
    ck_assert_int_eq(linked_list_first(l), 4);
    ck_assert_int_eq(linked_list_last(l), 6);
}
END_TEST

START_TEST(test_linked_list_delete) {
    TEST_INFO;
    LinkedList *l = linked_list_new();
    linked_list_insert_end(l, 0);
    linked_list_insert_end(l, 1);
    linked_list_insert_end(l, 2);

    linked_list_delete(l, 2);
    linked_list_delete(l, 0);

    ck_assert_int_eq(linked_list_size(l), 1);
    ck_assert_int_eq(linked_list_first(l), 1);
    ck_assert_int_eq(linked_list_last(l), 1);

    linked_list_free(&l);
}
END_TEST

START_TEST(test_linked_list_reverse) {
    TEST_INFO;
    LinkedList *l = linked_list_new();
    linked_list_insert_end(l, 0);
    linked_list_insert_end(l, 1);
    linked_list_insert_end(l, 2);

    linked_list_reverse(l);

    ck_assert_int_eq(linked_list_last(l), 0);
    ck_assert_int_eq(linked_list_first(l), 2);

    linked_list_free(&l);
}
END_TEST

Suite *linked_list_suite(void) {
    Suite *suite;
    TCase *tc_core;

    suite = suite_create("Linked List");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_linked_list_new);
    tcase_add_test(tc_core, test_linked_list_insert_end);
    tcase_add_test(tc_core, test_linked_list_insert_beginning);
    tcase_add_test(tc_core, test_linked_list_insert_at);
    tcase_add_test(tc_core, test_linked_list_update_at);
    tcase_add_test(tc_core, test_linked_list_delete);
    tcase_add_test(tc_core, test_linked_list_reverse);

    suite_add_tcase(suite, tc_core);

    return suite;
}

#endif /* !TEST_LINKED_LIST_H */
