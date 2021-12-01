#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <list>
#include <sstream>
#include <map>
#include <set>
#include <queue>

using namespace std;


const int MAX_VALUE = 100'000;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t N;

    cin >> N;

    vector<vector<int>> weights(N);
    vector<vector<size_t>> path(N);


    for (int i = 0; i < N; i++) {
        weights[i].resize(N);
        path[i].resize(N);

        for (int j = 0; j < N; j++) {
            cin >> weights[i][j];
            if (weights[i][j] == MAX_VALUE) {
                weights[i][j] = INT32_MAX;
            }
            path[i][j] = j;
        }
    }

    int cycleStart = -1;

    for (int k = 0; k < N; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (weights[i][k] + weights[k][j] < weights[i][j] &&
                    weights[i][k] < INT32_MAX &&
                    weights[k][j] < INT32_MAX) {

                    weights[i][j] = weights[i][k] + weights[k][j];
                    path[i][j] = path[i][k];

                    if (i == j && weights[i][j] < 0) {
                        cycleStart = i;
                        break;
                    }
                }
            }
            if (cycleStart > -1) {
                break;
            }
        }
        if (cycleStart > -1) {
            break;
        }
    }

    if (cycleStart > -1) {
        vector<size_t> cyclePath;
        size_t currentVertex = path[cycleStart][cycleStart];
        cyclePath.push_back(cycleStart);

        while (currentVertex != cycleStart) {
            cyclePath.push_back(currentVertex);
            currentVertex = path[currentVertex][cycleStart];
        }

        cout << "YES" << endl;
        cout << cyclePath.size() << endl;

        for (auto vertex : cyclePath) {
            cout << vertex + 1 << " ";
        }
    }
    else {
        cout << "NO" << endl;
    }

    return 0;
}