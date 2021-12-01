#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <list>
#include <sstream>

using namespace std;

const int MOD = 1'000'000'000;


struct Node {
    Node(int value) : value(value), rightChild(nullptr),
        leftChild(nullptr), height(1), treeSum(value) {}

    Node(Node& anotherNodeToCopy) = default;

    int value;
    Node* leftChild;
    Node* rightChild;
    size_t height;
    size_t treeSum;


    size_t getLeftHeight() const {
        return leftChild == nullptr ? 0 : leftChild->height;
    }


    size_t getRightHeight() const {
        return rightChild == nullptr ? 0 : rightChild->height;
    }


    void update() {
        size_t leftChildHeight = getLeftHeight();
        size_t rightChildHeight = getRightHeight();
        height = max(leftChildHeight, rightChildHeight) + 1;

        size_t leftTreeSum = getLeftTreeSum();
        size_t rightTreeSum = getRightTreeSum();

        treeSum = leftTreeSum + rightTreeSum + value;

    }


    size_t getLeftTreeSum() {
        return leftChild == nullptr ? 0 : leftChild->treeSum;
    }


    size_t getRightTreeSum() {
        return rightChild == nullptr ? 0 : rightChild->treeSum;
    }
};


class AVLTree {
public:
    AVLTree() : root(nullptr) {}

    void insert(int value) {
        root = insert(root, value);
        root->update();
    }

    long long sum(int left, int right) {
        return (higherSum(left, true, root, 0) - higherSum(right, false, root, 0));
    }


private:
    Node* root;

    Node* insert(Node* currentNode, int value) {
        if (currentNode == nullptr) {
            return new Node(value);
        }
        else if (value < currentNode->value) {
            currentNode->leftChild = insert(currentNode->leftChild, value);
        }
        else if (value > currentNode->value) {
            currentNode->rightChild = insert(currentNode->rightChild, value);
        }
        currentNode->update();
        balance(currentNode);
        return currentNode;
    }


    void smallRotateRight(Node* currentNode) {
        Node* temporary = new Node(*currentNode);
        temporary->leftChild = currentNode->leftChild->rightChild;
        temporary->update();
        *currentNode = *currentNode->leftChild;
        currentNode->rightChild = temporary;
        currentNode->update();
    }


    void smallRotateLeft(Node* currentNode) {
        Node* temporary = new Node(*currentNode);
        temporary->rightChild = currentNode->rightChild->leftChild;
        temporary->update();
        *currentNode = *currentNode->rightChild;
        currentNode->leftChild = temporary;
        currentNode->update();
    }


    void balance(Node* currentNode) {
        int difference = currentNode->getLeftHeight() - currentNode->getRightHeight();

        if (difference > 1) {
            if (currentNode->leftChild->getRightHeight() >
                currentNode->leftChild->getLeftHeight()) {

                smallRotateLeft(currentNode->leftChild);
            }
            smallRotateRight(currentNode);
        }
        else if (difference < -1) {
            if (currentNode->rightChild->getLeftHeight() >
                currentNode->rightChild->getRightHeight()) {

                smallRotateRight(currentNode->rightChild);
            }
            smallRotateLeft(currentNode);
        }
    }

    long long higherSum(int border, bool isLeft, Node* currentNode, long long add) {
        if (currentNode == nullptr) {
            return add;
        }
        else if (currentNode->value == border) {
            return add + isLeft * currentNode->value + currentNode->getRightTreeSum();
        }
        else if (currentNode->value > border) {
            return higherSum(border, isLeft, currentNode->leftChild,
                currentNode->getRightTreeSum() + currentNode->value + add);
        }
        else {
            return higherSum(border, isLeft, currentNode->rightChild, add);
        }
    }
};



int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    AVLTree tree = AVLTree();

    size_t counter;
    char operation;
    char lastOperation = '+';
    long long lastOperationResult;
    int value;
    int secondValue;

    cin >> counter;


    for (size_t i = 0; i < counter; i++) {
        cin >> operation >> value;

        if (operation == '+') {
            if (lastOperation == '?') {
                tree.insert(static_cast<int>((lastOperationResult + value) % MOD));
            }
            else {
                tree.insert(value);
            }
        }
        else if (operation == '?') {
            cin >> secondValue;
            lastOperationResult = tree.sum(value, secondValue);
            cout << lastOperationResult << "\n";

        }
        lastOperation = operation;
    }
    return 0;
}
