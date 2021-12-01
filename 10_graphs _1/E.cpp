#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <list>
#include <sstream>
#include <map>
#include <set>

using namespace std;


void dfs(const vector<vector<size_t>>& graph, size_t vertex,
    vector<size_t>& tin, vector<size_t>& up, set<size_t>& articulationPoints,
    size_t& step, bool isRoot) {

    step++;
    tin[vertex] = step;
    up[vertex] = step;
    size_t count = 0;

    for (size_t neighborVertex : graph[vertex]) {
        if (up[neighborVertex] > 0) {
            up[vertex] = min(up[vertex], tin[neighborVertex]);
        }
        else {
            dfs(graph, neighborVertex, tin, up, articulationPoints, step, false);
            count++;
            up[vertex] = min(up[vertex], up[neighborVertex]);

            if (up[neighborVertex] >= tin[vertex] && !isRoot) {
                articulationPoints.insert(vertex);
            }
        }
    }

    if (isRoot && count > 1) {
        articulationPoints.insert(vertex);
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n;
    size_t m;
    cin >> n >> m;

    vector<vector<size_t>> undirectedGraph(n);
    set<size_t> articulationPoints;
    vector<size_t> tin(n, 0);
    vector<size_t> up(n, 0);
    size_t step = 0;


    size_t firstVertex, secondVertex;

    for (size_t i = 0; i < m; i++) {
        cin >> firstVertex >> secondVertex;
        firstVertex--;
        secondVertex--;

        undirectedGraph[firstVertex].push_back(secondVertex);
        undirectedGraph[secondVertex].push_back(firstVertex);
    }


    for (size_t i = 0; i < n; i++) {
        if (up[i] == 0) {
            dfs(undirectedGraph, i, tin, up, articulationPoints, step, true);
        }
    }

    cout << articulationPoints.size() << endl;

    for (auto point : articulationPoints) {
        cout << point + 1 << " ";
    }

    return 0;
}