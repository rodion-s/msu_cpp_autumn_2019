/*
 S     --> T{+T | -T}
 T     --> F{*F | /F}
 F     --> -F | digit
 digit --> 0|1|....|INT_MAX
*/
#include <iostream>
#include <stack>
#include <stdexcept>
using namespace std;

void gc(char *input, int &idx) {
    while (isspace(input[idx++]));
}
void DIGIT(char *input, int &idx, stack<int> &my_stack) {
    static int current_num = 0;
    bool modified = false;
    while (isdigit((unsigned char)input[idx])) {
        modified = true;
        current_num = current_num * 10 + (input[idx++] - '0');
    }
    if (!modified) {
        throw invalid_argument("invalid_argument");
    }
    my_stack.push(current_num);
    current_num = 0;
    while (isspace(input[idx])) {
        ++idx;
    }
}
void F(char *input, int &idx, stack<int> &my_stack) {
    while (isspace(input[idx])) {
        ++idx;
    }
    if (input[idx] == '-') {
        ++idx;
        F(input, idx, my_stack);
        int op = my_stack.top(); my_stack.pop();
        my_stack.push(-op);
    } else {
        DIGIT(input, idx, my_stack);
    }
}
void T(char *input, int &idx, stack<int> &my_stack) {
    F(input, idx, my_stack);
    while (input[idx] == '*' || input[idx] == '/') {
        char temp = input[idx];
        gc(input, idx);
        F(input, idx, my_stack);
        int op2 = my_stack.top(); my_stack.pop();
        int op1 = my_stack.top(); my_stack.pop();
        if (temp == '*') {
            my_stack.push(op1 * op2);
        } else if (temp == '/') {
            my_stack.push(op1 / op2);
        }
    }
}

void S(char *input, int &idx, stack<int> &my_stack) {
    T(input, idx, my_stack);
    while (input[idx] == '+' || input[idx] == '-') {
        char temp = input[idx];
        gc(input, idx);
        T(input, idx, my_stack);
        int op2 = my_stack.top(); my_stack.pop();
        int op1 = my_stack.top(); my_stack.pop();
        if (temp == '-') {
            my_stack.push(op1 - op2);
        } else if (temp == '+') {
            my_stack.push(op1 + op2);
        }
    }
    if (input[idx]) {
        throw invalid_argument("invalid_argument");
    }
}
int main(int argc, char **argv) {
    int idx = 0;
    stack<int> my_stack;
    while (isspace(argv[1][idx])) {
        ++idx;
    }
    try {
        S(argv[1], idx, my_stack);
    } catch (const invalid_argument &exc) {
        cout << exc.what();
        return 1;
    }
    cout << my_stack.top();
    return 0;
}