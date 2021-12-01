#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <list>
#include <sstream>

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


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n;
    size_t m;
    cin >> n >> m;

    vector<vector<size_t>> undirectedGraph(n);
    vector<size_t> colors(n, DEFAULT_COLOR);

    size_t firstVertex, secondVertex;

    for (size_t i = 0; i < m; i++) {
        cin >> firstVertex >> secondVertex;
        firstVertex--;
        secondVertex--;

        undirectedGraph[firstVertex].push_back(secondVertex);
        undirectedGraph[secondVertex].push_back(firstVertex);
    }

    size_t currentColor = DEFAULT_COLOR;

    for (size_t i = 0; i < n; i++) {
        if (colors[i] == DEFAULT_COLOR) {
            currentColor++;
            dfs(undirectedGraph, i, colors, currentColor);
        }
    }

    cout << currentColor << "\n";

    for (size_t number : colors) {
        cout << number << " ";
    }

    return 0;
}