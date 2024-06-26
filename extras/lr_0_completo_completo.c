#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// transducer
int isLowerCaseLetter(char c) {
    return (c >= 'a' && c <= 'z');
}

char *transducer() {
    char input[100];
    char *output = (char *)malloc(100 * sizeof(char));
    if (output == NULL) {
        printf("Erro de alocação de memória\n");
        exit(1);
    }
    
    int i = 0;
    int j = 0;

    printf("Digite a cadeia de entrada: ");
    fgets(input, sizeof(input), stdin);

    while (input[i] != '\0' && input[i] != '\n') {
        if (isspace(input[i])) {
            i++;
            continue;
        } else if (isLowerCaseLetter(input[i])) {
            output[j++] = 'x';
            while (isLowerCaseLetter(input[i])) {
                i++;
            }
        } else if (input[i] == '+' || input[i] == '(' || input[i] == ')') {
            output[j++] = input[i++];
        } else {
            printf("<REJEITAR>\n");
            exit(1);
        }
    }

    output[j] = '\0';
    printf("Saida: %s\n", output);
    
    output[j] = '$';
    output[j + 1] = '\0';

    return output;
}

// Stack definitions and functions
typedef struct {
    int state;
    char symbol;
} StackItem;

typedef struct {
    StackItem *items;
    int top;
    int capacity;
} Stack;

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

int parsingTable(int state, char symbol, Stack* stack) {
    switch (state) {
        case 0:
            if (symbol == '(') { //S2
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
                //push(stack, 1, 'S');
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
            if (symbol == '(') {  // S2
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
                //push(stack, 5, 'S');
                return 5;
            } 
            if (symbol == 'E') { // G4
                printf("\n> G4 \n");
                stack->items[stack->top].state = 4;
                //push(stack, 4, 'E');
                return 4;
            } 
            break;
        case 3:
            printf("\n> R3: S -> x \n");
            pop(stack);  // pop x
            push(stack, peek(stack).state, 'S');
            return -3;
            break; 
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
            printf("\n>  R4: E -> S \n");
            pop(stack);  // pop S
            push(stack, 4, 'E');
            return -4;
            break;
        case 6: // R2: S -> ( E )
            printf("\n> R2: S -> ( E ) \n");
            pop(stack); // pop )
            pop(stack); // pop E
            pop(stack); // pop (
            // push(stack, 8, 'S');
            push(stack, 2, 'S');
            if ( stack->items[stack->top-2].symbol  == 'E' && stack->items[stack->top-1].symbol == '+'){
                stack->items[stack->top].state = 8;
            }else{
                return -1;
            }
            //displayStack(stack);
            return -2;
            break;
        case 7:
            if (symbol == '(') {// S2
                printf("\n> S2 \n");
                push(stack, 2, '(');
                return 2;
            }
            if (symbol == 'x') {// S3
                printf("\n> S3 \n");
                push(stack, 3, 'x');
                return 3;
            }
            if (symbol == 'S') { // G8
                printf("\n> G8 \n");
                stack->items[stack->top].state = 8;
                //push(stack, 8, 'S');
                return 8;
            }
            break;
        case 8:
            printf("\n> R5: E -> E + S \n");
            pop(stack);  // pop S
            pop(stack);  // pop +
            pop(stack);  // pop E
            push(stack, 4, 'E');
            return -5;
            break;
        default:
            return -1;
    }
    return -1;
}

int main() {
    char *input = transducer(); 

    Stack *stack = createStack(100);
    push(stack, 0, '$');  // Start symbol

    // char input[] = "(x+x+x)$";  // Exemplo de entrada
    // x, (x) (x+x)  (x+(x)), ((x)+x), ((x)+(x)), ((x+x)+x) etc...
    // extras: (x+(x)+x), (x+x+x), (x+((x+x))), (x+((x+(x))))
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
    
        // estado de aceitação
        if ( symbol == '$'){
            printf("----------- LOOP %d -----------\n", loop_counter); 
            displayStack(stack);
            
            push(stack, 1, symbol);
            symbol = input[++i];
            
            printf("\naceitacao");
            printf("\n----------- LOOP %d -----------\n", loop_counter+1); 
            displayStack(stack);
            break;

        } else if ( action > 0 && action != 1 && action != 4 && action != 5 && action != 8){
            // shift
            symbol = input[++i];   
        } else if ( action < 0 && action != -1){
            // go to 
            if( peek(stack).symbol == 'S' ||  peek(stack).symbol == 'E'){ // GO TO
                action = parsingTable(peek(stack).state, peek(stack).symbol, stack);   
            }
        
        // estado quando action é de erro
        } else {
            printf("Syntax error\n");
            break;
        }
        printf("----------- LOOP %d -----------\n", loop_counter); 
        displayStack(stack);  

        //if ( loop_counter == 40) break; // timeout
    }

    freeStack(stack);
    return 0;
}