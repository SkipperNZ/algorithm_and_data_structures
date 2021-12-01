#include <iostream>
#include <vector>
#include <cstdint>

using namespace std;

void printVector(const vector<int>& vec) {
    for (auto iter = vec.begin(); iter != vec.end(); iter++) {
        if (iter != vec.begin()) {
            cout << ' ';
        }
        cout << *iter;
    }
}

void quickSort(vector<int>& vec, const int& left, const int& right) {
    int leftBorder = left;
    int rightBorder = right;

    int midIndex = (right + left) / 2;
    int middle = vec[midIndex];

    while (leftBorder <= rightBorder) {
        while (vec[leftBorder] < middle) {
            leftBorder++;
        }
        while (vec[rightBorder] > middle) {
            rightBorder--;
        }
        if (leftBorder <= rightBorder) {
            swap(vec[leftBorder++], vec[rightBorder--]);
        }
    }

    if (left < rightBorder) {
        quickSort(vec, left, rightBorder);
    }
    if (right > leftBorder) {
        quickSort(vec, leftBorder, right);
    }
}

int main() {
    int n;
    cin >> n;

    vector<int> target(n);
    for (auto i = 0; i < n; i++) {
        cin >> target[i];
    }

    int left = 0;
    int right = target.size() - 1;

    quickSort(target, left, right);
    printVector(target);

    return 0;
}