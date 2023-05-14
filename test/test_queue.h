#ifndef TEST_QUEUE_H
#define TEST_QUEUE_H

#include <check.h>

#include "../src/queue.h"
#include "test.h"

START_TEST(test_queue_new) {
    TEST_INFO;
    Queue *q = queue_new();
    ck_assert_ptr_ne(q, NULL);

    queue_free(&q);
    ck_assert_ptr_eq(q, NULL);
}
END_TEST

START_TEST(test_queue_enqueue) {
    TEST_INFO;
    Queue *q = queue_new();
    int num1 = 3;
    int num2 = 2;

    queue_enqueue(q, &num1);
    queue_enqueue(q, &num2);

    ck_assert_int_eq(queue_size(q), 2);

    queue_free(&q);
}
END_TEST

START_TEST(test_queue_dequeue) {
    TEST_INFO;
    Queue *q = queue_new();
    int num1 = 3;
    int num2 = 2;

    queue_enqueue(q, &num1);
    queue_enqueue(q, &num2);
    void *item = queue_dequeue(q);
    void *item2 = queue_dequeue(q);
    void *should_not_exist = queue_dequeue(q);

    ck_assert_int_eq(queue_size(q), 0);
    ck_assert_ptr_ne(item, NULL);
    ck_assert_int_eq(*(int *)item, 3);
    ck_assert_ptr_ne(item2, NULL);
    ck_assert_int_eq(*(int *)item2, 2);
    ck_assert_ptr_eq(should_not_exist, NULL);

    queue_free(&q);
}
END_TEST

Suite *queue_suite(void) {
    Suite *suite;
    TCase *tc_core;

    suite = suite_create("Queue");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_queue_new);
    tcase_add_test(tc_core, test_queue_enqueue);
    tcase_add_test(tc_core, test_queue_dequeue);

    suite_add_tcase(suite, tc_core);

    return suite;
}

#endif /* !TEST_QUEUE_H */
