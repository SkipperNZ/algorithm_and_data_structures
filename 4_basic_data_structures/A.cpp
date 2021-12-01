#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

struct Node {
    Node(int val, Node* np, Node* nmp) :
        value(val), nextPtr(np), nextMinPtr(nmp) {}

    int value;
    Node* nextPtr;
    Node* nextMinPtr;
};

class Stack {
public:
    Stack() :
        headPtr(nullptr),
        minPtr(nullptr) {}

    void push(const int& value) {
        Node* newNode = new Node(value, headPtr, minPtr);
        headPtr = newNode;

        if (minPtr == nullptr || value < (*minPtr).value) {
            minPtr = newNode;
        }
    }

    void pop() {
        Node* oldHeadPtr = headPtr;
        headPtr = (*oldHeadPtr).nextPtr;
        minPtr = (*oldHeadPtr).nextMinPtr;
        delete oldHeadPtr;
    }

    int min() const {
        return (*minPtr).value;
    }

private:
    Node* headPtr;
    Node* minPtr;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    Stack s;
    int n;
    cin >> n;

    for (auto i = 0; i < n; i++) {
        int operation;
        cin >> operation;
        if (operation == 1) {
            int value;
            cin >> value;
            s.push(value);
        }
        else if (operation == 2) {
            s.pop();
        }
        else if (operation == 3) {
            cout << s.min() << endl;
        }
    }
    return 0;
}