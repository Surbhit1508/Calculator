#include <bits/stdc++.h>
#include <iostream>
#include <sstream>
#include <stack>
#include <cctype>
#include <cmath>
using namespace std;

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

int precedence(char op) {
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    if (op == '^')
        return 3;
    return 0;
}

double applyOperator(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        case '^': return pow(a, b);
        default: return 0;
    }
}

double evaluateExpression(const string& expression) {
    stack<double> values;
    stack<char> operators;

    for (char c : expression) {
        if (isspace(c)) {
            continue;
        } else if (isdigit(c)) {
            stringstream ss;
            ss << c;
            while (isdigit(expression.peek())) {
                ss << expression.get();
            }
            double num;
            ss >> num;
            values.push(num);
        } else if (c == '(') {
            operators.push(c);
        } else if (c == ')') {
            while (!operators.empty() && operators.top() != '(') {
                double b = values.top(); values.pop();
                double a = values.top(); values.pop();
                char op = operators.top(); operators.pop();
                values.push(applyOperator(a, b, op));
            }
            operators.pop(); // Remove '('
        } else if (isOperator(c)) {
            while (!operators.empty() && precedence(operators.top()) >= precedence(c)) {
                double b = values.top(); values.pop();
                double a = values.top(); values.pop();
                char op = operators.top(); operators.pop();
                values.push(applyOperator(a, b, op));
            }
            operators.push(c);
        }
    }

    while (!operators.empty()) {
        double b = values.top(); values.pop();
        double a = values.top(); values.pop();
        char op = operators.top(); operators.pop();
        values.push(applyOperator(a, b, op));
    }

    return values.top();
}

int main() {
    cout << "Advanced Calculator" << endl;
    cout << "Enter an expression (e.g., 2 + 3 * 4 / ( 1 - 5 ) ^ 2): ";
    
    string expression;
    getline(cin, expression);

    double result = evaluateExpression(expression);
    cout << "Result: " << result << endl;

    return 0;
}
/*This code defines a more advanced calculator that handles basic arithmetic operations, parentheses, and exponentiation. It evaluates expressions in infix notation using the Shunting Yard algorithm. Please note that this is a simplified version and does not cover all edge cases or error handling scenarios. For a production-level calculator, further enhancements and error handling would be necessary.*/