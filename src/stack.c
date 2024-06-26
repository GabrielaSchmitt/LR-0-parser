#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

Stack* createStack(int capacity) {
    Stack *stack = (Stack*)malloc(sizeof(Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->items = (StackItem*)malloc(stack->capacity * sizeof(StackItem));
    return stack;
}

int isFull(Stack *stack) {
    return stack->top == stack->capacity - 1;
}

int isEmpty(Stack *stack) {
    return stack->top == -1;
}

void push(Stack *stack, int state, char symbol) {
    if (isFull(stack))
        return;
    stack->items[++stack->top].state = state;
    stack->items[stack->top].symbol = symbol;
}

void displayStack(Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty\n");
        return;
    }
    printf("Stack: ");
    for (int i = 0; i <= stack->top; i++) {
        printf("[%d, %c] ", stack->items[i].state, stack->items[i].symbol);
    }
    printf("\n");
}

StackItem pop(Stack *stack) {
    if (isEmpty(stack)) {
        StackItem emptyItem = {-1, '\0'};
        return emptyItem;
    }
    return stack->items[stack->top--];
}

StackItem peek(Stack *stack) {
    if (isEmpty(stack)) {
        StackItem emptyItem = {-1, '\0'};
        return emptyItem;
    }
    return stack->items[stack->top];
}

void freeStack(Stack *stack) {
    free(stack->items);
    free(stack);
}
