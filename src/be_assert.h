#ifndef ASSERTIONS
#define ASSERTIONS

#include <stdio.h>

#define ASSERT_MALLOC(ptr)                           \
    do                                               \
    {                                                \
        if (!(ptr))                                  \
        {                                            \
            printf("Pointer null assertion failed"); \
            exit(0);                                 \
        };                                           \
    } while (0)


#define ASSERT_REALLOC(old, new)                     \
    do                                               \
    {                                                \
        if (!(new))                                  \
        {                                            \
            printf("Pointer null assertion failed"); \
            free(old);                               \
            exit(0);                                 \
        };                                           \
    } while (0)

#endif