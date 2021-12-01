#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>

using namespace std;

class Heap {
public:
    Heap() : counter(0) {}

    void push(int value) {
        counter++;
        heapVec.push_back({ value, counter });
        int index = heapVec.size() - 1;
        indexes.push_back(index);
        siftUp(index);
    }

    string extractMin() {
        counter++;
        indexes.push_back(-1);
        if (heapVec.empty()) {
            return "*";
        }
        else {
            string ansver = to_string(heapVec[0].first) + " " + to_string(heapVec[0].second);

            swap(heapVec[0], heapVec[heapVec.size() - 1]);
            swap(indexes[heapVec[0].second - 1], indexes[heapVec[heapVec.size() - 1].second - 1]);

            heapVec.pop_back();
            siftDown(0);

            return ansver;
        }
    }

    void decreaseKey(int pushOrder, int newValue) {
        counter++;
        indexes.push_back(-1);
        int heapInd = indexes[pushOrder - 1];
        heapVec[heapInd].first = newValue;
        siftUp(heapInd);
    }

private:
    void siftUp(int index) {
        while (index > 0 &&
            heapVec[index].first < heapVec[(index - 1) / 2].first) {

            swap(heapVec[index], heapVec[(index - 1) / 2]);
            swap(indexes[heapVec[index].second - 1], indexes[heapVec[(index - 1) / 2].second - 1]);

            index = (index - 1) / 2;
        }
    }

    void siftDown(int index) {

        int minChildIdx = 2 * index + 1;

        while (minChildIdx < heapVec.size()) {
            if (minChildIdx + 1 < heapVec.size() &&
                heapVec[minChildIdx].first > heapVec[minChildIdx + 1].first) {

                minChildIdx++;
            }

            if (heapVec[minChildIdx].first < heapVec[index].first) {

                swap(heapVec[index], heapVec[minChildIdx]);
                swap(indexes[heapVec[index].second - 1],
                    indexes[heapVec[minChildIdx].second - 1]);

            }
            index = minChildIdx;
            minChildIdx = 2 * index + 1;
        }
    }

    int counter;
    vector<pair<int, int>> heapVec;
    vector<int> indexes;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    Heap h;

    string operation;
    while (cin >> operation) {
        if (operation == "push") {
            int value;
            cin >> value;
            h.push(value);
        }
        else if (operation == "decrease-key") {
            int pushOrder;
            int newValue;
            cin >> pushOrder >> newValue;
            h.decreaseKey(pushOrder, newValue);
        }
        else {
            cout << h.extractMin() << "\n";
        }
    }

    return 0;
}