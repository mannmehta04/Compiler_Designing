%{
  #include<stdio.h>
  int tokencount = 0;
%}
del [,|;]
keyword "int"|"float"|"double"|"char"
digit [0-9]
letter [a-zA-Z]
op [+|*|/]
op1 "-"
un [_]
sc [@|$|&|#|!]
%%

({keyword})+ {printf("%s - keyword\n",yytext); tokencount++;}
({digit})+ {printf("%s - digit\n",yytext);tokencount++;}
({op}|{op1}) {printf("%s - operator\n",yytext);tokencount++;}
({letter}|{un})(({letter}|{digit})*)+ {printf("%s - identifier\n",yytext);tokencount++;}
({sc}|({digit})*)+({letter})+ {printf("%s - invalid token\n",yytext);tokencount++;}
({del})+ {printf("%s - delimiter\n",yytext);tokencount++;}

%%

int main(void)
{
  yylex();
  printf("Total Tokens: %d", tokencount);
  return 0;
}