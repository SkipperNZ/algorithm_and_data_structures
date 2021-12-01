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


size_t DEFAULT_COLOR = 0;


void dfs(vector<vector<size_t>>& graph, size_t vertex,
    vector<size_t>& colors, size_t currentColor) {

    colors[vertex] = currentColor;

    for (size_t neighborVertex : graph[vertex]) {
        if (colors[neighborVertex] == DEFAULT_COLOR) {
            dfs(graph, neighborVertex, colors, currentColor);
        }
    }
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
    vector<vector<size_t>> reversedGraph(n);

    vector<size_t> colors(n, DEFAULT_COLOR);
    vector<size_t> ans;
    vector<bool> used(n, false);
    size_t currentColor = DEFAULT_COLOR;
    set<pair<size_t, size_t>> condensedEdges;

    size_t firstVertex, secondVertex;


    for (size_t i = 0; i < m; i++) {
        cin >> firstVertex >> secondVertex;
        firstVertex--;
        secondVertex--;

        directedGraph[firstVertex].push_back(secondVertex);
        reversedGraph[secondVertex].push_back(firstVertex);
    }


    for (size_t i = 0; i < n; i++) {
        if (used[i] == false) {
            dfsTopologicalSort(reversedGraph, i, used, ans);
        }
    }


    reverse(ans.begin(), ans.end());

    for (size_t i = 0; i < n; i++) {
        size_t vertex = ans[i];
        if (colors[vertex] == DEFAULT_COLOR) {
            currentColor++;
            dfs(directedGraph, vertex, colors, currentColor);
        }
    }


    for (size_t i = 0; i < n; i++) {
        for (auto neigbor : directedGraph[i]) {
            if (colors[i] > colors[neigbor]) {
                condensedEdges.insert({ colors[i], colors[neigbor] });
            }
            else if (colors[i] > colors[neigbor]) {
                condensedEdges.insert({ colors[neigbor], colors[i] });
            }
        }
    }

    cout << condensedEdges.size() << endl;

    return 0;
}