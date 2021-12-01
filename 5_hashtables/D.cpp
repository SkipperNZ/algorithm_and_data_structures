#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <list>
#include <sstream>


using namespace std;

const size_t MAX_SIZE = 200'000;
const size_t SET_INIT_SIZE = 128;

//set from A deep modification for string
class Set {
public:
    Set() : sizeSet(0) {
        vec = vector<string>(SET_INIT_SIZE);
    };

    void put(string& value) {
        if (sizeSet == vec.size() / 2 && vec.size() < MAX_SIZE) {
            size_t newSize = min(vec.size() * 2, MAX_SIZE);
            rehash(newSize);
        }

        size_t index = findIndex(value);

        if (vec[index] != value) {
            vec[index] = value;
            sizeSet++;
        }
    }

    void del(string& value) {
        size_t index = findIndex(value);
        if (vec[index] == value) {
            vec[index] = "";
            shiftHash(index);
            sizeSet--;
        }

        if (sizeSet == vec.size() / 8 && vec.size() > SET_INIT_SIZE) {
            size_t newSize = max(vec.size() / 2, SET_INIT_SIZE);
            rehash(newSize);
        }
    }

    string get() {
        stringstream ss;

        ss << sizeSet;
        for (string& s : vec) {
            if (!s.empty()) {
                ss << " " << s;
            }
        }
        ss << "\n";
        return ss.str();
    }

    bool isEmpty() {
        return sizeSet == 0;
    }

private:
    vector<string> vec;
    size_t sizeSet;
    const int P = 2'013'377;
    const int A = 7;

    size_t hash(const string& value) const {
        size_t  hashString = 0;

        for (char c : value) {
            hashString = (hashString * A + c) % P;
        }

        hashString = hashString % vec.size();
        return hashString;
    }

    size_t findIndex(string& key) {
        size_t index = hash(key);
        while (!(vec[index].empty()) && (vec[index] != key)) {
            index = (index + 1) % vec.size();
        }
        return index;
    }

    void rehash(size_t newSize) {
        vector<string> oldVec = vec;
        vec = vector<string>(newSize);

        for (auto& element : oldVec) {
            size_t index = findIndex(element);
            if (!element.empty()) {
                vec[index] = element;
            }
        }
    }

    void shiftHash(size_t swapIndex) {
        size_t nextIndex = (swapIndex + 1) % vec.size();
        while (!vec[nextIndex].empty()) {

            auto& key = vec[nextIndex];
            size_t nextHash = hash(key);

            if ((swapIndex <= nextIndex && nextHash <= swapIndex) &&
                (nextHash > nextIndex || (swapIndex >= nextHash && swapIndex <= nextIndex))) {

                swap(vec[swapIndex], vec[nextIndex]);
                swapIndex = nextIndex;
            }
            nextIndex = (nextIndex + 1) % vec.size();
        }
    }
};

class Map {
public:
    Map() {
        vec = vector<pair<string, Set>*>(MAX_SIZE);
    };

    void put(string& key, string& value) {
        size_t index = findIndex(key);

        if (vec[index] == nullptr) {
            vec[index] = new pair<string, Set>;
            vec[index]->first = key;
            vec[index]->second.put(value);
        }
        else {
            vec[index]->second.put(value);
        }
    }

    string get(const string& key) {
        size_t index = findIndex(key);
        if (vec[index] != nullptr) {
            return vec[index]->second.get();
        }
        else {
            return "0";
        }

    }

    void del(string& key, string& value) {
        size_t index = findIndex(key);
        if (vec[index] != nullptr) {
            vec[index]->second.del(value);
            if (vec[index]->second.isEmpty()) {
                delete vec[index];
                vec[index] = nullptr;
                shiftHash(index);
            }
        }
    }

    void delAll(string& key) {
        size_t index = findIndex(key);
        if (vec[index] != nullptr) {
            delete vec[index];
            vec[index] = nullptr;
            shiftHash(index);
        }
    }

private:
    const int P = 2'013'377;
    const int A = 7;

    vector<pair<string, Set>*> vec;

    size_t hash(const string& value) const {
        size_t  hashString = 0;

        for (char c : value) {
            hashString = (hashString * A + c) % P;
        }

        hashString = hashString % vec.size();
        return hashString;
    }

    size_t findIndex(const string& key) {
        size_t index = hash(key);
        while (vec[index] != nullptr && vec[index]->first != key) {
            index = (index + 1) % vec.size();
        }
        return index;
    }

    void shiftHash(size_t swapIndex) {
        size_t nextIndex = (swapIndex + 1) % vec.size();
        while (vec[nextIndex] != nullptr) {

            auto& key = vec[nextIndex]->first;
            size_t nextHash = hash(key);

            if ((swapIndex <= nextIndex && nextHash <= swapIndex) &&
                (nextHash > nextIndex || (swapIndex >= nextHash && swapIndex <= nextIndex))) {

                swap(vec[swapIndex], vec[nextIndex]);
                swapIndex = nextIndex;
            }
            nextIndex = (nextIndex + 1) % vec.size();
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
            cin >> value;
            m.del(key, value);
        }
        else if (command == "get") {
            cout << m.get(key) << endl;
        }
        else if (command == "deleteall") {
            m.delAll(key);
        }
    }

    return 0;
}