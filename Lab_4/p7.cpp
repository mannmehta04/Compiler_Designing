#include <iostream>
#include <stack>
#include <sstream>
#include <vector>

using namespace std;

bool isOperator(const string& token) {
    return token == "+" || token == "*";
}

bool isIdentifier(const string& token) {
    return token == "id";
}

int main() {
    stack<string> stk;
    string input;

    cout << "Enter an expression (e.g., 'id + id * id'): ";
    getline(cin, input);
    stringstream ss(input);
    vector<string> tokens;
    string token;

    // Tokenize the input
    while (ss >> token) {
        tokens.push_back(token);
    }

    size_t index = 0;

    while (true) {
        // Check for acceptance
        if (stk.size() == 1 && stk.top() == "S" && index == tokens.size()) {
            cout << "Input accepted!" << endl;
            return 0;
        }

        // Shift action
        if (index < tokens.size()) {
            stk.push(tokens[index++]);
            cout << "Shift: " << stk.top() << endl;
        }
        // Reduce action
        else if (stk.size() >= 3) {
            string top1 = stk.top(); stk.pop();
            string top2 = stk.top(); stk.pop();
            string top3 = stk.top(); stk.pop();

            if (isOperator(top2) && isIdentifier(top1) && isIdentifier(top3)) {
                stk.push("S");
                cout << "Reduce to S" << endl;
            } else {
                // Push back if no reduction possible
                stk.push(top3); stk.push(top2); stk.push(top1);
            }
        } else {
            cout << "String Rejected" << endl;
            return 1;
        }
    }
}