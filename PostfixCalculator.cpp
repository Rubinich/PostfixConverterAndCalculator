#include <iostream>
#include <stack>
using namespace std;

int priority(char c) {
    if (c == '+' || c == '-')
        return 1;
    if (c == '*' || c == '/')
        return 2;
    return 0;
}

string InfixToPostfix(string infix) {
    stack<char> operations;
    string postfix = "";
    for (int i = 0; i < infix.length(); i++) {
        char c = infix[i];
        if (isdigit(c)){
            postfix += c;
            //postfix += " ";
        } 
        else if (c == '(')
            operations.push(c);
        else if (c == ')') {
            while (!operations.empty() && operations.top() != '(') {
                postfix += operations.top();
                //postfix += " ";
                operations.pop();
            }
            operations.pop();
        }
        else {
            while (!operations.empty() && priority(c) <= priority(operations.top())) {
                postfix += operations.top();
                //postfix += " ";
                operations.pop();
            }
            operations.push(c);
        }
    }
    while (!operations.empty()) {
        postfix += operations.top();
        //postfix += " ";
        operations.pop();
    }
    return postfix;
}

int main() {
    string infix;
    cin >> infix;
    cout << "Postfix: " << InfixToPostfix(infix) << endl;
    return 0;
}