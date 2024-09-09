#include <iostream>
#include <vector>
#include <string>

using namespace std;

void eliminateLeftRecursion(const vector<string>& productions) {
    string nonTerminal = productions[0].substr(0, 1);
    vector<string> alpha, beta;
    
    for (const string& prod : productions) {
        if (prod[0] == nonTerminal[0]) {
            alpha.push_back(prod.substr(1));
        } else {
            beta.push_back(prod);
        }
    }

    if (!alpha.empty()) {
        cout << "Grammar has left recursion.\n";
        
        string newNonTerminal = nonTerminal + "'";

        for (const string& b : beta) {
            cout << nonTerminal << " -> " << b << newNonTerminal << endl;
        }
        for (const string& a : alpha) {
            cout << newNonTerminal << " -> " << a << newNonTerminal << endl;
        }
        cout << newNonTerminal << " -> ε";
    } else {
        cout << "Grammar does not have left recursion.\n";
        for (const string& prod : productions) {
            cout << nonTerminal << " -> " << prod << endl;
        }
    }
}

int main() {
    // A -> Aa | b
    vector<string> productions = {"Aa", "b"};
    
    cout << "Original Productions:\n";
    for (const string& prod : productions) {
        cout << "A -> " << prod << endl;
    }

    cout << "\nEliminated Left Recursion:\n";
    eliminateLeftRecursion(productions);

    return 0;
}
