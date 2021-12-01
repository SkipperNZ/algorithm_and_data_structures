#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <list>
#include <sstream>

using namespace std;


struct Node {
    Node(int value, int priority, Node* leftChild, Node* rightChild) :
        value(value),
        priority(priority),
        leftChild(leftChild),
        rightChild(rightChild) {};

    int value;
    int priority;

    Node* leftChild;
    Node* rightChild;
};



class Treap {
public:
    Treap() : root(nullptr) {};


    void insert(int value) {
        if (!exists(value)) {
            root = insert(root, value, rand());
            int jojo = 5;
        }

    }


    void del(int value) {
        root = del(root, value);
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


    pair<Node*, Node*> split(Node* currentRoot, int value) {
        if (currentRoot == nullptr) {
            return { nullptr, nullptr };
        }
        if (currentRoot->value > value) {
            pair<Node*, Node*> pairOfTree = split(currentRoot->leftChild, value);
            currentRoot->leftChild = pairOfTree.second;
            return { pairOfTree.first, currentRoot };
        }
        else {
            pair<Node*, Node*> pairOfTree = split(currentRoot->rightChild, value);
            currentRoot->rightChild = pairOfTree.first;
            return { currentRoot, pairOfTree.second };
        }
    }


    Node* merge(Node* firstTree, Node* secondTree) {
        if (firstTree == nullptr) {
            return secondTree;
        }
        else if (secondTree == nullptr) {
            return firstTree;
        }
        if (firstTree->priority > secondTree->priority) {
            firstTree->rightChild = merge(firstTree->rightChild, secondTree);
            return firstTree;
        }
        else {
            secondTree->leftChild = merge(firstTree, secondTree->leftChild);
            return secondTree;
        }
    }


    Node* insert(Node* currentRoot, int value, int priority) {
        if (currentRoot == nullptr || currentRoot->priority < priority) {
            pair<Node*, Node*> pairOfTree = split(currentRoot, value);
            Node* newSubTree = new Node(value, priority, pairOfTree.first, pairOfTree.second);
            return newSubTree;

        }
        else if (value > currentRoot->value) {
            currentRoot->rightChild = insert(currentRoot->rightChild, value, priority);
        }
        else if (value < currentRoot->value) {
            currentRoot->leftChild = insert(currentRoot->leftChild, value, priority);
        }
        return currentRoot;
    }


    Node* del(Node* currentRoot, int value) {
        if (currentRoot == nullptr) {
            return nullptr;
        }
        else if (value < currentRoot->value) {
            currentRoot->leftChild = del(currentRoot->leftChild, value);
        }
        else if (value > currentRoot->value) {
            currentRoot->rightChild = del(currentRoot->rightChild, value);
        }
        else {
            Node* tempNode = merge(currentRoot->leftChild, currentRoot->rightChild);
            delete currentRoot;
            currentRoot = tempNode;
        }
        return currentRoot;
    }
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    Treap tree = Treap();

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