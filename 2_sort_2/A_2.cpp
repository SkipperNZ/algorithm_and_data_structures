#include <iostream>
#include <vector>

using namespace std;

int split(vector<int>& vec, const int& left, const int& right) {
    int leftIndex = left + 1;
    int rightIndex = right;
    int pivot = vec[left];

    while (true) {
        while ((leftIndex < right) &&
            (vec[leftIndex] < pivot)) {
            leftIndex++;
        }
        while (vec[rightIndex] > pivot) {
            rightIndex--;
        }
        if (leftIndex >= rightIndex) {
            break;
        }
        swap(vec[leftIndex], vec[rightIndex]);
        leftIndex++;
        rightIndex--;
    }
    swap(vec[left], vec[rightIndex]);

    return rightIndex;
}

int findOrderStatistic(vector<int>& vec, const int& k, const int& left, const int& right) {
    int midIndex = (right + left) / 2;
    swap(vec[left], vec[midIndex]);
    int border = split(vec, left, right);

    if (border == k - 1) {
        return vec[border];
    }
    else if (border < k - 1) {
        return findOrderStatistic(vec, k, border + 1, right);
    }
    else {
        return findOrderStatistic(vec, k, left, border - 1);
    }
}

int main() {
    int n;
    cin >> n;

    vector<int> target(n);

    for (auto i = 0; i < n; i++) {
        cin >> target[i];
    }

    int m;
    cin >> m;

    for (auto i = 0; i < m; i++) {
        int leftBorder;
        int rightBorder;
        int k;
        cin >> leftBorder >> rightBorder >> k;

        // make subvector from i to j 
        auto firtstTrooper = target.begin() + leftBorder - 1;
        auto lastTrooper = target.begin() + rightBorder;
        vector<int> subTarget(firtstTrooper, lastTrooper);

        // find k statistic in this subvector
        int left = 0;
        int right = subTarget.size() - 1;
        cout << findOrderStatistic(subTarget, k, left, right) << endl;
    }

    return 0;
}