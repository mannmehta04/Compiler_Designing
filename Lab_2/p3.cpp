#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

map<string, vector<string>> leftFactor(const map<string, vector<string>>& grammar) {
    map<string, vector<string>> factoredGrammar;

    for (const auto& [nonTerminal, productions] : grammar) {
        string prefix = productions[0];

        for (const string& prod : productions) {
            size_t i = 0;
            while (i < prefix.size() && i < prod.size() && prefix[i] == prod[i]) ++i;
            prefix = prefix.substr(0, i);
        }

        if (prefix.empty()) {
            factoredGrammar[nonTerminal] = productions;
        } else {
            vector<string> newProductions, factoredProductions;
            for (const string& prod : productions) {
                if (prod.substr(0, prefix.size()) == prefix) {
                    string suffix = prod.substr(prefix.size());
                    factoredProductions.push_back(suffix.empty() ? "ε" : suffix);
                } else {
                    newProductions.push_back(prod);
                }
            }

            string newNonTerminal = nonTerminal + "'";
            factoredGrammar[nonTerminal].push_back(prefix + newNonTerminal);
            factoredGrammar[newNonTerminal] = factoredProductions;

            if (!newProductions.empty()) {
                factoredGrammar[nonTerminal].insert(factoredGrammar[nonTerminal].end(), newProductions.begin(), newProductions.end());
            }
        }
    }

    return factoredGrammar;
}

int main() {
    map<string, vector<string>> grammar = {
        {"S", {"iEtS", "iEtSeS", "a"}},
        {"E", {"b"}}
    };

    map<string, vector<string>> factoredGrammar = leftFactor(grammar);

    for (const auto& [nonTerminal, productions] : factoredGrammar) {
        cout << nonTerminal << " -> ";
        for (size_t i = 0; i < productions.size(); ++i) {
            cout << productions[i] << (i < productions.size() - 1 ? " | " : "");
        }
        cout << endl;
    }

    return 0;
}
