%{
#include <stdio.h>
#include <stdlib.h>
%}

%token NUMBER

%%
calculation:
    expression '\n'  { printf("Result: %d\n", $1); }
    | /* empty */
    ;

expression:
    expression '+' term  { $$ = $1 + $3; }
    | expression '-' term  { $$ = $1 - $3; }
    | term
    ;

term:
    term '*' factor  { $$ = $1 * $3; }
    | term '/' factor  { 
            if($3 == 0) {
                printf("Error: Division by zero!\n");
                exit(1);
            }
            $$ = $1 / $3; 
        }
    | factor
    ;

factor:
    '(' expression ')'  { $$ = $2; }
    | NUMBER
    ;

%%
int main() {
    printf("Enter an expression: ");
    yyparse();
    return 0;
}

int yyerror(char *s) {
    printf("Error: %s\n", s);
    return 0;
}
