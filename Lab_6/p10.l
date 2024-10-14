%{
  #include<stdio.h>
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

({keyword})+ {printf("%s - keyword\n",yytext);}
({digit})+ {printf("%s - digit\n",yytext);}
({op}|{op1}) {printf("%s - operator\n",yytext);}
({letter}|{un})(({letter}|{digit})*)+ {printf("%s - identifier\n",yytext);}
({sc}|({digit})*)+({letter})+ {printf("%s - invalid token\n",yytext);}
({del})+ {printf("%s - delimiter\n",yytext);}

%%

int main(void)
{
  yylex();
  return 0;
}