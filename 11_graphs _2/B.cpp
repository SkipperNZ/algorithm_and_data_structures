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
    Edge(size_t from, size_t to, int weight) :
        from(from), to(to), weight(weight) {};

    size_t from;
    size_t to;
    int weight;
};

const pair<int, int> FIRST_VERTEX = { 0, 0 };


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n;
    size_t m;

    size_t firstVertex;
    size_t secondVertex;
    int weightEdge;

    cin >> n >> m;

    vector<vector<Edge>> graph(n);

    for (int i = 0; i < m; i++) {
        cin >> firstVertex >> secondVertex >> weightEdge;
        firstVertex--;
        secondVertex--;

        graph[firstVertex].push_back({ firstVertex, secondVertex, weightEdge });
        graph[secondVertex].push_back({ secondVertex, firstVertex, weightEdge });
    }

    set<pair<int, int>> order;
    vector<int> path(n, INT32_MAX);
    vector <bool> used(n, false);
    path[0] = 0;

    order.insert(FIRST_VERTEX);

    while (!order.empty()) {
        auto iteration = order.begin();
        auto currentVertex = (*iteration).second;
        order.erase(iteration);
        used[currentVertex] = true;

        for (auto& edge : graph[currentVertex]) {

            if (!used[edge.to]) {
                order.erase({ path[edge.to], edge.to });
                path[edge.to] = min(path[edge.to], path[currentVertex] + edge.weight);
                order.insert({ path[edge.to], edge.to });
            }
        }
    }

    for (auto& weight : path) {
        cout << weight << " ";
    }

    return 0;
}