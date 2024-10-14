%{
#include <stdio.h>
#include <stdlib.h>

int yylex();
void yyerror(const char* s);

int result = 0; // Global variable to store result
%}

%option noyywrap

%%

[0-9]+         { return atoi(yytext); }  // Return the integer value directly
"+"            { return '+'; }
"-"            { return '-'; }
"*"            { return '*'; }
"/"            { return '/'; }
"("            { return '('; }
")"            { return ')'; }
[ \t\n]+       { /* Ignore whitespace */ }
.              { return yytext[0]; }  // Return any single character as is

%%

// Error handling function
void yyerror(const char* s) {
    fprintf(stderr, "Error: %s\n", s);
}

// Function to perform calculation
int calculate(int num1, char operator, int num2) {
    switch (operator) {
        case '+': return num1 + num2;
        case '-': return num1 - num2;
        case '*': return num1 * num2;
        case '/':
            if (num2 == 0) {
                yyerror("Division by zero");
                exit(1);
            }
            return num1 / num2;
        default: return 0;
    }
}

// Main function
int main() {
    int current_number = 0;
    char operator = '+'; // Default operator

    printf("Enter an expression: ");
    while (1) {
        int token = yylex();
        if (token == 0) break;  // End of input
        
        if (token >= 256) { // If it's a number
            current_number = token; // Token holds the number
            result = calculate(result, operator, current_number);
        } else if (token == '+' || token == '-' || token == '*' || token == '/') {
            operator = token; // Update operator
        } else if (token == '\n') {
            printf("Result: %d\n", result);
            result = 0;  // Reset for the next expression
            operator = '+';  // Reset operator for the next expression
            current_number = 0;
        } else {
            yyerror("Invalid token");
        }
    }

    return 0;
}
