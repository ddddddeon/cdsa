#ifndef COMMON_H
#define COMMON_H

#define ABORT_IF_NULL(p)                                              \
    do {                                                              \
        if (p == NULL) {                                              \
            printf("[%s] structure has been freed!\n", __FUNCTION__); \
            abort();                                                  \
        }                                                             \
    } while (0)

#endif /* COMMON_H */
