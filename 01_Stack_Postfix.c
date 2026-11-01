/*
 * Stack implementation (array based) and its use to evaluate a
 * POSTFIX expression - program in C
 *
 * Stack operations : push, pop, peek, isEmpty, isFull, display
 * Postfix input    : operands and operators separated by SPACES
 *                    (so multi-digit numbers work), e.g.  10 2 8 * + 3 -
 * Operators        : +  -  *  /  %  ^   (^ = power)
 *
 * Algorithm:
 *   1. Scan the expression from left to right.
 *   2. If a number is found, push it onto the stack.
 *   3. If an operator is found, pop two operands (b first, then a),
 *      compute (a operator b) and push the result back.
 *   4. At the end, the single value left on the stack is the answer.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

int stack[MAX];
int top = -1;

/* ---------- Stack operations ---------- */

int isEmpty() {
    return (top == -1);
}

int isFull() {
    return (top == MAX - 1);
}

/* returns 1 on success, 0 on overflow */
int push(int value) {
    if (isFull()) {
        printf("Stack Overflow!\n");
        return 0;
    }
    stack[++top] = value;
    return 1;
}

/* returns 1 on success, 0 on underflow; popped value goes in *value */
int pop(int *value) {
    if (isEmpty()) {
        printf("Stack Underflow!\n");
        return 0;
    }
    *value = stack[top--];
    return 1;
}

/* returns 1 on success, 0 if empty */
int peek(int *value) {
    if (isEmpty())
        return 0;
    *value = stack[top];
    return 1;
}

void displayStack() {
    if (isEmpty()) {
        printf("[ empty ]");
        return;
    }
    printf("[ ");
    for (int i = 0; i <= top; i++)
        printf("%d ", stack[i]);
    printf("]  (top = %d)", stack[top]);
}

/* ---------- Postfix evaluation ---------- */

/* integer power: base^exp, exp >= 0 */
int power(int base, int exp) {
    int result = 1;
    while (exp > 0) {
        result *= base;
        exp--;
    }
    return result;
}

/* Evaluate postfix expression. Returns 1 if valid, 0 on error. */
int evaluatePostfix(const char *exp, int *answer) {
    int i = 0, a, b, result;
    top = -1;                               /* reset the stack */

    printf("\n%-10s %-12s %s\n", "Symbol", "Action", "Stack after step");
    printf("---------------------------------------------\n");

    while (exp[i] != '\0') {
        char ch = exp[i];

        if (isspace((unsigned char)ch)) {   /* skip spaces */
            i++;
            continue;
        }

        if (isdigit((unsigned char)ch)) {   /* read a full (multi-digit) number */
            int num = 0, start = i;
            while (isdigit((unsigned char)exp[i])) {
                num = num * 10 + (exp[i] - '0');
                i++;
            }
            if (!push(num))
                return 0;
            printf("%-10.*s %-12s ", i - start, exp + start, "push");
            displayStack();
            printf("\n");
            continue;
        }

        if (strchr("+-*/%^", ch) != NULL) { /* operator */
            if (!pop(&b) || !pop(&a)) {
                printf("Invalid expression: not enough operands for '%c'.\n", ch);
                return 0;
            }
            switch (ch) {
                case '+': result = a + b; break;
                case '-': result = a - b; break;
                case '*': result = a * b; break;
                case '/':
                    if (b == 0) {
                        printf("Error: division by zero.\n");
                        return 0;
                    }
                    result = a / b;
                    break;
                case '%':
                    if (b == 0) {
                        printf("Error: modulo by zero.\n");
                        return 0;
                    }
                    result = a % b;
                    break;
                case '^':
                    if (b < 0) {
                        printf("Error: negative exponent not supported.\n");
                        return 0;
                    }
                    result = power(a, b);
                    break;
            }
            push(result);
            printf("%-10c %-12s ", ch, "operate");
            displayStack();
            printf("   <- %d %c %d = %d\n", a, ch, b, result);
            i++;
            continue;
        }

        printf("Invalid character '%c' in expression.\n", ch);
        return 0;
    }

    /* exactly one value must remain */
    if (top != 0) {
        if (isEmpty())
            printf("Invalid expression: empty expression.\n");
        else
            printf("Invalid expression: too many operands.\n");
        return 0;
    }

    pop(answer);
    return 1;
}

int main() {
    char expression[200];
    int answer;

    printf("=== Postfix Expression Evaluation using Stack ===\n");
    printf("Enter operands/operators separated by spaces.\n");
    printf("Example: 10 2 8 * + 3 -     (answer = 23)\n");
    printf("Type 'exit' to quit.\n");

    while (1) {
        printf("\nEnter postfix expression: ");
        if (fgets(expression, sizeof(expression), stdin) == NULL)
            break;

        expression[strcspn(expression, "\n")] = '\0';   /* remove newline */

        if (strcmp(expression, "exit") == 0)
            break;
        if (strlen(expression) == 0)
            continue;

        if (evaluatePostfix(expression, &answer))
            printf("\nResult = %d\n", answer);
    }

    printf("Program ended.\n");
    return 0;
}