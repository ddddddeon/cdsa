#ifndef TEST_GRAPH_H
#define TEST_GRAPH_H

#include <check.h>

#include "../src/graph.h"
#include "../src/queue.h"
#include "test.h"

START_TEST(test_vertex_new) {
    TEST_INFO;
    Vertex *v = vertex_new("alice");
    Vertex *v2 = vertex_new("bob");
    Vertex *v3 = vertex_new("cliff");
    Vertex *v4 = vertex_new("out");
    Vertex *v5 = vertex_new("way out");

    vertex_connect(v, v2, 100);
    vertex_connect(v2, v3, 200);
    vertex_connect(v3, v4, 100);
    vertex_connect(v, v5, 300);

    vertex_print(v);
    vertex_print(v2);
    vertex_print(v3);

    vertex_dfs_print(v);
    printf("*********\n");
    vertex_bfs_print(v);

    vertex_free(&v);
    ck_assert_ptr_eq(v, NULL);
}
END_TEST

Suite *graph_suite(void) {
    Suite *suite;
    TCase *tc_core;

    suite = suite_create("Graph");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_vertex_new);

    suite_add_tcase(suite, tc_core);

    return suite;
}

#endif /* TEST_GRAPH_H */
