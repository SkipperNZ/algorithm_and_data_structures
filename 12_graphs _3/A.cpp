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
        parents(N),
        minVec(N),
        maxVec(N),
        count(N, 1)
    {
        for (int i = 0; i < N; i++) {
            parents[i] = i;
            minVec[i] = i;
            maxVec[i] = i;
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

            minVec[right] = min(minVec[left], minVec[right]);
            maxVec[right] = max(maxVec[left], maxVec[right]);

            count[right] = count[right] + count[left];
        }
    }

    void print(int index) {
        int parent = get(index);
        int minimum = minVec[parent];
        int maximun = maxVec[parent];
        int countValue = count[parent];
        cout << minimum + 1 << " " << maximun + 1 << " " << countValue << "\n";
    }

private:
    vector<int> rank;
    vector<int> parents;
    vector<int> minVec;
    vector<int> maxVec;
    vector<int> count;
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t N;
    cin >> N;

    DSU dsu(N);
    string operation;
    int first, second;

    while (cin >> operation) {
        if (operation == "get") {
            cin >> first;
            dsu.print(first - 1);
        }
        else {
            cin >> first >> second;
            dsu.join(first - 1, second - 1);
        }
    }
    return 0;
}