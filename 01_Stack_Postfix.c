#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

struct Stack {
    int arr[MAX];
    int top;
};

void initialize(struct Stack *s) {
    s->top = -1;
}

int isEmpty(struct Stack *s) {
    return s->top == -1;
}

int isFull(struct Stack *s) {
    return s->top == MAX - 1;
}

void push(struct Stack *s, int x) {
    if (isFull(s)) {
        printf("Stack Overflow\n");
        return;
    }

    s->arr[++s->top] = x;
}

int pop(struct Stack *s) {
    if (isEmpty(s)) {
        printf("Stack Underflow\n");
        return -1;
    }

    return s->arr[s->top--];
}

int evaluatePostfix(char exp[]) {
    struct Stack s;
    initialize(&s);

    for (int i = 0; i < strlen(exp); i++) {

        // Ignore spaces
        if (exp[i] == ' ')
            continue;

        // If operand, push it into stack
        if (isdigit(exp[i])) {
            push(&s, exp[i] - '0');
        }

        // If operator, pop two operands
        else {
            int val2 = pop(&s);
            int val1 = pop(&s);

            switch (exp[i]) {
                case '+':
                    push(&s, val1 + val2);
                    break;

                case '-':
                    push(&s, val1 - val2);
                    break;

                case '*':
                    push(&s, val1 * val2);
                    break;

                case '/':
                    push(&s, val1 / val2);
                    break;

                case '%':
                    push(&s, val1 % val2);
                    break;
            }
        }
    }

    return pop(&s);
}

int main() {
    char postfix[MAX];

    printf("Enter Postfix Expression: ");
    fgets(postfix, MAX, stdin);

    printf("Result = %d", evaluatePostfix(postfix));

    return 0;
}
