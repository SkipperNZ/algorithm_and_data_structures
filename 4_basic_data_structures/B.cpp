#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <sstream>

using namespace std;

int EMPTY_VEC_CAPACITY = 8;

class Stack {
public:
    Stack() : capacity(EMPTY_VEC_CAPACITY),
        size(0),
        arrPtr(new int[EMPTY_VEC_CAPACITY]) {}

    void push(const int& value) {
        *(arrPtr + size) = value;
        size++;
        if (size == capacity) {
            changeCapacity(capacity * 2);
        }
    }

    int pop() {
        size--;
        int value = *(arrPtr + size);
        if (size == capacity / 4) {
            changeCapacity(capacity / 2);
        }

        return value;
    }

private:
    void changeCapacity(int newCapacity) {
        int* newArr = new int[newCapacity];

        for (auto i = 0; i < size; i++) {
            *(newArr + i) = *(arrPtr + i);
        }

        delete[] arrPtr;
        arrPtr = newArr;
        capacity = newCapacity;
    }

    int capacity;
    int size;
    int* arrPtr;
};

int makeOperation(Stack& stk, const string& operand) {
    int second = stk.pop();
    int first = stk.pop();
    if (operand == "*") {
        return first * second;
    }
    else if (operand == "+") {
        return first + second;
    }
    else {
        return first - second;
    }
}

int main() {
    string element;

    string expression;
    getline(cin, expression);

    stringstream ss;
    ss << expression;

    Stack stk;

    while (getline(ss, element, ' ')) {
        if (element == "*") {
            stk.push(makeOperation(stk, element));
        }
        else if (element == "+") {
            stk.push(makeOperation(stk, element));
        }
        else if (element == "-") {
            stk.push(makeOperation(stk, element));
        }
        else {
            int digit = stoi(element);
            stk.push(digit);
        }
    }

    cout << stk.pop() << endl;

    return 0;
}