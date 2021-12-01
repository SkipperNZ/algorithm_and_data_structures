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


class DSU {
public:
    DSU(size_t N) :
        rank(N, 0),
        parents(N)
    {
        for (int i = 0; i < N; i++) {
            parents[i] = i;
        }
    }

    int get(int index) {
        if (parents[index] != index) {
            parents[index] = get(parents[index]);
        }
        return parents[index];
    }

    void join(int left, int right) {
        left = get(left);
        right = get(right);

        if (left != right) {
            if (rank[left] > rank[right]) {
                swap(left, right);
            }
            if (rank[left] == rank[right]) {
                rank[right]++;
            }
            parents[left] = right;
        }
    }

private:
    vector<int> rank;
    vector<int> parents;
};


struct Edge {
    int from;
    int to;
    int weight;

    Edge() : from(0), to(0), weight(0) {};
    Edge(int from, int to, int weight) :
        from(from), to(to), weight(weight) {};

    bool operator<(const Edge& lhs) const {
        return this->weight < lhs.weight;
    }
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t N;
    size_t M;
    cin >> N >> M;

    vector<Edge> graph(M);
    DSU dsu(N);
    int from;
    int to;
    int weight;

    for (int i = 0; i < M; i++) {
        cin >> from >> to >> weight;
        from--;
        to--;
        graph[i] = { from, to, weight };
    }

    sort(graph.begin(), graph.end());
    long long sumWeight = 0;

    for (auto& edge : graph) {
        if (dsu.get(edge.from) != dsu.get(edge.to)) {
            sumWeight += edge.weight;
            dsu.join(edge.from, edge.to);
        }
    }

    cout << sumWeight << endl;
    return 0;
}