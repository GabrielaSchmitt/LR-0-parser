#include <stdio.h>
#include "transducer.h"
#include "stack.h"
#include "parser.h"

char *transducer();

int main() {
    char *input = transducer(); 

    Stack *stack = createStack(100);
    push(stack, 0, '$'); // Start symbol

    int i = 0;
    char symbol = input[i];
    int loop_counter = 0;

    printf("Cadeia: %s\n", input);
    printf("----------- LOOP %d -----------\n", loop_counter); 
    displayStack(stack);

    while (1) {
        StackItem top = peek(stack);
        int action = parsingTable(top.state, symbol, stack);     

        loop_counter++;
    
        if (symbol == '$') {
            printf("----------- LOOP %d -----------\n", loop_counter); 
            displayStack(stack);
            
            push(stack, 1, symbol);
            symbol = input[++i];
            
            printf("\naceitacao");
            printf("\n----------- LOOP %d -----------\n", loop_counter + 1); 
            displayStack(stack);
            break;
        } else if (action > 0 && action != 1 && action != 4 && action != 5 && action != 8) {
            symbol = input[++i];   
        } else if (action < 0) {
            if (peek(stack).symbol == 'S' || peek(stack).symbol == 'E') {
                action = parsingTable(peek(stack).state, peek(stack).symbol, stack);   
            }
        } else {
            printf("Syntax error\n");
            break;
        }
        printf("----------- LOOP %d -----------\n", loop_counter); 
        displayStack(stack);  

        if (loop_counter == 40) break;
    }

    freeStack(stack);
    return 0;
}