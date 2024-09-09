#include <iostream>
#include <vector>
#include <map>
#include <set>
using namespace std;

map<char, vector<string>> grammar = {
    {'S', {"AB"}},
    {'A', {"a", "ε"}},
    {'B', {"b"}}
};

map<char, set<char>> first, follow;

void computeFirst(char c) {
    for (const string& s : grammar[c]) {
        if (islower(s[0])) first[c].insert(s[0]);
        else if (isupper(s[0])) {
            computeFirst(s[0]);
            first[c].insert(first[s[0]].begin(), first[s[0]].end());
        }
        if (s == "ε") first[c].insert('ε');
    }
}

void computeFollow(char c) {
    if (c == 'S') follow[c].insert('$');
    for (const auto& [nonTerm, productions] : grammar) {
        for (const string& s : productions) {
            size_t pos = s.find(c);
            if (pos != string::npos) {
                if (pos + 1 < s.size()) {
                    char next = s[pos + 1];
                    if (islower(next)) follow[c].insert(next);
                    else {
                        for (char f : first[next]) {
                            if (f != 'ε') follow[c].insert(f);
                        }
                        if (first[next].count('ε')) computeFollow(nonTerm);
                        for (char f : follow[nonTerm]) follow[c].insert(f);
                    }
                } else if (nonTerm != c) {
                    computeFollow(nonTerm);
                    for (char f : follow[nonTerm]) follow[c].insert(f);
                }
            }
        }
    }
}

bool isLL1() {
    for (const auto& [nonTerm, productions] : grammar) {
        set<char> seen;
        for (const string& s : productions) {
            char start = s[0];
            if (seen.count(start)) return false;
            seen.insert(start);
            if (s == "ε") {
                for (char f : follow[nonTerm]) if (seen.count(f)) return false;
            }
        }
    }
    return true;
}

int main() {
    for (char i = 'A'; i <= 'Z'; i++) {
        computeFirst(i);
        computeFollow(i);
    }
    
    cout << (isLL1() ? "The grammar is LL(1)" : "The grammar is not LL(1)") << endl;
    return 0;
}