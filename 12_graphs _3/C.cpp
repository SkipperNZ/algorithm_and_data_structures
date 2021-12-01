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


struct Edge {
    int x;
    int y;
    int number;

    Edge() : x(0), y(0), number(0) {}
    Edge(int x, int y, int number) : x(x), y(y), number(number) {};

    double distance(Edge& lhs) const {
        return sqrt(pow((this->x - lhs.x), 2) + pow((this->y - lhs.y), 2));
    }

    bool operator<(const Edge& lhs) const {
        return this->x < lhs.x;
    }

    bool operator==(const Edge& lhs) const {
        return this->x == lhs.x && this->y == lhs.y;
    }
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t N;
    cin >> N;

    int x;
    int y;
    vector<Edge> graph(N);

    for (int i = 0; i < N; i++) {
        cin >> x >> y;
        graph[i] = { x, y, i };
    }

    vector<bool> used(N, false);
    vector<double> weights(N, INT32_MAX);
    weights[0] = 0;
    Edge currentVertex = graph[0];
    double sumWeight = 0;

    for (int i = 0; i < N; i++) {
        used[currentVertex.number] = true;
        Edge newVertex = currentVertex;
        double minDistance = INT32_MAX;

        for (auto& vertex : graph) {
            if (used[vertex.number] == false) {
                weights[vertex.number] = min(weights[vertex.number], currentVertex.distance(vertex));

                if (weights[vertex.number] < minDistance) {
                    minDistance = weights[vertex.number];
                    newVertex = vertex;
                }
            }
        }
        if (minDistance == INT32_MAX) {
            break;
        }

        currentVertex = newVertex;
        sumWeight += minDistance;
    }

    cout << sumWeight << endl;
    return 0;
}