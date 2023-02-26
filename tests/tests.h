#include "../stack.h"

#ifndef PROJECT_TESTS_H
#define PROJECT_TESTS_H

typedef enum {
    OK,
    failed
} errors;

int run_all_tests(struct Stack *stack);
errors memory_test(struct Stack *stack);
errors protection_test(struct Stack *stack);

#endif
