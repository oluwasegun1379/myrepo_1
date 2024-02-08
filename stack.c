#include <stdio.h>

#define MAX_SIZE 100

struct Stack {
    int arr[MAX_SIZE];
    int top;
};

void initStack(struct Stack *stack) {
    stack->top = -1;
}

int isEmpty(struct Stack *stack) {
    return (stack->top == -1);
}

int isFull(struct Stack *stack) {
    return (stack->top == MAX_SIZE - 1);
}

void push(struct Stack *stack, int value) {
    if (!isFull(stack)) {
        stack->arr[++stack->top] = value;
    } else {
        printf("Stack overflow\n");
    }
}

int pop(struct Stack *stack) {
    if (!isEmpty(stack)) {
        return stack->arr[stack->top--];
    } else {
        printf("Stack underflow\n");
        return -1;  // Assuming -1 is not a valid value in the stack
    }
}

void printStack(struct Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty\n");
        return;
    }

    printf("Stack: ");
    for (int i = 0; i <= stack->top; i++) {
        printf("%d ", stack->arr[i]);
    }
    printf("\n");
}

int main() {
    struct Stack stack;
    initStack(&stack);

    push(&stack, 10);
    push(&stack, 20);
    push(&stack, 30);
    push(&stack, 40);

    printStack(&stack);

    pop(&stack);
    printStack(&stack);

    return 0;
}
