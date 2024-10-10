#include <iostream>
#include <stack>
#include <vector>
#include <sstream>

using namespace std;

struct Quadruple {
    string operator_;
    string operand1;
    string operand2;
    string result;
};

class QuadrupleGenerator {
private:
    vector<Quadruple> quadruples;
    int tempCount;

public:
    QuadrupleGenerator() : tempCount(0) {}

    void generateQuadruples(const string& postfix) {
        stack<string> operands;
        stringstream ss(postfix);
        string token;

        while (ss >> token) {
            if (isOperator(token)) {
                string op2 = operands.top(); operands.pop();
                string op1 = operands.top(); operands.pop();
                string tempVar = "t" + to_string(tempCount++);

                // Create a new quadruple
                Quadruple quad = {token, op1, op2, tempVar};
                quadruples.push_back(quad);

                // Push the temporary variable onto the stack
                operands.push(tempVar);
            } else {
                // Push operand onto the stack
                operands.push(token);
            }
        }
    }

    void displayQuadruples() {
        cout << "Quadruples:\n";
        cout << "Operator | Operand1 | Operand2 | Result\n";
        for (const auto& quad : quadruples) {
            cout << quad.operator_ << " | " << quad.operand1 << " | "
                 << quad.operand2 << " | " << quad.result << "\n";
        }
    }

private:
    bool isOperator(const string& token) {
        return token == "+" || token == "-" || token == "*" || token == "/";
    }
};

int main() {
    QuadrupleGenerator generator;
    string postfix;

    cout << "Enter a postfix expression (e.g., 'A B + C *'): ";
    getline(cin, postfix);

    generator.generateQuadruples(postfix);
    generator.displayQuadruples();

    return 0;
}