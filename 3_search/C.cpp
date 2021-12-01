#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <iomanip> 

using namespace std;

const double EPS = 1e-6;

double mathFunc(double x) {
    return x * x + sqrt(x);
}

double findLeftBoarder(const double& C) {
    double x = -1;
    while (mathFunc(x) > C) {
        x = x * 2;
    }
    return x;
}

double findRightBoarder(const double& C) {
    double x = 1;
    while (mathFunc(x) < C) {
        x = x * 2;
    }
    return x;
}

float binSearch(const float& C) {
    double leftBorder = findLeftBoarder(C);
    double rightBorder = findRightBoarder(C);
    const int iterations = static_cast<int>(log2((rightBorder - leftBorder) / EPS));

    for (auto i = 0; i < iterations; i++) {
        double middle = (rightBorder + leftBorder) / 2;
        if (mathFunc(middle) < C) {
            leftBorder = middle;
        }
        else {
            rightBorder = middle;
        }
    }

    return rightBorder;
}

int main() {
    float C;
    cin >> C;

    cout << setprecision(10) << binSearch(C) << endl;

    return 0;
}