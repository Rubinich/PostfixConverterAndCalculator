#include <iostream>
#include <stack>
using namespace std;

int priority(char c) {
    if (c == '*' || c == '/')
        return 2;
    if (c == '+' || c == '-')
        return 1;
    return 0;
}

string InfixToPostfix(string infix) {
    stack<char> operations;
    string postfix;
    for (int i = 0; i < infix.length(); i++) {
        char c = infix[i];
        if (isdigit(c)) {
            postfix += c;
            // if the next number is operation make a whitespace
            if (isdigit(c) != isdigit(infix[i+1]))
                postfix += ' ';
        }
        else if (c == '(')
            operations.push(c);
        else if (c == ')') {
            /* if we reach ')' we have to save and pop all operations
            sorted by priority*/
            while (!operations.empty() && operations.top() != '(') {
                postfix += operations.top();
                postfix += ' ';
                operations.pop();
            }
            operations.pop();
        }
        else {
            /*if the character in stack has higher priroity than the character in
            infix we have to save them and pop all the characters with highter of
            equal priroty*/
            while (!operations.empty() && priority(c) <= priority(operations.top())) {
                postfix += operations.top();
                postfix += ' ';
                operations.pop();
            }
            // pushing new operation from string
            operations.push(c);
        }
    }
    // to get rid of leftovers(operations)
    while (!operations.empty()) {
        postfix += operations.top();
        postfix += ' ';
        operations.pop();
    }
    return postfix;
}

double PostfixEvaluation(string postfix) {
    stack<int> numbers;
    for (int i = 0; i < postfix.length();) {
        char  c = postfix[i];
        if (isdigit(c)) {
            numbers.push(c - '0');
            i++;
        }
        else if (c == ' ')
            i++;
        else {
            // second number
            int b = numbers.top();
            numbers.pop();
            // first number
            int a = numbers.top();
            numbers.pop();
            switch (c) {
            case '+': numbers.push(a + b); break;
            case '-': numbers.push(a - b); break;
            case '*': numbers.push(a * b); break;
            case '/': numbers.push(a / b); break;
            }
            i++;
        }
    }
    return numbers.top();
}

int main() {
    string infix;
    cout << "Enter infix: ";
    cin >> infix;
    string postfix = InfixToPostfix(infix);
    cout << "Postfix: " << postfix << endl;
    cout << "Solution: " << PostfixEvaluation(postfix) << endl;
    return 0;
}