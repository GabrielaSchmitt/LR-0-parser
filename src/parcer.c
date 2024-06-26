#include "parser.h"
#include "stack.h"
#include <stdio.h>

int parsingTable(int state, char symbol, Stack* stack) {
    switch (state) {
        case 0:
            if (symbol == '(') { // S2
                printf("\n> S2 \n");
                push(stack, 2, '(');
                return 2;
            } 
            if (symbol == 'x') { // S3
                printf("\n> S3 \n");
                push(stack, 3, 'x');
                return 3;
            }
            if (symbol == 'S') { // G1
                printf("\n> G1 \n");
                stack->items[stack->top].state = 1;
                return 1;
            }
            break;
        case 1:
            if (symbol == '$') { // Accept
                printf("\n> aceitacao \n");
                push(stack, 1, '$');
                return -6;
            }
            break;
        case 2:
            if (symbol == '(') { // S2
                printf("\n> S2 \n");
                push(stack, 2, '(');
                return 2;
            }
            if (symbol == 'x') { // S3
                printf("\n> S3 \n");
                push(stack, 3, 'x');
                return 3;
            }
            if (symbol == 'S') { // G5
                printf("\n> G5 \n");
                stack->items[stack->top].state = 5;
                return 5;
            }
            if (symbol == 'E') { // G4
                printf("\n> G4 \n");
                stack->items[stack->top].state = 4;
                return 4;
            }
            break;
        case 3:
            printf("\n> R3: S -> x \n");
            pop(stack); // pop x
            push(stack, peek(stack).state, 'S');
            return -3;
        case 4:
            if (symbol == ')') { // S6
                printf("\n> S6 \n");
                push(stack, 6, ')');
                return 6;
            }
            if (symbol == '+') { // S7
                printf("\n> S7 \n");
                push(stack, 7, '+');
                return 7;
            }
            break;
        case 5: // R4: E -> S
            printf("\n> R4: E -> S \n");
            pop(stack); // pop S
            push(stack, 4, 'E');
            return -4;
        case 6: // R2: S -> ( E )
            printf("\n> R2: S -> ( E ) \n");
            pop(stack); // pop )
            pop(stack); // pop E
            pop(stack); // pop (
            push(stack, 2, 'S');
            if (stack->items[stack->top-2].symbol == 'E' && stack->items[stack->top-1].symbol == '+') {
                stack->items[stack->top].state = 8;
            }
            return -2;
        case 7:
            if (symbol == '(') { // S2
                printf("\n> S2 \n");
                push(stack, 2, '(');
                return 2;
            }
            if (symbol == 'x') { // S3
                printf("\n> S3 \n");
                push(stack, 3, 'x');
                return 3;
            }
            if (symbol == 'S') { // G8
                printf("\n> G8 \n");
                stack->items[stack->top].state = 8;
                return 8;
            }
            break;
        case 8:
            printf("\n> R5: E -> E + S \n");
            pop(stack); // pop S
            pop(stack); // pop +
            pop(stack); // pop E
            push(stack, 4, 'E');
            return -5;
        default:
            return -1;
    }
    return -1;
}
