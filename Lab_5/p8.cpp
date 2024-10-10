#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Symbol {
    string name;
    string type;
    int scope; // For simplicity, using an integer to represent scope
};

class SymbolTable {
private:
    vector<vector<Symbol>> table; // Hash table with separate chaining
    int size;

    int hashFunction(const string& name) {
        int hash = 0;
        for (char ch : name) {
            hash += ch; // Simple hash function
        }
        return hash % size;
    }

public:
    SymbolTable(int s) : size(s) {
        table.resize(size);
    }

    void insert(const string& name, const string& type, int scope) {
        int index = hashFunction(name);
        for (const auto& symbol : table[index]) {
            if (symbol.name == name) {
                cout << "Symbol '" << name << "' already exists.\n";
                return; // Prevent duplicates
            }
        }
        table[index].push_back({name, type, scope});
        cout << "Inserted: " << name << " of type " << type << " in scope " << scope << endl;
    }

    void lookup(const string& name) {
        int index = hashFunction(name);
        for (const auto& symbol : table[index]) {
            if (symbol.name == name) {
                cout << "Found: " << name << " of type " << symbol.type << " in scope " << symbol.scope << endl;
                return;
            }
        }
        cout << "Symbol '" << name << "' not found.\n";
    }
};

int main() {
    SymbolTable symTable(10); // Create a symbol table with size 10

    symTable.insert("x", "int", 1);
    symTable.insert("y", "float", 1);
    symTable.insert("func", "void", 0);
    
    symTable.lookup("x");
    symTable.lookup("y");
    symTable.lookup("z"); // Not found

    return 0;
}