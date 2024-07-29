#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_set>
#include <cctype>
using namespace std;

unordered_set<string> keywords = {
    "auto", "break", "case", "char", "const", "continue", "default", "do", "double", 
    "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register", 
    "return", "short", "signed", "sizeof", "static", "struct", "switch", "typedef", 
    "union", "unsigned", "void", "volatile", "while"
};

unordered_set<string> operators = {
    "+", "-", "*", "/", "%", "++", "--", "==", "!=", ">", "<", ">=", "<=", "&&", "||",
    "!", "&", "|", "^", "~", "<<", ">>", "=", "+=", "-=", "*=", "/=", "%=", "&=", "|=", 
    "^=", "<<=", ">>="
};

unordered_set<char> separators = {
    '(', ')', '{', '}', '[', ']', ';', ',', '.', '#'
};

// check if number
bool isNumber(const string& str) {
    for (char const &c : str) {
        if (isdigit(c) == 0) return false;
    }
    return true;
}

// seaprate token
vector<string> tokenize(const string &line) {
    vector<string> tokens;
    string token;
    stringstream ss(line);

    while (ss >> token) {
        tokens.push_back(token);
    }

    return tokens;
}

// identify token
void identifyTokens(const vector<string> &tokens) {
    for (const string &token : tokens) {
        if (keywords.find(token) != keywords.end()) {
            cout << token << " : Keyword" << endl;
        } else if (operators.find(token) != operators.end()) {
            cout << token << " : Operator" << endl;
        } else if (separators.find(token[0]) != separators.end()) {
            cout << token << " : Separator" << endl;
        } else if (isNumber(token)) {
            cout << token << " : Number" << endl;
        } else {
            cout << token << " : Identifier" << endl;
        }
    }
}

int main() {
    string line;
    cout << "Enter a line of C code: ";
    getline(cin, line);

    vector<string> tokens = tokenize(line);
    identifyTokens(tokens);

    return 0;
}
