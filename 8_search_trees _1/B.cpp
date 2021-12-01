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
        leftChild(nullptr), height(1) {}

    Node(Node& anotherNodeToCopy) = default;

    int value;
    Node* leftChild;
    Node* rightChild;
    size_t height;

    size_t getLeftHeight() const {
        return leftChild == nullptr ? 0 : leftChild->height;
    }

    size_t getRightHeight() const {
        return rightChild == nullptr ? 0 : rightChild->height;
    }

    void updateHeight() {
        size_t leftChildHeight = getLeftHeight();
        size_t rightChildHeight = getRightHeight();
        height = max(leftChildHeight, rightChildHeight) + 1;
    }
};


class AVLTree {
public:
    AVLTree() : root(nullptr) {}

    void insert(int value) {
        root = insert(root, value);
        root->updateHeight();
    }


    void del(int value) {
        root = del(root, value);

        if (root != nullptr) {
            root->updateHeight();
            balance(root);
        }
    }


    bool exists(int value) {
        if (search(root, value) == nullptr) {
            return false;
        }
        else {
            return true;
        }
    }


    Node* next(int value) {
        Node* currentNode = root;
        Node* res = nullptr;

        while (currentNode != nullptr) {
            if (currentNode->value > value) {
                res = currentNode;
                currentNode = currentNode->leftChild;
            }
            else {
                currentNode = currentNode->rightChild;
            }
        }
        return res;
    }


    Node* prev(int value) {
        Node* currentNode = root;
        Node* res = nullptr;

        while (currentNode != nullptr) {
            if (currentNode->value < value) {
                res = currentNode;
                currentNode = currentNode->rightChild;
            }
            else {
                currentNode = currentNode->leftChild;
            }
        }
        return res;
    }


private:
    Node* root;

    Node* search(Node* currentNode, int value) {
        if (currentNode == nullptr) {
            return nullptr;
        }
        if (currentNode->value == value) {
            return currentNode;
        }
        else if (value < currentNode->value) {
            return search(currentNode->leftChild, value);
        }
        else {
            return search(currentNode->rightChild, value);
        }
    }


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
        currentNode->updateHeight();
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

        currentNode->updateHeight();
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
        temporary->updateHeight();
        *currentNode = *currentNode->leftChild;
        currentNode->rightChild = temporary;
        currentNode->updateHeight();
    }


    void smallRotateLeft(Node* currentNode) {
        Node* temporary = new Node(*currentNode);
        temporary->rightChild = currentNode->rightChild->leftChild;
        temporary->updateHeight();
        *currentNode = *currentNode->rightChild;
        currentNode->leftChild = temporary;
        currentNode->updateHeight();
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
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    AVLTree tree = AVLTree();

    int value;
    string command;

    while (cin >> command) {
        cin >> value;
        if (command == "insert") {
            tree.insert(value);
        }
        else if (command == "delete") {
            tree.del(value);
        }
        else if (command == "exists") {
            if (tree.exists(value)) {
                cout << "true" << "\n";
            }
            else {
                cout << "false" << "\n";
            }
        }
        else if (command == "next") {
            Node* ansver = tree.next(value);
            if (ansver == nullptr) {
                cout << "none" << "\n";
            }
            else {
                cout << ansver->value << "\n";
            }
        }
        else if (command == "prev") {
            Node* ansver = tree.prev(value);
            if (ansver == nullptr) {
                cout << "none" << "\n";
            }
            else {
                cout << ansver->value << "\n";
            }
        }
    }
    return 0;
}