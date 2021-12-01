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

vector<int> merge(vector<int>& leftVec, vector<int>& rightVec) {
    vector<int> result(leftVec.size() + rightVec.size());
    size_t i = 0;
    size_t j = 0;
    size_t n = leftVec.size();
    size_t m = rightVec.size();
    while (i + j < n + m) {
        if ((j == m) || ((i < n) && (leftVec[i] < rightVec[j]))) {
            result[i + j] = leftVec[i];
            i++;
        }
        else {
            result[i + j] = rightVec[j];
            j++;
        }
    }
    return result;
}

vector<int> mergeSort(vector<int>& vec) {
    if (vec.size() == 1) {
        return vec;
    }

    auto middle = begin(vec) + vec.size() / 2;
    vector<int> left(begin(vec), middle);
    vector<int> right(middle, end(vec));

    left = mergeSort(left);
    right = mergeSort(right);

    return merge(left, right);
}

int main() {
    int N;
    cin >> N;

    vector<int> target(N);
    for (auto i = 0; i < N; i++) {
        cin >> target[i];
    }

    printVector(mergeSort(target));

    return 0;
}