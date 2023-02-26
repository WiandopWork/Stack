#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Stack initialization
 * @details The function creates a stack with an initial size of 32 bytes
 * @param stack Data structure - stack
 * @see make_canary
 */

void stack_init(Stack *stack) {
    stack->memory = (int*) malloc(8 * sizeof(int));
    stack->num_of_elem = 0;
    stack->size = 8 * sizeof(int);

    make_canary(stack);
    stack->hash = MurmurHash2(stack->memory, stack->num_of_elem + 2);
    return;
}

/**
 * @brief Removing the stack
 * @details The function clears the memory allocated for the stack
 * @param stack Data structure - stack
 */

void delete_stack(Stack *stack) {
    free(stack->memory);
    stack->num_of_elem = 0;
    stack->size = 0;
    stack->hash = 0;
    return;
}

/**
 * @brief Push element in stack
 * @details The function adds an element to the stack. If there is not enough memory in the stack, the function increases it by 2 times
 * @param stack Data structure - stack
 * @param key The element being added
 */

void push(Stack *stack, int key) {
    stack->memory[stack->num_of_elem + 1] = key;
    stack->num_of_elem++;
    stack->memory[stack->num_of_elem + 2] = stack->canary;

    if (((stack->num_of_elem + 2) * sizeof(int)) == stack->size) {
        stack->memory = (int*) realloc(stack->memory, sizeof(int) * (stack->num_of_elem + 2) * 2);
        stack->size *= 2;
    }

    stack->hash = MurmurHash2(stack->memory, stack->num_of_elem + 2);

    return;
}

/**
 * @brief Pop element from stack
 * @details The function removes an element from the stack. If the elements in the stack are 4 times less than the allocated memory, then the function reduces it
 * @param stack Data structure - stack
 */

int pop(Stack *stack) {
    if (stack->num_of_elem == 0) {
        return 1;
    }

    stack->num_of_elem--;

    if (((stack->num_of_elem + 2) * sizeof(int)) == stack->size / 4) {
        stack->memory = (int*) realloc(stack->memory, stack->size / 4);
        stack->size /= 4;
    }

    stack->memory[stack->num_of_elem + 1] = stack->canary;
    stack->hash = MurmurHash2(stack->memory, stack->num_of_elem + 2);

    return 0;
}

/**
 * @brief Creating canary
 * @details The function creates a degree of protection canary
 * @param stack Data structure - stack
 */

void make_canary(Stack *stack) {
    stack->canary = 922337807;
    stack->memory[0] = stack->canary;
    stack->memory[1] = stack->canary;
    return;
}

/**
 * @brief Checking the canary
 * @details The function compares the value of the canary elements
 * @param stack Data structure - stack
 */

int verify_canary(Stack *stack) {
    if (stack->memory[0] == stack->memory[stack->num_of_elem + 1]) {
        return 0;
    } else {
        return 1;
    }
}

/**
 * @brief Creating a hash
 * @details The function generates a hash using an algorithm murmurhash
 * @param stack Data structure - stack
 */

unsigned int MurmurHash2 (int *key, unsigned int len) {
    const unsigned int m = 0x5bd1e995;
    const unsigned int seed = 0;
    const int r = 24;

    unsigned int h = seed ^ len;

    const unsigned int * data = (const unsigned int *)key;
    unsigned int k = 0;

    while (len >= 4) {
        k  = data[0];
        k |= data[1] << 8;
        k |= data[2] << 16;
        k |= data[3] << 24;

        k *= m;
        k ^= k >> r;
        k *= m;

        h *= m;
        h ^= k;

        data += 4;
        len -= 4;
    }

    switch (len) {
        case 3:
            h ^= data[2] << 16;
        case 2:
            h ^= data[1] << 8;
        case 1:
            h ^= data[0];
            h *= m;
    };

    h ^= h >> 13;
    h *= m;
    h ^= h >> 15;

    return h;
}

/**
 * @brief Checking a hash
 * @details The function checks the current hash with the generated
 * @param stack Data structure - stack
 */

int verify_hash(Stack *stack) {
    int buf_hash = MurmurHash2(stack->memory, stack->size);

    if (buf_hash == stack->hash) {
        return 0;
    } else {
        return 1;
    }
}