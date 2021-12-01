#include <iostream>
#include <vector>

using namespace std;

void printVector(const vector<int>& vec) {
    for (auto iter = vec.begin(); iter != vec.end(); iter++) {
        if (iter != vec.begin()) {
            cout << ' ';
        }
        cout << *iter;
    }
}

void countingSort(vector<int>& vec) {
    int M = 'z';  // different value of vector element
    vector<int> cnt(M);

    for (int elem : vec) {
        cnt[elem]++;
    }

    int i = 0;
    for (int j = 0; j <= M - 1; j++) {
        while (cnt[j] > 0) {
            vec[i++] = j;
            cnt[j]--;
        }
    }
}

int main() {
    vector<int> target;

    int element;
    while (cin >> element) {
        target.push_back(element);
    }

    countingSort(target);
    printVector(target);

    return 0;
}