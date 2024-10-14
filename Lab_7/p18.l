%{
#include "y.tab.h"
%}

%%
[0-9]+      { yylval = atoi(yytext); return NUMBER; }
[\t]        { }
[-+*/()]    { return yytext[0]; }
\n          { return 0; }
.           { printf("Invalid character: %c\n", yytext[0]); }
%%

int yywrap() {
    return 1;
}
