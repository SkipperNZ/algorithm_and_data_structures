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
    int usedPath;

    Edge(int from, int to, int flow, int usedFlow, int id) :
        from(from), to(to), flow(flow), usedFlow(usedFlow), id(id), usedPath(false) {};
};


int maxFlowFinder(size_t N, int start, int finish, vector<vector<Edge*>>& graph) {

    int result = 0;
    bool pathExist = true;

    while (pathExist) {

        queue<size_t> edgeOrder;
        edgeOrder.push(start);
        size_t currentVertex = start;
        vector<bool> used(N, false);
        vector<Edge*> vertexPath(N);
        used[start] = true;


        while (!edgeOrder.empty() && currentVertex != finish) {
            currentVertex = edgeOrder.front();
            edgeOrder.pop();

            for (auto edge : graph[currentVertex]) {
                if (!used[edge->to] && edge->usedFlow < edge->flow &&
                    edge->flow - edge->usedFlow > 0) {

                    edgeOrder.push(edge->to);
                    used[edge->to] = true;
                    vertexPath[edge->to] = edge;
                }
            }
        }

        if (currentVertex == finish) {
            result++;
            while (currentVertex != start) {
                Edge* edge = vertexPath[currentVertex];
                edge->usedFlow += 1;
                graph[edge->to][edge->id]->usedFlow -= 1;
                currentVertex = edge->from;
            }
        }
        else {
            pathExist = false;
        }
    }
    return result;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t N;
    size_t M;
    size_t start;
    size_t finish;
    cin >> N >> M >> start >> finish;

    start--;
    finish--;

    int from;
    int to;

    vector<vector<Edge*>> graph(N);
    vector<Edge*> edges;


    for (int i = 0; i < M; i++) {
        cin >> from >> to;
        from--;
        to--;

        Edge* edge = new Edge(from, to, 1, 0, graph[to].size());
        graph[from].push_back(edge);
        edges.push_back(edge);

        Edge* reversedEdge = new Edge(to, from, 0, 0, graph[from].size() - 1);
        graph[to].push_back(reversedEdge);
    }

    int pathCount = maxFlowFinder(N, start, finish, graph);

    if (pathCount > 1) {
        cout << "YES" << "\n";

        for (int i = 0; i < 2; i++) {
            queue<size_t> edgeOrder;
            edgeOrder.push(start);
            int currentVertex = start;
            vector<bool> used(N, false);
            vector<Edge*> vertexPath(N);
            used[start] = true;


            while (!edgeOrder.empty() && currentVertex != finish) {
                currentVertex = edgeOrder.front();
                edgeOrder.pop();

                for (auto edge : graph[currentVertex]) {
                    if (!used[edge->to] && edge->usedFlow == 1 && !edge->usedPath) {
                        edgeOrder.push(edge->to);
                        used[edge->to] = true;
                        vertexPath[edge->to] = edge;
                    }
                }
            }

            list<int> path;
            path.push_front(currentVertex);

            while (currentVertex != start) {
                Edge* edge = vertexPath[currentVertex];
                edge->usedPath = true;
                currentVertex = edge->from;
                path.push_front(currentVertex);
            }

            for (auto element : path) {
                cout << element + 1 << " ";
            }
            cout << endl;

        }
    }
    else {
        cout << "NO" << "\n";
    }

    return 0;
}