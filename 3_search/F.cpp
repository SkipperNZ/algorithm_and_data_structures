#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <iomanip> 

using namespace std;

const double EPS = 1e-5;
const double LEFT_SIDE = -0.01;
const double RIGHT_SIDE = 1.01;
const int ITN = static_cast<int>(log((RIGHT_SIDE - LEFT_SIDE) / EPS) / log(3.0 / 2));

double trevelTime(const double& xСoord, const double& yBorder,
    const int& poleSpeed, const int& forestSpeed) {

    double polePath = sqrt(pow(xСoord, 2) + pow((1 - yBorder), 2));
    double forestPath = sqrt(pow(yBorder, 2) + pow((1 - xСoord), 2));

    return (polePath / poleSpeed) + (forestPath / forestSpeed);
}

double coordCalc(const int& poleSpeed, const int& forestSpeed, const double& yBorder) {
    double leftBorder = LEFT_SIDE;
    double rightBorder = RIGHT_SIDE;

    for (auto i = 0; i < ITN; i++) {
        double leftSlice = (2 * leftBorder + rightBorder) / 3;
        double rightSlice = (leftBorder + 2 * rightBorder) / 3;

        if (trevelTime(leftSlice, yBorder, poleSpeed, forestSpeed) <
            trevelTime(rightSlice, yBorder, poleSpeed, forestSpeed)) {
            rightBorder = rightSlice;
        }
        else {
            leftBorder = leftSlice;
        }
    }

    return rightBorder;
}

int main() {
    int poleSpeed;
    int forestSpeed;
    cin >> poleSpeed >> forestSpeed;

    double yBorder;
    cin >> yBorder;

    cout << setprecision(10) <<
        coordCalc(poleSpeed, forestSpeed, yBorder) << endl;

    return 0;
}