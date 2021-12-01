#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <list>

using namespace std;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t N;
    size_t K;
    cin >> N >> K;

    vector<size_t> jumpedPillars;
    vector<int> pillarCost(N);
    vector<size_t> path;

    vector<int> mapOfcost(N, INT32_MIN);
    mapOfcost[0] = 0;
    jumpedPillars.push_back(0);

    for (size_t i = 1; i < N - 1; ++i) {
        cin >> pillarCost[i];
    }

    for (size_t i = 1; i < N; i++) {
        size_t maxJumpsToPillar = min(K, i);
        size_t trackPrevStep = i;

        for (size_t j = 1; j <= maxJumpsToPillar; ++j) {
            if (mapOfcost[i] < mapOfcost[i - j]) {
                mapOfcost[i] = mapOfcost[i - j];
                trackPrevStep = i - j;
            }
        }
        mapOfcost[i] += pillarCost[i];
        jumpedPillars.push_back(trackPrevStep + 1);
    }

    jumpedPillars.push_back(N);

    cout << mapOfcost.back() << "\n";

    size_t columnId = jumpedPillars.size() - 1;

    while (columnId > 0) {
        path.push_back(jumpedPillars[columnId]);
        columnId = jumpedPillars[columnId] - 1;
    }

    reverse(path.begin(), path.end());

    cout << path.size() - 1 << "\n";

    for (auto i : path) {
        cout << i << ' ';
    }

    return 0;
}