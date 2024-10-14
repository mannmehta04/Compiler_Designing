%{
#include <stdio.h>
#include <string.h>
%}

%%
[a-zA-Z]+  {
                printf("Length of '%s' is %lu\n", yytext, strlen(yytext));
           }
.|\n       { }
%%

int main() {
    yylex();
    return 0;
}
