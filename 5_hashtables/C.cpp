#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <list>


using namespace std;

const size_t MAX_SIZE = 2'001'337;
const size_t INITIAL_SIZE = 1024;

struct Node {
    Node(string& key, string& value, Node* prevNode) :
        key(key), value(value), prevNode(prevNode), nextNode(nullptr) {};

    string key;
    string value;
    Node* prevNode;
    Node* nextNode;
};

class Map {
public:
    Map() : lastNode(nullptr), sizeMap(0) {
        vec = vector<list<Node*>>(INITIAL_SIZE);
    };

    void put(string& key, string& value) {
        Node* newElement = new Node(key, value, lastNode);
        put(newElement);
    }

    void put(Node* node) {
        if (sizeMap == vec.size() / 2 && vec.size() < MAX_SIZE) {
            size_t newSize = min(vec.size() * 2, MAX_SIZE);
            rehash(newSize);
        }

        size_t index = hash(node->key);
        list<Node*>& listOfElement = vec[index];

        for (auto& element : listOfElement) {
            if (element->key == node->key) {
                element->value = node->value;
                return;
            }
        }

        listOfElement.push_back(node);

        if (lastNode != nullptr) {
            lastNode->nextNode = node;
        }

        lastNode = node;
    }

    string get(const string& key) {
        size_t index = hash(key);
        auto& listOfElement = vec[index];

        for (auto& element : listOfElement) {
            if (element->key == key) {
                return element->value;
            }
        }
        return "none";
    }

    void del(string& key) {
        size_t index = hash(key);
        auto& listOfElement = vec[index];
        auto it = listOfElement.begin();
        size_t counter = 0;

        for (auto* element : listOfElement) {
            if (element->key == key) {
                Node* targetNode = element;

                if (targetNode->nextNode != nullptr) {
                    targetNode->nextNode->prevNode = targetNode->prevNode;
                }

                if (targetNode->prevNode != nullptr) {
                    targetNode->prevNode->nextNode = targetNode->nextNode;
                }

                if (targetNode == lastNode) {
                    lastNode = targetNode->prevNode;
                }

                advance(it, counter);
                listOfElement.erase(it);
                sizeMap--;

                if (sizeMap == vec.size() / 8 && vec.size() > INITIAL_SIZE) {
                    size_t newSize = max(vec.size() / 2, INITIAL_SIZE);
                    rehash(newSize);
                }

                delete targetNode;
                break;
            }
            counter++;
        }
    }

    string next(const string& key) {
        size_t index = hash(key);
        list<Node*>& listOfElement = vec[index];

        for (auto& element : listOfElement) {
            if (element->key == key && element->nextNode != nullptr) {
                return element->nextNode->value;
            }
        }
        return "none";
    }

    string prev(const string& key) {
        size_t index = hash(key);
        list<Node*>& listOfElement = vec[index];

        for (auto& element : listOfElement) {
            if (element->key == key && element->prevNode != nullptr) {
                return element->prevNode->value;
            }
        }
        return "none";
    }

private:
    const int P = 2'013'377;
    const int A = 7;

    size_t sizeMap;
    vector<list<Node*>> vec;
    Node* lastNode;

    size_t hash(const string& value) const {
        size_t  hashString = 0;

        for (char c : value) {
            hashString = (hashString * A + c) % P;
        }

        hashString = hashString % vec.size();
        return hashString;
    }

    void rehash(size_t newSize) {
        vector<list<Node*>> oldVec = vec;
        vec = vector<list<Node*>>(newSize);
        sizeMap = 0;

        for (auto& listOfElement : oldVec) {
            for (auto& element : listOfElement) {
                put(element);
            }
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string command;
    string key;
    string value;

    Map m;

    while (cin >> command >> key) {
        if (command == "put") {
            cin >> value;
            m.put(key, value);
        }
        else if (command == "delete") {
            m.del(key);
        }
        else if (command == "get") {
            cout << m.get(key) << endl;
        }
        else if (command == "next") {
            cout << m.next(key) << endl;
        }
        else if (command == "prev") {
            cout << m.prev(key) << endl;
        }
    }

    return 0;
}