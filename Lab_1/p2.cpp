#include <iostream>
#include <string>
using namespace std;

bool isDFAAccepted(string input) {
    int state = 0;
    
    for (char c : input) {
        if (state == 0) {
            if (c == '0') state = 0;
            else if (c == '1') state = 1;
            else return false;
        } else if (state == 1) {
            if (c == '0') state = 2;
            else if (c == '1') state = 1;
            else return false;
        } else if (state == 2) {
            if (c == '0') state = 0;
            else if (c == '1') state = 3;
            else return false;
        } else if (state == 3) {
            if (c == '0') state = 2;
            else if (c == '1') state = 1;
            else return false;
        }
    }
    
    return state == 2;
}

int main() {
    string input;
    cout << "Enter the input string: ";
    cin >> input;
    
    if (isDFAAccepted(input)) {
        cout << "The input string is accepted by the DFA." << endl;
    } else {
        cout << "The input string is not accepted by the DFA." << endl;
    }
    
    return 0;
}