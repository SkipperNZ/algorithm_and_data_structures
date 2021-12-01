#include <iostream>
#include <vector>
#include <string>
#include <cstdint>

using namespace std;

int binSearch(const vector<int>& vec, const int& value) {
    int left = -1;
    int right = vec.size();

    while (left < right - 1) {
        int middle = (left + right) / 2;

        if (vec[middle] == value) {
            left = middle;
            break;
        }
        else if (vec[middle] < value) {
            left = middle;
        }
        else {
            right = middle;
        }
    }

    if (right == vec.size()) {
        return vec[left];
    }
    else if ((value - vec[left] <= vec[right] - value) && left > -1) {
        return vec[left];
    }
    else {
        return vec[right];
    }
}

int main() {
    int n;
    int k;
    cin >> n >> k;

    vector<int> target(n);
    vector<int> values(k);

    for (int i = 0; i < n; i++) {
        cin >> target[i];
    }

    for (int i = 0; i < k; i++) {
        cin >> values[i];
    }

    for (int& i : values) {
        cout << binSearch(target, i) << endl;
    }

    return 0;
}
