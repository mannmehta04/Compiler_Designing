%{
int vowels = 0, consonants = 0;
%}

%%

[aeiouAEIOU] { vowels++; }
[a-zA-Z] { consonants++; }
.|\n {  }

%%

int main() {
    printf("Enter text: ");
    yylex(); 
    printf("Vowels: %d\n", vowels);
    printf("Consonants: %d\n", consonants);
    return 0;
}
