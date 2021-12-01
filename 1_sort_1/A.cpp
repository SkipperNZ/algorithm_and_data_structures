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

void bubbleSort(vector<int>& vec) {
    for (auto i = 0; i < vec.size(); i++) {
        for (auto j = 0; j < vec.size() - 1; j++) {
            if (vec[j] > vec[j + 1]) {
                auto tempVar = vec[j];
                vec[j] = vec[j + 1];
                vec[j + 1] = tempVar;
            }
        }
    }
}

int main() {
    int N;
    cin >> N;

    vector<int> target(N);
    for (auto i = 0; i < N; i++) {
        cin >> target[i];
    }

    bubbleSort(target);
    printVector(target);

    return 0;
}