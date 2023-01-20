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
            if (isdigit(c) != isdigit(infix[i+1]))
                postfix += ' ';
        }
        else if (c == '(')
            operations.push(c);
        else if (c == ')') {
            while (!operations.empty() && operations.top() != '(') {
                postfix += operations.top();
                postfix += ' ';
                operations.pop();
            }
            operations.pop();
        }
        else {
            while (!operations.empty() && priority(c) <= priority(operations.top())) {
                postfix += operations.top();
                postfix += ' ';
                operations.pop();
            }
            operations.push(c);
        }
    }
    while (!operations.empty()) {
        postfix += operations.top();
        postfix += ' ';
        operations.pop();
    }
    return postfix;
}

/*int MultiDigit(stack<int> numbers) {
    int number;
    while (!numbers.empty()) {

    }
    return number;
}*/

double PostfixEvaluation(string postfix) {
    stack<int> numbers;
    int t = 0;
    for (int i = 0; i < postfix.length();) {
        char  c = postfix[i];
        if (isdigit(c)) {
            numbers.push(c - '0');
            t++;
            i++;
        }
        else if (c == ' ')
            i++;
        else if (c == ' ' && isdigit(postfix[i-1])) {
            //MultiDigit(numbers);
            i++;
            t = 0;
        }
        else {
            int b = numbers.top();
            numbers.pop();
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
    cout << "Postfix: " << InfixToPostfix(infix) << endl;
    cout << "Solution: " << PostfixEvaluation(InfixToPostfix(infix)) << endl;
    return 0;
}