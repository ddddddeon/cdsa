#ifndef TEST_H
#define TEST_H

#include <stdio.h>

#define TEST_INFO                       \
    do {                                \
        printf("* %s\n", __FUNCTION__); \
    } while (0)

#endif /* !TEST_H */
