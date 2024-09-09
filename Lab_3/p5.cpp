#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <string>

using namespace std;

map<char, vector<string>> pr;
map<char, set<char>> first, follow;

void computeFirst(char nonTerminal);
void computeFollow(char nonTerminal);

void computeFirst(char nonTerminal) {
    if (first[nonTerminal].size() > 0) return;

    for (const string& prod : pr[nonTerminal]) {
        if (islower(prod[0])) {
            first[nonTerminal].insert(prod[0]);
        } else {
            computeFirst(prod[0]);
            first[nonTerminal].insert(first[prod[0]].begin(), first[prod[0]].end());
        }
    }
}

void computeFollow(char nonTerminal) {
    if (follow[nonTerminal].size() > 0) return;

    for (const auto& p : pr) {
        for (const string& prod : p.second) {
            for (size_t i = 0; i < prod.size(); ++i) {
                if (prod[i] == nonTerminal) {
                    if (i + 1 < prod.size()) {
                        char nextSymbol = prod[i + 1];
                        if (islower(nextSymbol)) {
                            follow[nonTerminal].insert(nextSymbol);
                        } else {
                            computeFirst(nextSymbol);
                            follow[nonTerminal].insert(first[nextSymbol].begin(), first[nextSymbol].end());
                        }
                    }
                }
            }
        }
    }
}

int main() {
    int n = 4;
    string prods[] = {"S->AB", "A->a", "A->aA", "B->b"};

    for (const string& prod : prods) {
        pr[prod[0]].push_back(prod.substr(3));
    }

    for (const auto& p : pr) {
        computeFirst(p.first);
    }

    for (const auto& p : pr) {
        computeFollow(p.first);
    }

    cout << "FIRST SETS:\n";
    for (const auto& p : first) {
        cout << p.first << ": { ";
        for (char c : p.second) cout << c << " ";
        cout << "}\n";
    }

    cout << "FOLLOW SETS:\n";
    for (const auto& p : follow) {
        cout << p.first << ": { ";
        for (char c : p.second) cout << c << " ";
        cout << "}\n";
    }

    return 0;
}