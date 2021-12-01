#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <list>
#include <sstream>

using namespace std;


struct Node {
    Node(int value) : value(value), rightChild(nullptr),
        leftChild(nullptr), height(1), treeSize(1) {}

    Node(Node& anotherNodeToCopy) = default;

    int value;
    Node* leftChild;
    Node* rightChild;
    size_t height;
    size_t treeSize;


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

        size_t leftTreeSize = getLeftTreeSize();
        size_t rightTreeSize = getRightTreeSize();
        treeSize = leftTreeSize + rightTreeSize + 1;
    }


    size_t getLeftTreeSize() {
        return leftChild == nullptr ? 0 : leftChild->treeSize;
    }


    size_t getRightTreeSize() {
        return rightChild == nullptr ? 0 : rightChild->treeSize;
    }
};


class AVLTree {
public:
    AVLTree() : root(nullptr) {}

    void insert(int value) {
        root = insert(root, value);
        root->update();
    }


    void del(int value) {
        root = del(root, value);

        if (root != nullptr) {
            root->update();
            balance(root);
        }
    }


    int kmax(size_t k) {
        return kmax(k, root, 0)->value;
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


    Node* del(Node* currentNode, int value) {
        if (currentNode == nullptr) {
            return nullptr;
        }
        else if (value < currentNode->value) {
            currentNode->leftChild = del(currentNode->leftChild, value);
        }
        else if (value > currentNode->value) {
            currentNode->rightChild = del(currentNode->rightChild, value);
        }
        else if (currentNode->rightChild == nullptr &&
            currentNode->leftChild == nullptr) {
            return nullptr;
        }
        else if (currentNode->leftChild == nullptr) {
            Node* elementToDel = currentNode;
            currentNode = currentNode->rightChild;
            delete elementToDel;
        }
        else if (currentNode->rightChild == nullptr) {
            Node* elementToDel = currentNode;
            currentNode = currentNode->leftChild;
            delete elementToDel;
        }
        else {
            currentNode->value = findMax(currentNode->leftChild)->value;
            currentNode->leftChild = del(currentNode->leftChild, currentNode->value);
        }

        currentNode->update();
        balance(currentNode);
        return currentNode;
    }


    Node* findMax(Node* currentNode) {
        while (currentNode->rightChild != nullptr) {
            currentNode = currentNode->rightChild;
        }
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


    Node* kmax(size_t k, Node* currentNode, size_t discardedPart) {
        if (currentNode->getRightTreeSize() + discardedPart + 1 == k) {
            return currentNode;
        }
        else if (currentNode->getRightTreeSize() + discardedPart + 1 > k) {
            return kmax(k, currentNode->rightChild, discardedPart);
        }
        else {
            return kmax(k, currentNode->leftChild, discardedPart + currentNode->getRightTreeSize() + 1);
        }
    }
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    AVLTree tree = AVLTree();

    size_t counter;
    int value;
    int command;

    cin >> counter;

    for (size_t i = 0; i < counter; i++) {
        cin >> command >> value;
        if (command == 0) {
            cout << tree.kmax(value) << "\n";
        }
        else if (command == -1) {
            tree.del(value);
        }
        else if (command == 1) {
            tree.insert(value);
        }
    }
    return 0;
}