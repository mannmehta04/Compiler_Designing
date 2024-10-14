%{
#include <stdio.h>
#include <stdlib.h>
%}

%%
[0-9]+  {
            int number = atoi(yytext);
            if (number % 7 == 0) {
                printf("%d is divisible by 7\n", number);
            } else {
                printf("%d is not divisible by 7\n", number);
            }
        }
.|\n    { }
%%

int main() {
    yylex();
    return 0;
}
