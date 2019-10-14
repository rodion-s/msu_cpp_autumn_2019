/*
 EXPR     --> TERM{+TERM | -TERM}
 TERM     --> FACTOR{*FACTOR | /FACTOR}
 FACTOR     --> -FACTOR | NUMBER
 NUMBER --> 0|1|....|INT_MAX
*/
#include <iostream>
#include <stack>
#include <stdexcept>
#include <string>
using namespace std;

void GET_LEX(const char *input, int &idx) {
    while (isspace((unsigned char)input[idx++]));
}
void NUMBER(const char *input, int &idx, stack<int> &my_stack) {
    if (!isdigit((unsigned char)input[idx])) {
        throw invalid_argument(string("Error on lexeme: ") + input[idx]);
    }
    int current_num = 0;
    while (isdigit((unsigned char)input[idx])) {
        current_num = current_num * 10 + (input[idx++] - '0');
    }
    my_stack.push(current_num);
    while (isspace((unsigned char)input[idx])) {
        ++idx;
    }
}
void FACTOR(const char *input, int &idx, stack<int> &my_stack) {
    while (isspace((unsigned char)input[idx])) {
        ++idx;
    }
    if (input[idx] == '-') {
        ++idx;
        FACTOR(input, idx, my_stack);
        int op = my_stack.top(); my_stack.pop();
        my_stack.push(-op);
    } else {
        NUMBER(input, idx, my_stack);
    }
}
void TERM(const char *input, int &idx, stack<int> &my_stack) {
    FACTOR(input, idx, my_stack);
    while (input[idx] == '*' || input[idx] == '/') {
        char temp = input[idx];
        GET_LEX(input, idx);
        FACTOR(input, idx, my_stack);
        int op2 = my_stack.top(); my_stack.pop();
        int op1 = my_stack.top(); my_stack.pop();
        if (temp == '*') {
            my_stack.push(op1 * op2);
        } else if (temp == '/') {
            if (op2 == 0) {
                throw logic_error("Error: division by zero");
            }
            my_stack.push(op1 / op2);
        }
    }
}

void EXPR(const char *input, int &idx, stack<int> &my_stack) {
    TERM(input, idx, my_stack);
    while (input[idx] == '+' || input[idx] == '-') {
        char temp = input[idx];
        GET_LEX(input, idx);
        TERM(input, idx, my_stack);
        int op2 = my_stack.top(); my_stack.pop();
        int op1 = my_stack.top(); my_stack.pop();
        if (temp == '-') {
            my_stack.push(op1 - op2);
        } else if (temp == '+') {
            my_stack.push(op1 + op2);
        }
    }
    if (input[idx]) {
        throw invalid_argument(string("Error on lexeme: ") + input[idx]);
    }
}
int main(int argc, char **argv) {
    int idx = 0;
    while (isspace((unsigned char)argv[1][idx])) {
        ++idx;
    }
    stack<int> my_stack;
    try {
        EXPR(argv[1], idx, my_stack);
    } catch (invalid_argument &exc) {
        cout << exc.what() << endl;
        return 1;
    } catch (logic_error &exc) {
        cout << exc.what() << endl;
        return 1;
    }
    cout << my_stack.top() << endl;
    return 0;
}