#ifndef STACK_H
#define STACK_H

typedef struct {
    int state;
    char symbol;
} StackItem;

typedef struct {
    StackItem *items;
    int top;
    int capacity;
} Stack;

Stack* createStack(int capacity);
int isFull(Stack *stack);
int isEmpty(Stack *stack);
void push(Stack *stack, int state, char symbol);
void displayStack(Stack *stack);
StackItem pop(Stack *stack);
StackItem peek(Stack *stack);
void freeStack(Stack *stack);

#endif // STACK_H
