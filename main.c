#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "tests/tests.h"

/**
 * OUTPUT_LANGUAGE = English
 * PROJECT_NAME = Stack
 * PROJECT_NUMBER = 1.0.0
 * PROJECT_BRIEF = A program with the implementation of a protected stack for a single data type
 * OUTPUT_DIRECTORY = /doc
 */

/**
 * @brief Entry point
 * @detailed Execution of the program
 * starts here.
 * @return Program exit status
 */

int main() {
    Stack stack;
    stack_init(&stack);

    run_all_tests(&stack);

    return 0;
}
