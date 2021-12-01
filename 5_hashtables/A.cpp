#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <sstream>

using namespace std;

const size_t MAX_SIZE = 2'001'337;
const size_t INITIAL_SIZE = 1024;

class Set {
public:
    Set() : sizeSet(0) {
        vec = vector<int>(INITIAL_SIZE, INT32_MAX);
    };

    void insert(int value) {
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

    void del(int value) {
        size_t index = findIndex(value);

        if (vec[index] == value) {
            vec[index] = EMPTY_VALUE;
            shiftHash(index);
            sizeSet--;
        }

        if (sizeSet == vec.size() / 8 && vec.size() > INITIAL_SIZE) {
            size_t newSize = max(vec.size() / 2, INITIAL_SIZE);
            rehash(newSize);
        }
    }

    bool contains(int value) {
        size_t index = findIndex(value);
        return vec[index] == value;
    }

private:

    vector<int> vec;
    size_t sizeSet;
    const int P = 2'013'377;
    const int A = 7;
    const int EMPTY_VALUE = INT32_MAX;

    size_t hash(int value) {
        return ((value * A) % P) % vec.size();
    }

    size_t findIndex(int value) {
        size_t index = hash(value);
        while (vec[index] != EMPTY_VALUE && vec[index] != value) {
            index = (index + 1) % vec.size();
        }
        return index;
    }

    void rehash(size_t newSize) {
        vector<int> oldVec = vec;

        vec = vector<int>(newSize, INT32_MAX);
        for (auto i : oldVec) {
            if (i != EMPTY_VALUE) {
                size_t index = findIndex(i);
                vec[index] = i;
            }
        }
    }

    void shiftHash(size_t swapIndex) {
        size_t nextIndex = (swapIndex + 1) % vec.size();
        while (vec[nextIndex] != EMPTY_VALUE) {
            size_t nextHash = hash(vec[nextIndex]);

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
    int value;

    Set s;

    while (cin >> command >> value) {
        if (command == "insert") {
            s.insert(value);
        }
        else if (command == "delete") {
            s.del(value);
        }
        else if (command == "exists") {
            if (s.contains(value)) {
                cout << "true" << "\n";
            }
            else {
                cout << "false" << "\n";
            }
        }
    }

    return 0;
}