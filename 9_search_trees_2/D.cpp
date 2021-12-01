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
        treeSize(1),
        isReversed(false) {};

    int value;
    int priority;
    size_t treeSize;

    Node* leftChild;
    Node* rightChild;

    bool isReversed;


    void updateReverse() {
        if (this->isReversed) {
            this->reverse();
        }
    }


    void reverse() {
        this->isReversed = false;
        swap(this->leftChild, this->rightChild);
        if (this->leftChild != nullptr) {
            this->leftChild->isReversed = !this->leftChild->isReversed;
        }
        if (this->rightChild != nullptr) {
            this->rightChild->isReversed = !this->rightChild->isReversed;
        }
    }


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


    void reverse(size_t leftBorder, size_t rightBorder) {
        pair<Node*, Node*> firstPairOfTree = split(root, rightBorder);
        pair<Node*, Node*> secondPairOfTree = split(firstPairOfTree.first, leftBorder - 1);

        Node* partToReverse = secondPairOfTree.second;

        if (partToReverse != nullptr) {
            partToReverse->reverse();
        }

        root = merge(secondPairOfTree.first, partToReverse);
        root = merge(root, firstPairOfTree.second);
    }


    void printTree() {
        if (root != nullptr) {
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
            currentRoot->updateReverse();
            recursPrintTree(currentRoot->leftChild);
            cout << currentRoot->value << " ";
            recursPrintTree(currentRoot->rightChild);
        }
    }


    pair<Node*, Node*> split(Node* currentRoot, int index) {
        if (currentRoot == nullptr) {
            return { nullptr, nullptr };
        }

        currentRoot->updateReverse();

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
            firstTree->updateReverse();
            firstTree->rightChild = merge(firstTree->rightChild, secondTree);
            firstTree->fixTreeSize();
            return firstTree;
        }
        else {
            secondTree->updateReverse();
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
        tree.insert(i, i + 1);
    }

    for (size_t i = 0; i < counter; i++) {
        cin >> firstValue >> secondValue;
        tree.reverse(firstValue, secondValue);
    }
    tree.printTree();

    return 0;
}