#include "tests.h"
#include "../stack.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

int run_all_tests(Stack *stack) {
    assert(OK == memory_test(stack));
    assert(OK == protection_test(stack));
}

errors memory_test(Stack *stack) {
    printf("Testing memory functions. \n \n");
    printf("Testing push(). \n");
    push(stack, 9);

    if (stack->num_of_elem != 1) {
        return failed;
    }

    if (stack->memory[1] != 9) {
        return failed;
    }

    printf("Testing push() completed! \n \n");

    printf("Testing delete_stack(). \n");
    delete_stack(stack);

    if(stack->size != 0) {
        return failed;
    }

    printf("Testing delete_stack() completed! \n \n");

    printf("Testing pop(). \n");
    int buf = pop(stack);

    if(buf != 1) {
        return failed;
    }

    push(stack, 1);
    push(stack, 2);
    pop(stack);

    if (stack->memory[1] != 1) {
        return failed;
    }

    printf("Testing pop() completed! \n \n");
    printf("Testing memory functions completed! \n");
    printf("-------------------------------------- \n \n");
    delete_stack(stack);
    return OK;
}

errors protection_test(Stack *stack) {
    printf("Testing protection functions. \n \n");
    printf("Testing verify_canary(). \n");
    make_canary(stack);
    push(stack, 8);
    push(stack, 8);
    push(stack, 8);

    memset(stack->memory, 1, 3*sizeof(int));

    if (verify_canary(stack) == 0) {
        return failed;
    }

    printf("Testing verify_canary() completed! \n \n");

    printf("Testing make_canary(). \n");
    delete_stack(stack);
    make_canary(stack);
    push(stack, 8);
    push(stack, 8);

    if (verify_canary(stack) != 0) {
        return failed;
    }
    printf("Testing make_canary() completed! \n \n");


    printf("Testing verify_hash(). \n");
    int buf_hash = stack->hash;
    push(stack, 1);
    stack->hash = buf_hash;

    if (verify_hash(stack) == 0) {
        return failed;
    }

    printf("Testing verify_hash() completed! \n \n");
    printf("Testing protection functions completed! \n");
    printf("-------------------------------------- \n \n");
    return OK;
}

