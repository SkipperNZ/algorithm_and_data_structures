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

    string firstStr;
    string secondStr;

    cin >> firstStr >> secondStr;

    vector<vector<int>> dp_matrix;

    for (size_t i = 0; i <= firstStr.size(); i++) {
        vector<int> row((secondStr.size() + 1), 0);
        dp_matrix.push_back(row);
    }

    for (size_t j = 1; j <= secondStr.size(); ++j) {
        dp_matrix[0][j] = dp_matrix[0][j - 1] + 1;
    }

    for (size_t i = 1; i <= firstStr.size(); ++i) {
        dp_matrix[i][0] = dp_matrix[i - 1][0] + 1;

        for (size_t j = 1; j <= secondStr.size(); ++j) {
            if (firstStr[i - 1] == secondStr[j - 1]) {
                dp_matrix[i][j] = dp_matrix[i - 1][j - 1];
            }
            else {
                int minOnAxis = min(dp_matrix[i][j - 1], dp_matrix[i - 1][j]);
                int fullMin = min(minOnAxis, dp_matrix[i - 1][j - 1]);

                dp_matrix[i][j] = fullMin + 1;
            }
        }
    }

    cout << dp_matrix[firstStr.size()][secondStr.size()] << endl;

    return 0;
}