#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <list>
#include <sstream>
#include <map>

using namespace std;

size_t COLOR_WHITE = 0;
size_t COLOR_GRAY = 1;
size_t COLOR_BLACK = 2;


bool dfsCheckCycle(vector<vector<size_t>>& graph, size_t vertex, vector<size_t>& colors) {

    colors[vertex] = COLOR_GRAY;
    bool isCycle = false;

    for (size_t neighborVertex : graph[vertex]) {
        if (colors[neighborVertex] == COLOR_WHITE) {
            isCycle = isCycle || dfsCheckCycle(graph, neighborVertex, colors);
        }
        if (colors[neighborVertex] == 1) {
            isCycle = true;
        }
    }
    colors[vertex] = 2;
    return isCycle;
}


void dfsTopologicalSort(vector<vector<size_t>>& graph, size_t vertex,
    vector<bool>& used, vector<size_t>& ans) {

    used[vertex] = true;

    for (size_t neighborVertex : graph[vertex]) {

        if (used[neighborVertex] == false) {
            dfsTopologicalSort(graph, neighborVertex, used, ans);
        }
    }
    ans.push_back(vertex);
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n;
    size_t m;
    cin >> n >> m;

    vector<vector<size_t>> directedGraph(n);
    vector<size_t> colors(n, COLOR_WHITE);
    bool isCycle = false;

    size_t firstVertex, secondVertex;

    for (size_t i = 0; i < m; i++) {
        cin >> firstVertex >> secondVertex;
        firstVertex--;
        secondVertex--;
        directedGraph[firstVertex].push_back(secondVertex);
    }

    for (size_t i = 0; i < n; i++) {
        if (colors[i] == 0) {
            isCycle = isCycle || dfsCheckCycle(directedGraph, i, colors);
        }
    }

    if (isCycle) {
        cout << -1 << endl;
    }
    else {
        vector<size_t> ans;
        vector<bool> used(n, false);

        for (size_t i = 0; i < n; i++) {
            if (used[i] == false) {
                dfsTopologicalSort(directedGraph, i, used, ans);
            }
        }

        for (int i = ans.size() - 1; i >= 0; i--) {
            cout << ans[i] + 1 << " ";
        }
    }

    return 0;
}