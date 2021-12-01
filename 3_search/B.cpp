#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int lowerBound(const vector<int>& vec, const int& value) {
    int left = -1;
    int right = vec.size();

    while (left < right - 1) {
        int middle = (left + right) / 2;

        if (vec[middle] >= value) {
            right = middle;
        }
        else {
            left = middle;
        }
    }

    return right;
}

int distCounter(const vector<int>& vec, const int& left, const int& right) {
    return lowerBound(vec, right + 1) - lowerBound(vec, left);
}

int main() {
    int n;
    cin >> n;

    vector<int> target(n);
    for (int i = 0; i < n; i++) {
        cin >> target[i];
    }
    sort(target.begin(), target.end());

    int k;
    cin >> k;

    for (auto i = 0; i < k; i++) {
        int left;
        int right;
        cin >> left >> right;

        cout << distCounter(target, left, right) << endl; 
    }

    return 0;
}