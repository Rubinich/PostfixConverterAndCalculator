#include <iostream>
#include <stack>
#include <string> //for stod() -> converts string to double

int priority(char c) {
    if (c == '*' || c == '/')
        return 2;
    if (c == '+' || c == '-')
        return 1;
    return 0;
}

double performOperation(double a, double b, char operation) {
    switch (operation) {
    case '+':
        return (a + b);
    case '-':
        return (a - b);
    case '*':
        return (a * b);
    case '/':
        return (a / b);
    }
}

std::string infixToPostfix(std::string infix) {
    std::stack<char> operations;
    std::string postfix;
    for (int i = 0; i < infix.length(); i++) {
        char c = infix[i];
        if (isdigit(c)) {
            postfix += c;
            // if the next number is operation make a whitespace -> esthetic output
            if (isdigit(c) != isdigit(infix[i+1]))
                postfix += ' ';
        }
        else if (c == '(')
            operations.push(c);
        else if (c == ')') {
            /* if we reach ')' we have to save all operators to operators stack till '('*/
            while (!operations.empty() && operations.top() != '(') {
                postfix += operations.top();
                postfix += ' ';
                operations.pop();
            }
            //removes ')'
            operations.pop();
        }
        else {
            /*if the character in stack has higher priroity than the character in
            infix we have to save operations and pop them till we reach operation in stack
            that's smaller that infix operation*/
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

double postfixEvaluation(std::string postfix) {
    std::stack<double> numbers;
    for (int i = 0; i < postfix.length(); i++) {
        if (isdigit(postfix[i])) {
            std::string number;
            //checking for multi-digit numbers
            while (i < postfix.length() && isdigit(postfix[i])) {
                number += postfix[i];
                i++;
            }
            //removes the values of i by 1 that was added in while -> postfix[i] isn't a number any more
            i--;
            numbers.push(stod(number));
        }
        else if (postfix[i] == ' ') {
            continue;
        }
        else {
            double b = numbers.top();
            numbers.pop();
            double a = numbers.top();
            numbers.pop();
            char operation = postfix[i];
            numbers.push(performOperation(a, b, operation));
        }
    }
    return numbers.top();
}

int main() {
    std::string infix;
    std::cout << "Enter infix: ";
    std::cin >> infix;
    std::string postfix = infixToPostfix(infix);
    std::cout << "Postfix: " << postfix << std::endl;
    std::cout << "Solution: " << postfixEvaluation(postfix) << std::endl;
    return 0;
}