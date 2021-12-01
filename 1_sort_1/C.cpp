#include <iostream>
#include <vector>
#include <cstdint>

using namespace std;

vector<int> merge(vector<int>& leftVec, vector<int>& rightVec, int64_t& invCounter) {
    vector<int> result(leftVec.size() + rightVec.size());
    size_t i = 0;
    size_t j = 0;
    size_t n = leftVec.size();
    size_t m = rightVec.size();
    while (i + j < n + m) {
        if ((j == m) || ((i < n) && (leftVec[i] <= rightVec[j]))) {
            result[i + j] = leftVec[i];
            i++;
        }
        else {
            result[i + j] = rightVec[j];
            j++;
            invCounter += n - i;
        }
    }
    return result;
}

vector<int> mergeSort(vector<int>& vec, int64_t& invCounter) {
    if (vec.size() == 1) {
        return vec;
    }

    auto middle = begin(vec) + vec.size() / 2;
    vector<int> left(begin(vec), middle);
    vector<int> right(middle, end(vec));

    left = mergeSort(left, invCounter);
    right = mergeSort(right, invCounter);

    return merge(left, right, invCounter);
}

int main() {
    int n;
    cin >> n;

    vector<int> target(n);
    for (auto i = 0; i < n; i++) {
        cin >> target[i];
    }

    int64_t invCounter = 0;

    mergeSort(target, invCounter);
    cout << invCounter;

    return 0;
}