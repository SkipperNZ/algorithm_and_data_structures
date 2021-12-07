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
    int from;
    int to;
    int flow;
    int usedFlow;
    int id;

    Edge(int from, int to, int flow, int usedFlow, int id) :
        from(from), to(to), flow(flow), usedFlow(usedFlow), id(id) {};
};


vector<bool> dfs(size_t vertex, size_t drain,
    vector<vector<Edge*>>& graph, vector<bool>& used) {

    used[vertex] = true;

    if (vertex == drain) {
        return used;
    }
    for (auto& edge : graph[vertex]) {
        if (!used[edge->to] && edge->usedFlow < edge->flow) {
            used = dfs(edge->to, drain, graph, used);
        }
    }
    return used;
}

int maxFlowFinder(size_t N, int maxCapasity, vector<vector<Edge*>>& graph) {

    int result = 0;
    int currentPower = floor(log2(maxCapasity));

    while (currentPower >= 0) {
        queue<size_t> edgeOrder;
        edgeOrder.push(0);
        size_t currentVertex = 0;
        vector<bool> used(N, false);
        vector<Edge*> vertexPath(N);
        used[0] = true;
        int delta = pow(2, currentPower);

        while (!edgeOrder.empty() && currentVertex != N - 1) {
            currentVertex = edgeOrder.front();
            edgeOrder.pop();

            for (auto edge : graph[currentVertex]) {
                if (!used[edge->to] && edge->usedFlow < edge->flow &&
                    edge->flow - edge->usedFlow >= delta) {

                    edgeOrder.push(edge->to);
                    used[edge->to] = true;
                    vertexPath[edge->to] = edge;
                }
            }
        }

        if (currentVertex == N - 1) {
            result += delta;
            while (currentVertex != 0) {
                Edge* edge = vertexPath[currentVertex];
                edge->usedFlow += delta;
                graph[edge->to][edge->id]->usedFlow -= delta;
                currentVertex = edge->from;
            }
        }
        else {
            currentPower--;
        }
    }
    return result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t N;
    size_t M;
    cin >> N >> M;

    int from;
    int to;
    int flow;

    vector<vector<Edge*>> graph(N);
    vector<Edge*> edges;
    int maxCapasity = 0;
    vector<bool> used(N, false);
    vector<size_t> minCutEdges;
    int minCutCapacity = 0;

    for (int i = 0; i < M; i++) {
        cin >> from >> to >> flow;
        from--;
        to--;

        Edge* edge = new Edge(from, to, flow, 0, graph[to].size());
        graph[from].push_back(edge);
        edges.push_back(edge);

        Edge* reversedEdge = new Edge(to, from, flow, 0, graph[from].size() - 1);
        graph[to].push_back(reversedEdge);
        maxCapasity = max(maxCapasity, flow);
    }

    maxFlowFinder(N, maxCapasity, graph);
    used = dfs(0, N - 1, graph, used);

    for (int i = 0; i < edges.size(); i++) {
        if (used[edges[i]->to] != used[edges[i]->from]) {
            minCutCapacity += edges[i]->flow;
            minCutEdges.push_back(i + 1);
        }
    }

    cout << minCutEdges.size() << " " << minCutCapacity << "\n";

    for (auto element : minCutEdges) {
        cout << element << " ";
    }

    return 0;
}