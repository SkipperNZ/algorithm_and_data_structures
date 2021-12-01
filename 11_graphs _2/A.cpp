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

const pair<int, int> DEFAULT_VALUE = { 0, 0 };
const pair<int, int> START_VALUE = { -1, -1 };
const vector<pair<int, int>> KNIGHT_MOVES = {
    {-2, 1},
    {-2, -1},
    {2, 1},
    {2, -1},
    {1, 2},
    {1, -2},
    {-1, 2},
    {-1, -2}
};


bool checkPosition(pair<int, int> position, pair<int, int> moveTo, size_t bordSize) {
    pair<int, int> newPosition = { position.first + moveTo.first, position.second + moveTo.second };

    return newPosition.first >= 1 && newPosition.first <= bordSize &&
        newPosition.second >= 1 && newPosition.second <= bordSize;
}


vector<pair<int, int>> getNeighborPosition(pair<int, int> currentPosition, size_t bordSize) {
    vector<pair<int, int>> res;

    for (const pair<int, int>& move : KNIGHT_MOVES) {

        if (checkPosition(currentPosition, move, bordSize)) {
            res.push_back({ currentPosition.first + move.first,
                currentPosition.second + move.second });
        }

    }
    return res;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t N;
    int xOne;
    int yOne;
    int xTwo;
    int yTwo;
    cin >> N >> xOne >> yOne >> xTwo >> yTwo;

    vector<vector<pair<int, int>>> bord(N);
    queue<pair<int, int>> coordQueue;

    coordQueue.push({ xOne, yOne });

    for (auto& row : bord) {
        row.resize(N, DEFAULT_VALUE);
    }

    bord[xOne - 1][yOne - 1] = START_VALUE;

    pair<int, int> currentPosition = { xOne, yOne };
    pair<int, int> finishPosition = { xTwo, yTwo };

    while (!coordQueue.empty() && currentPosition != finishPosition) {
        currentPosition = coordQueue.front();
        coordQueue.pop();

        for (auto& neighbor : getNeighborPosition(currentPosition, N)) {
            if (bord[neighbor.first - 1][neighbor.second - 1] == DEFAULT_VALUE) {

                coordQueue.push(neighbor);

                bord[neighbor.first - 1][neighbor.second - 1] =
                { currentPosition.first, currentPosition.second };
            }
        }
    }

    list<pair<int, int>> path;
    pair<int, int> currentPathPosition = { xTwo, yTwo };

    while (currentPathPosition != START_VALUE) {
        path.push_front(currentPathPosition);
        currentPathPosition = bord[currentPathPosition.first - 1][currentPathPosition.second - 1];
    }

    cout << path.size() << endl;

    for (pair<int, int> step : path) {
        cout << step.first << " " << step.second << "\n";
    }

    return 0;
}