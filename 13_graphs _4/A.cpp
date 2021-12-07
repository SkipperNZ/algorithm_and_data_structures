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


int pushFlow(int vertex, int drain, int currentFlow,
    vector<vector<Edge>>& graph, vector<bool>& used) {

    used[vertex] = true;

    if (vertex == drain) {
        return currentFlow;
    }

    for (auto& edge : graph[vertex]) {
        if (!used[edge.to] && edge.usedFlow < edge.flow) {
            int nextFlow = min(currentFlow, edge.flow - edge.usedFlow);
            int delta = pushFlow(edge.to, drain, nextFlow, graph, used);
            if (delta > 0) {
                edge.usedFlow += delta;
                graph[edge.to][edge.id].usedFlow -= delta;
                return delta;
            }
        }
    }
    return 0;
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

    vector<vector<Edge>> graph(N);
    vector<bool> used;
    int result = 0;

    for (int i = 0; i < M; i++) {
        cin >> from >> to >> flow;
        from--;
        to--;
        graph[from].push_back(Edge(from, to, flow, 0, graph[to].size()));
        graph[to].push_back(Edge(to, from, flow, 0, graph[from].size() - 1));
    }

    while (true) {
        used.assign(N, false);
        int delta = pushFlow(0, N - 1, INT32_MAX, graph, used);
        if (delta > 0) {
            result += delta;
        }
        else {
            break;
        }
    }
    cout << result << "\n";

    return 0;
}