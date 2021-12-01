#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <list>


using namespace std;
using storage = vector<list<pair<string, string>>>;

const size_t MAX_SIZE = 2'001'337;
const size_t INITIAL_SIZE = 1024;

class Map {
public:
    Map() : sizeMap(0) {
        vec = storage(INITIAL_SIZE);
    };

    void put(string& key, string& value) {
        if (sizeMap == vec.size() / 2 && vec.size() < MAX_SIZE) {
            size_t newSize = min(vec.size() * 2, MAX_SIZE);
            rehash(newSize);
        }

        bool flag = false;
        size_t index = hash(key);
        list<pair<string, string>>& listOfElement = vec[index];

        for (auto& element : listOfElement) {
            if (element.first == key) {
                flag = true;
                element.second = value;
                break;
            }
        }

        if (!flag) {
            listOfElement.push_back(make_pair(key, value));
            sizeMap++;
        }
    }

    string get(const string& key) {
        size_t index = hash(key);
        const list<pair<string, string>>& listOfElement = vec[index];

        for (const auto& element : listOfElement) {
            if (element.first == key) {
                return element.second;
            }
        }
        return "none";
    }

    void del(string& key) {
        size_t index = hash(key);
        list<pair<string, string>>& listOfElement = vec[index];
        auto it = listOfElement.begin();
        size_t counter = 0;

        for (auto& element : listOfElement) {
            if (element.first == key) {
                advance(it, counter);
                listOfElement.erase(it);
                sizeMap--;

                if (sizeMap == vec.size() / 8 && vec.size() > INITIAL_SIZE) {
                    size_t newSize = max(vec.size() / 2, INITIAL_SIZE);
                    rehash(newSize);
                }
                break;
            }
            counter++;
        }
    }

private:
    const int P = 2'013'377;
    const int A = 7;

    size_t sizeMap;
    storage vec;

    size_t hash(const string& value) const {
        size_t  hashString = 0;

        for (char c : value) {
            hashString = (hashString * A + c) % P;
        }

        hashString = hashString % vec.size();
        return hashString;
    }

    void rehash(size_t newSize) {
        storage oldVec = vec;
        vec = storage(newSize);
        sizeMap = 0;

        for (auto& listOfElement : oldVec) {
            for (auto& element : listOfElement) {
                put(element.first, element.second);
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
    }

    return 0;
}