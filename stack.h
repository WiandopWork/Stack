#ifndef STACK_STACK_H
#define STACK_STACK_H

typedef struct Stack {
    int* memory;
    int size;
    int num_of_elem;
    int canary;
    int hash;
} Stack;

void make_canary(Stack *stack);
int verify_canary(Stack *stack);
void stack_init(Stack *stack);
void delete_stack(Stack *stack);
void push(Stack *stack, int key);
int pop(Stack *stack);
unsigned int MurmurHash2 (int *key, unsigned int len);
int verify_hash(Stack *stack);

#endif
