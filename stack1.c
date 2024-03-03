#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 100

// Structure to represent the stack
struct Stack {
    int top;
    char array[MAX_SIZE];
};

// Function to initialize the stack
void initializeStack(struct Stack *stack) {
    stack->top = -1; // Initialize top as -1 to indicate an empty stack
}

// Function to check if the stack is full
int isFull(struct Stack *stack) {
    return stack->top == MAX_SIZE - 1;
}

// Function to check if the stack is empty
int isEmpty(struct Stack *stack) {
    return stack->top == -1;
}

// Function to push an element onto the stack
void push(struct Stack *stack, char value) {
    if (isFull(stack)) {
        printf("Stack overflow!\n");
        return;
    }
    stack->array[++stack->top] = value;
}

// Function to pop an element from the stack
char pop(struct Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack underflow!\n");
        return '\0'; // Return a dummy value indicating underflow
    }
    return stack->array[stack->top--];
}

// Function to get the precedence of an operator
int precedence(char op) {
    if (op == '+' || op == '-')
        return 1;
    else if (op == '*' || op == '/')
        return 2;
    return 0;
}

// Function to convert infix expression to postfix expression
char* infixToPostfix(char* infix) {
    struct Stack stack;
    initializeStack(&stack);

    int len = strlen(infix);
    char* postfix = (char*)malloc((len + 1) * sizeof(char));
    int j = 0;

    for (int i = 0; i < len; i++) {
        char ch = infix[i];
        if (isalnum(ch)) {
            postfix[j++] = ch;
        } else if (ch == '(') {
            push(&stack, ch);
        } else if (ch == ')') {
            while (!isEmpty(&stack) && stack.array[stack.top] != '(') {
                postfix[j++] = pop(&stack);
            }
            if (!isEmpty(&stack) && stack.array[stack.top] != '(')
                return NULL; // Invalid expression
            else
                pop(&stack); // Remove '('
        } else {
            while (!isEmpty(&stack) && precedence(ch) <= precedence(stack.array[stack.top])) {
                postfix[j++] = pop(&stack);
            }
            push(&stack, ch);
        }
    }

    while (!isEmpty(&stack)) {
        postfix[j++] = pop(&stack);
    }
    postfix[j] = '\0';
    return postfix;
}

// Function to evaluate postfix expression
int evaluatePostfix(char* postfix) {
    struct Stack stack;
    initializeStack(&stack);

    int len = strlen(postfix);

    for (int i = 0; i < len; i++) {
        char ch = postfix[i];
        if (isdigit(ch)) {
            push(&stack, ch - '0');
        } else {
            int operand2 = pop(&stack);
            int operand1 = pop(&stack);
            switch (ch) {
                case '+':
                    push(&stack, operand1 + operand2);
                    break;
                case '-':
                    push(&stack, operand1 - operand2);
                    break;
                case '*':
                    push(&stack, operand1 * operand2);
                    break;
                case '/':
                    push(&stack, operand1 / operand2);
                    break;
            }
        }
    }
    return pop(&stack);
}

// Main function
int main() {
    char infix[MAX_SIZE];
    printf("Enter infix expression: ");
    fgets(infix, MAX_SIZE, stdin);
    infix[strcspn(infix, "\n")] = '\0'; // Remove newline character

    char* postfix = infixToPostfix(infix);
    if (postfix == NULL) {
        printf("Invalid infix expression!\n");
        return 1;
    }

    printf("Postfix expression: %s\n", postfix);

    int result = evaluatePostfix(postfix);
    printf("Result after evaluation: %d\n", result);

    free(postfix); // Free dynamically allocated memory
    return 0;
}
