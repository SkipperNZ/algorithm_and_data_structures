#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int EMPTY_VEC_CAPACITY = 8;

class MyQueue {
public:
    MyQueue() : begin(0),
        end(0),
        capacity(EMPTY_VEC_CAPACITY),
        arrPtr(new int[EMPTY_VEC_CAPACITY]) {}

    void push(const int& value) {
        *(arrPtr + end) = value;
        end = next(end);
        if (end == begin) {
            changeCapacity(capacity * 2);
        }
    }

    int pop() {
        int value = *(arrPtr + begin);
        begin = next(begin);
        int actualSize = size();
        if (actualSize >= EMPTY_VEC_CAPACITY && actualSize == capacity / 4) {
            changeCapacity(capacity / 2);
        }

        return value;
    }

private:
    int next(int i) {
        return (i + 1) % capacity;
    }

    int size() {
        return (end + capacity - begin) % capacity;
    }

    void changeCapacity(int newCapacity) {
        int* newArr = new int[newCapacity];

        for (auto i = 0; i < capacity; i++) {
            *(newArr + i) = *(arrPtr + (begin + i) % capacity);
        }

        delete[] arrPtr;
        arrPtr = newArr;
        begin = 0;
        end = capacity;
        capacity = newCapacity;
    }

    int begin;
    int end;
    int capacity;
    int* arrPtr;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    MyQueue q;

    int m;
    cin >> m;

    for (auto i = 0; i < m; i++) {
        char operation;
        cin >> operation;

        if (operation == '-') {
            cout << q.pop() << "\n";
        }
        else {
            int digit;
            cin >> digit;
            q.push(digit);
        }
    }

    return 0;
}