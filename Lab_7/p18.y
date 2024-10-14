%{
#include <stdio.h>
#include <stdlib.h>

#define MAX 100

void push(char);
char pop();
void printPostfix();

char stack[MAX];
int top = -1;
int postfixIndex = 0;
char postfix[MAX][MAX];

%}

%token NUMBER

%%
expression:
    expression '+' term   { push('+'); }
    | expression '-' term { push('-'); }
    | term
    ;

term:
    term '*' factor   { push('*'); }
    | term '/' factor { push('/'); }
    | factor
    ;

factor:
    '(' expression ')'  { /* No need to push parentheses */ }
    | NUMBER            { printf("%d ", $1); }
    ;

%%
void push(char op) {
    if (top < MAX - 1) {
        stack[++top] = op;
    } else {
        printf("Stack Overflow\n");
    }
}

char pop() {
    if (top >= 0) {
        return stack[top--];
    } else {
        printf("Stack Underflow\n");
        return '\0';
    }
}

void printPostfix() {
    while (top >= 0) {
        printf("%c ", pop());
    }
}

int main() {
    printf("Enter an infix expression: ");
    yyparse();
    printPostfix();
    printf("\n");
    return 0;
}

int yyerror(char *s) {
    printf("Error: %s\n", s);
    return 0;
}
