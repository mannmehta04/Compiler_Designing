%{
#include <stdio.h>
#include <string.h>
%}

%%
[0-9]{2}CP[0-9]{3}  { printf("Computer Engineering\n"); }
[0-9]{2}EC[0-9]{3}  { printf("Electronics and Communication\n"); }
[0-9]{2}ME[0-9]{3}  { printf("Mechanical Engineering\n"); }
[0-9]{2}CE[0-9]{3}  { printf("Civil Engineering\n"); }
[0-9]{2}EE[0-9]{3}  { printf("Electrical Engineering\n"); }
.|\n               { }
%%

int main() {
    yylex();
    return 0;
}
