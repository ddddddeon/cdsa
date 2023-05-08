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
    queue_enqueue(q, 3);
    queue_enqueue(q, 2);

    ck_assert_int_eq(queue_size(q), 2);

    queue_free(&q);
}
END_TEST

START_TEST(test_queue_dequeue) {
    TEST_INFO;
    Queue *q = queue_new();
    queue_enqueue(q, 3);
    queue_enqueue(q, 2);
    QueueItem item = queue_dequeue(q);
    QueueItem item2 = queue_dequeue(q);
    QueueItem should_not_exist = queue_dequeue(q);

    ck_assert_int_eq(queue_size(q), 0);
    ck_assert(item.exists);
    ck_assert_int_eq(item.value, 3);
    ck_assert(item2.exists);
    ck_assert_int_eq(item2.value, 2);
    ck_assert(!should_not_exist.exists);

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
