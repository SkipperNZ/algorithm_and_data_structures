#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <list>
#include <sstream>

using namespace std;


struct Node {
    Node(int value, int priority) :
        value(value),
        priority(priority),
        leftChild(nullptr),
        rightChild(nullptr),
        treeSize(1) {};

    int value;
    int priority;
    size_t treeSize;

    Node* leftChild;
    Node* rightChild;


    void fixTreeSize() {
        this->treeSize = this->getLeftTreeSize() + this->getRightTreeSize() + 1;
    }


    size_t getLeftTreeSize() const {
        return leftChild == nullptr ? 0 : leftChild->treeSize;
    }


    size_t getRightTreeSize() const {
        return rightChild == nullptr ? 0 : rightChild->treeSize;
    }
};


class Treap {
public:
    Treap() : root(nullptr) {};


    void insert(size_t index, int value) {
        pair<Node*, Node*> pairOfTree = split(root, index);
        Node* tempNode = new Node(value, rand());
        Node* leftPart = merge(pairOfTree.first, tempNode);
        root = merge(leftPart, pairOfTree.second);
    }


    void del(int index) {
        pair<Node*, Node*> firstSplitPair = split(root, index);
        pair<Node*, Node*> secondSplitPair = split(firstSplitPair.first, index - 1);
        root = merge(secondSplitPair.first, firstSplitPair.second);
        delete secondSplitPair.second;

    }


    void printTree() {
        if (root != nullptr) {
            cout << root->treeSize << "\n";
            recursPrintTree(root);
        }
        else {
            cout << 0;
        }
    }


private:
    Node* root;

    void recursPrintTree(Node* currentRoot) {
        if (currentRoot != nullptr) {
            recursPrintTree(currentRoot->leftChild);
            cout << currentRoot->value << " ";
            recursPrintTree(currentRoot->rightChild);
        }
    }


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


    pair<Node*, Node*> split(Node* currentRoot, int index) {
        if (currentRoot == nullptr) {
            return { nullptr, nullptr };
        }
        if (currentRoot->getLeftTreeSize() + 1 == index) {
            Node* rightSubtree = currentRoot->rightChild;
            currentRoot->rightChild = nullptr;
            currentRoot->fixTreeSize();

            return { currentRoot, rightSubtree };
        }
        else if (currentRoot->getLeftTreeSize() + 1 > index) {
            pair<Node*, Node*> pairOfTree = split(currentRoot->leftChild, index);
            currentRoot->leftChild = pairOfTree.second;
            currentRoot->fixTreeSize();
            return { pairOfTree.first, currentRoot };
        }
        else {
            int subSomefingInLeft = index - (currentRoot->getLeftTreeSize() + 1);
            pair<Node*, Node*> pairOfTree = split(currentRoot->rightChild, subSomefingInLeft);
            currentRoot->rightChild = pairOfTree.first;
            currentRoot->fixTreeSize();
            return { currentRoot,  pairOfTree.second };
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
            firstTree->fixTreeSize();
            return firstTree;
        }
        else {
            secondTree->leftChild = merge(firstTree, secondTree->leftChild);
            secondTree->fixTreeSize();
            return secondTree;
        }
    }
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    Treap tree = Treap();

    size_t vecSize;
    size_t counter;
    cin >> vecSize >> counter;

    string operation;

    int firstValue;
    int secondValue;

    for (size_t i = 0; i < vecSize; i++) {
        cin >> firstValue;
        tree.insert(i, firstValue);
    }

    for (size_t i = 0; i < counter; i++) {
        cin >> operation >> firstValue;
        if (operation == "add") {
            cin >> secondValue;
            tree.insert(firstValue, secondValue);
        }
        else {
            tree.del(firstValue);
        }
    }
    tree.printTree();

    return 0;
}