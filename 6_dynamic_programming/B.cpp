#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <list>
#include <sstream>

using namespace std;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n;
    size_t m;
    cin >> n >> m;

    vector<vector<int>> moneyMatrix;
    vector<vector<int>> maxMoneyInCell;
    vector<vector<char>> trackMatrix;

    for (size_t i = 0; i < n; i++) {
        vector<int> rowMoney(m);
        vector<int> rowMaxMoney(m);
        vector<char> rowVoidTrack(m);

        for (size_t j = 0; j < m; j++) {
            cin >> rowMoney[j];
            rowMaxMoney[j] = INT32_MIN;
        }

        moneyMatrix.push_back(rowMoney);
        maxMoneyInCell.push_back(rowMaxMoney);
        trackMatrix.push_back(rowVoidTrack);
    }

    maxMoneyInCell[0][0] = moneyMatrix[0][0];

    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < m; j++) {
            if (i == 0 && j > 0) {
                maxMoneyInCell[0][j] = maxMoneyInCell[0][j - 1] + moneyMatrix[0][j];
                trackMatrix[0][j] = 'R';
            }
            else if (i > 0 && j == 0) {
                maxMoneyInCell[i][0] = maxMoneyInCell[i - 1][0] + moneyMatrix[i][0];
                trackMatrix[i][0] = 'D';
            }
            else if (i > 0 && j > 0) {

                if (maxMoneyInCell[i - 1][j] >= maxMoneyInCell[i][j - 1]) {
                    maxMoneyInCell[i][j] = maxMoneyInCell[i - 1][j] + moneyMatrix[i][j];
                    trackMatrix[i][j] = 'D';
                }
                else {
                    maxMoneyInCell[i][j] = maxMoneyInCell[i][j - 1] + moneyMatrix[i][j];
                    trackMatrix[i][j] = 'R';
                }
            }
        }
    }

    cout << maxMoneyInCell[n - 1][m - 1] << "\n";

    size_t i = n - 1;
    size_t j = m - 1;
    vector<char> track(i + j);

    while (i > 0 || j > 0) {
        track[(i + j) - 1] = trackMatrix[i][j];
        if (trackMatrix[i][j] == 'D') {
            i -= 1;
        }
        else {
            j -= 1;
        }
    }

    for (auto& c : track) {
        cout << c;
    }
    return 0;
}