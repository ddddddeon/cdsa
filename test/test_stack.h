#ifndef TEST_STACK_H
#define TEST_STACK_H

#include <check.h>

#include "../src/stack.h"
#include "test.h"

START_TEST(test_stack_new) {
    TEST_INFO;
    Stack *s = stack_new();
    ck_assert_ptr_ne(s, NULL);

    stack_free(&s);
    ck_assert_ptr_eq(s, NULL);
}
END_TEST

START_TEST(test_stack_push) {
    TEST_INFO;
    Stack *s = stack_new();
    stack_push(s, 10);
    stack_push(s, 12);

    ck_assert_int_eq(stack_size(s), 2);

    stack_free(&s);
}
END_TEST

START_TEST(test_stack_pop) {
    TEST_INFO;
    Stack *s = stack_new();
    stack_push(s, 10);
    stack_push(s, 12);
    StackItem popped = stack_pop(s);

    ck_assert(popped.exists);
    ck_assert_int_eq(popped.value, 12);
    ck_assert_int_eq(stack_size(s), 1);

    stack_pop(s);
    StackItem should_not_exist = stack_pop(s);
    ck_assert(!should_not_exist.exists);
    ck_assert_int_eq(stack_size(s), 0);

    stack_free(&s);
}
END_TEST

START_TEST(test_stack_peek) {
    TEST_INFO;
    Stack *s = stack_new();
    stack_push(s, 10);
    stack_push(s, 12);
    StackItem peeked = stack_peek(s);

    ck_assert(peeked.exists);
    ck_assert_int_eq(peeked.value, 12);
    ck_assert_int_eq(stack_size(s), 2);

    stack_pop(s);
    stack_pop(s);

    StackItem should_not_exist = stack_peek(s);
    ck_assert(!should_not_exist.exists);
    ck_assert_int_eq(stack_size(s), 0);

    stack_free(&s);
}
END_TEST

Suite *stack_suite(void) {
    Suite *suite;
    TCase *tc_core;

    suite = suite_create("Stack");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_stack_new);
    tcase_add_test(tc_core, test_stack_push);
    tcase_add_test(tc_core, test_stack_pop);
    tcase_add_test(tc_core, test_stack_peek);

    suite_add_tcase(suite, tc_core);

    return suite;
}

#endif /* !TEST_STACK_H */
