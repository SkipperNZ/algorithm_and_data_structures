#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAX_TIME_VALUE = 2 * 1e8 * 10;

int copyCount(int time, const int& speedX, const int& speedY) {
    int minSpeed = min(speedX, speedY);

    if (time >= minSpeed) {
        time -= minSpeed;
        return (time / speedX) + (time / speedY) + 1;
    }
    else {
        return 0;
    }
}

int printTimeCounter(const int& paperCopy, const int& speedX, const int& speedY) {
    int left = 0;
    int right = MAX_TIME_VALUE;

    while (left < right - 1) {
        int middle = (right + left) / 2;
        if (copyCount(middle, speedX, speedY) >= paperCopy) {
            right = middle;
        }
        else {
            left = middle;
        }
    }
    return right;
}

int main() {
    int n;
    int x;
    int y;
    cin >> n >> x >> y;

    cout << printTimeCounter(n, x, y) << endl;

    return 0;
}