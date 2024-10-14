%{
#include <stdio.h>
#include <string.h>

int a = 0;  // Total number
int b = 0;  // Current number (hundreds, tens, ones)
int c = 0;  // Temporary value for thousands
%}

ones       "one"|"two"|"three"|"four"|"five"|"six"|"seven"|"eight"|"nine"
teens      "eleven"|"twelve"|"thirteen"|"fourteen"|"fifteen"|"sixteen"|"seventeen"|"eighteen"|"nineteen"
tens       "ten"|"twenty"|"thirty"|"forty"|"fifty"|"sixty"|"seventy"|"eighty"|"ninety"
hundred    "hundred"
thousand   "thousand"

%%

{ones} { 
    b += strcmp(yytext, "one") == 0 ? 1 :
         strcmp(yytext, "two") == 0 ? 2 :
         strcmp(yytext, "three") == 0 ? 3 :
         strcmp(yytext, "four") == 0 ? 4 :
         strcmp(yytext, "five") == 0 ? 5 :
         strcmp(yytext, "six") == 0 ? 6 :
         strcmp(yytext, "seven") == 0 ? 7 :
         strcmp(yytext, "eight") == 0 ? 8 : 9;
}

{teens} { 
    b += strcmp(yytext, "eleven") == 0 ? 11 :
         strcmp(yytext, "twelve") == 0 ? 12 :
         strcmp(yytext, "thirteen") == 0 ? 13 :
         strcmp(yytext, "fourteen") == 0 ? 14 :
         strcmp(yytext, "fifteen") == 0 ? 15 :
         strcmp(yytext, "sixteen") == 0 ? 16 :
         strcmp(yytext, "seventeen") == 0 ? 17 :
         strcmp(yytext, "eighteen") == 0 ? 18 : 19;
}

{tens} {
    b += strcmp(yytext, "ten") == 0 ? 10 :
         strcmp(yytext, "twenty") == 0 ? 20 :
         strcmp(yytext, "thirty") == 0 ? 30 :
         strcmp(yytext, "forty") == 0 ? 40 :
         strcmp(yytext, "fifty") == 0 ? 50 :
         strcmp(yytext, "sixty") == 0 ? 60 :
         strcmp(yytext, "seventy") == 0 ? 70 :
         strcmp(yytext, "eighty") == 0 ? 80 : 90;
}

{hundred} { b *= 100; }

{thousand} { 
    a += b;  // Add the current value to total for thousands
    a *= 1000;  // Multiply the total by 1000
    b = 0;  // Reset current number
}

[ \t\n]+ { /* Skip whitespace */ }

. { printf("Invalid input: %s\n", yytext); }  // Handle invalid input

%%

int main() {
    printf("Enter number words: ");
    yylex();
    a += b;  // Add any remaining value in b to total
    printf("Number: %d\n", a);
    return 0;
}
