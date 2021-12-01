#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip> 

using namespace std;

const int MIN_ROPE_SIZE = 1;
const int MAX_ROPE_SIZE = 100 * 1000 * 100;

int ropeCount(const vector<int>& ropes, const int& ropeSize) {
    int count = 0;
    for (auto rope : ropes) {
        count += rope / ropeSize;
    }
    return count;
}

int maxLenCalc(const vector<int>& vec, const int& houses) {
    int left = MIN_ROPE_SIZE - 1;
    int right = MAX_ROPE_SIZE + 1;

    while (left < right - 1) {
        int middle = (right + left) / 2;
        if (ropeCount(vec, middle) >= houses) {
            left = middle;
        }
        else {
            right = middle;
        }
    }
    return left;
}

int main() {
    int N;
    int K;
    cin >> N >> K;

    vector<int> ropes(N);
    for (auto i = 0; i < N; i++) {
        cin >> ropes[i];
    }

    cout << maxLenCalc(ropes, K) << endl;

    return 0;
}