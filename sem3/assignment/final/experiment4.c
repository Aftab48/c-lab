/*
 * Experiment-4: Demonstrate the efficacy of a stack in solving 
 * a) postfix expression evaluation and 
 * b) Stock Span problems. 
 * Prepare your own input files to prove the correctness of your programs. 
 * There should be output files tracing the different parts of your implementation at different debug levels.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 100
#define DEBUG_LEVEL 2 // 0 = no debug, 1 = basic, 2 = verbose

FILE* debugFile;

struct Stack {
    int arr[MAX_SIZE];
    int top;
};

void initStack(struct Stack* s) {
    s->top = -1;
}

int isEmpty(struct Stack* s) {
    return s->top == -1;
}

int isFull(struct Stack* s) {
    return s->top == MAX_SIZE - 1;
}

void push(struct Stack* s, int value) {
    if (isFull(s)) {
        printf("Stack overflow!\n");
        return;
    }
    s->arr[++s->top] = value;
    if (DEBUG_LEVEL >= 2) {
        fprintf(debugFile, "  [DEBUG] Pushed %d onto stack. Top: %d\n", value, s->top);
    }
}

int pop(struct Stack* s) {
    if (isEmpty(s)) {
        printf("Stack underflow!\n");
        return -1;
    }
    int value = s->arr[s->top--];
    if (DEBUG_LEVEL >= 2) {
        fprintf(debugFile, "  [DEBUG] Popped %d from stack. Top: %d\n", value, s->top);
    }
    return value;
}

int peek(struct Stack* s) {
    if (isEmpty(s)) {
        return -1;
    }
    return s->arr[s->top];
}

// Part A: Postfix Expression Evaluation
int evaluatePostfix(char* expression) {
    fprintf(debugFile, "\n=== POSTFIX EXPRESSION EVALUATION ===\n");
    fprintf(debugFile, "Expression: %s\n", expression);
    
    struct Stack stack;
    initStack(&stack);
    
    int len = strlen(expression);
    
    for (int i = 0; i < len; i++) {
        if (DEBUG_LEVEL >= 1) {
            fprintf(debugFile, "\nProcessing character: '%c'\n", expression[i]);
        }
        
        if (expression[i] == ' ') {
            continue;
        }
        
        if (isdigit(expression[i])) {
            int num = 0;
            while (i < len && isdigit(expression[i])) {
                num = num * 10 + (expression[i] - '0');
                i++;
            }
            i--;
            push(&stack, num);
            if (DEBUG_LEVEL >= 1) {
                fprintf(debugFile, "  Operand: %d\n", num);
            }
        } else if (expression[i] == '+' || expression[i] == '-' || 
                   expression[i] == '*' || expression[i] == '/') {
            if (DEBUG_LEVEL >= 1) {
                fprintf(debugFile, "  Operator: %c\n", expression[i]);
            }
            
            int b = pop(&stack);
            int a = pop(&stack);
            
            if (DEBUG_LEVEL >= 1) {
                fprintf(debugFile, "  Operands: %d %c %d\n", a, expression[i], b);
            }
            
            int result;
            switch (expression[i]) {
                case '+':
                    result = a + b;
                    break;
                case '-':
                    result = a - b;
                    break;
                case '*':
                    result = a * b;
                    break;
                case '/':
                    if (b == 0) {
                        fprintf(debugFile, "  [ERROR] Division by zero!\n");
                        return -1;
                    }
                    result = a / b;
                    break;
            }
            
            push(&stack, result);
            if (DEBUG_LEVEL >= 1) {
                fprintf(debugFile, "  Result: %d\n", result);
            }
        }
    }
    
    int finalResult = pop(&stack);
    fprintf(debugFile, "\nFinal Result: %d\n", finalResult);
    return finalResult;
}

// Part B: Stock Span Problem
void calculateStockSpan(int prices[], int n, int span[]) {
    fprintf(debugFile, "\n=== STOCK SPAN PROBLEM ===\n");
    fprintf(debugFile, "Prices: ");
    for (int i = 0; i < n; i++) {
        fprintf(debugFile, "%d ", prices[i]);
    }
    fprintf(debugFile, "\n");
    
    struct Stack stack;
    initStack(&stack);
    
    span[0] = 1;
    push(&stack, 0);
    
    if (DEBUG_LEVEL >= 1) {
        fprintf(debugFile, "Day 0: Price = %d, Span = 1 (first day)\n", prices[0]);
    }
    
    for (int i = 1; i < n; i++) {
        if (DEBUG_LEVEL >= 1) {
            fprintf(debugFile, "\nDay %d: Price = %d\n", i, prices[i]);
        }
        
        while (!isEmpty(&stack) && prices[peek(&stack)] <= prices[i]) {
            int popped = pop(&stack);
            if (DEBUG_LEVEL >= 2) {
                fprintf(debugFile, "  Popped index %d (price: %d) as it's <= current price\n", 
                        popped, prices[popped]);
            }
        }
        
        if (isEmpty(&stack)) {
            span[i] = i + 1;
            if (DEBUG_LEVEL >= 1) {
                fprintf(debugFile, "  Stack empty, span = %d (all previous days)\n", span[i]);
            }
        } else {
            span[i] = i - peek(&stack);
            if (DEBUG_LEVEL >= 1) {
                fprintf(debugFile, "  Top of stack: index %d (price: %d), span = %d\n", 
                        peek(&stack), prices[peek(&stack)], span[i]);
            }
        }
        
        push(&stack, i);
    }
    
    fprintf(debugFile, "\nFinal Spans: ");
    for (int i = 0; i < n; i++) {
        fprintf(debugFile, "%d ", span[i]);
    }
    fprintf(debugFile, "\n");
}

int main() {
    debugFile = fopen("stack_debug.txt", "w");
    if (debugFile == NULL) {
        printf("Error creating debug file\n");
        return 1;
    }
    
    fprintf(debugFile, "=== STACK OPERATIONS DEBUG TRACE ===\n");
    fprintf(debugFile, "Debug Level: %d\n", DEBUG_LEVEL);
    
    // Part A: Postfix Evaluation
    FILE* postfixInput = fopen("postfix_input.txt", "r");
    if (postfixInput == NULL) {
        printf("Creating postfix_input.txt...\n");
        postfixInput = fopen("postfix_input.txt", "w");
        fprintf(postfixInput, "2 3 4 * +\n");
        fprintf(postfixInput, "5 6 + 7 *\n");
        fprintf(postfixInput, "10 2 3 * +\n");
        fclose(postfixInput);
        postfixInput = fopen("postfix_input.txt", "r");
    }
    
    FILE* postfixOutput = fopen("postfix_output.txt", "w");
    fprintf(postfixOutput, "Postfix Expression Evaluation Results\n");
    fprintf(postfixOutput, "=====================================\n\n");
    
    char expression[100];
    while (fgets(expression, sizeof(expression), postfixInput)) {
        expression[strcspn(expression, "\n")] = 0; // Remove newline
        if (strlen(expression) > 0) {
            int result = evaluatePostfix(expression);
            fprintf(postfixOutput, "Expression: %s\n", expression);
            fprintf(postfixOutput, "Result: %d\n\n", result);
        }
    }
    
    fclose(postfixInput);
    fclose(postfixOutput);
    
    // Part B: Stock Span
    FILE* stockInput = fopen("stock_input.txt", "r");
    if (stockInput == NULL) {
        printf("Creating stock_input.txt...\n");
        stockInput = fopen("stock_input.txt", "w");
        fprintf(stockInput, "7\n");
        fprintf(stockInput, "100 80 60 70 60 75 85\n");
        fclose(stockInput);
        stockInput = fopen("stock_input.txt", "r");
    }
    
    int n;
    fscanf(stockInput, "%d", &n);
    int prices[MAX_SIZE];
    int span[MAX_SIZE];
    
    for (int i = 0; i < n; i++) {
        fscanf(stockInput, "%d", &prices[i]);
    }
    fclose(stockInput);
    
    calculateStockSpan(prices, n, span);
    
    FILE* stockOutput = fopen("stock_output.txt", "w");
    fprintf(stockOutput, "Stock Span Problem Results\n");
    fprintf(stockOutput, "==========================\n\n");
    fprintf(stockOutput, "Day\tPrice\tSpan\n");
    fprintf(stockOutput, "-------------------\n");
    for (int i = 0; i < n; i++) {
        fprintf(stockOutput, "%d\t%d\t%d\n", i, prices[i], span[i]);
    }
    fclose(stockOutput);
    
    fclose(debugFile);
    
    printf("Stack operations completed!\n");
    printf("Output files generated:\n");
    printf("  - stack_debug.txt (debug trace)\n");
    printf("  - postfix_output.txt (postfix evaluation results)\n");
    printf("  - stock_output.txt (stock span results)\n");
    
    return 0;
}

