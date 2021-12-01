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
        expVec(N, 0)
    {
        for (int i = 0; i < N; i++) {
            parents[i] = i;
        }
    }

    void add(int index, int exp) {
        int clan = get(index);
        expVec[clan] += exp;
    }

    int getExp(int index) {
        int resultExp = 0;

        while (index != parents[index]) {
            resultExp += expVec[index];
            index = parents[index];
        }

        resultExp += expVec[index];
        return resultExp;
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

            expVec[left] -= expVec[right];
            parents[left] = right;
        }
    }

private:
    vector<int> rank;
    vector<int> parents;
    vector<int> expVec;

    int get(int index) {
        return get(index, 0).first;
    }

    pair<int, int> get(int index, int exp) {
        if (parents[index] != index) {

            pair<int, int> cleanExp = get(parents[index], exp);
            expVec[index] += cleanExp.second;
            parents[index] = cleanExp.first;

            exp = expVec[index];
        }
        return { parents[index], exp };
    }
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t N;
    size_t M;
    cin >> N >> M;

    DSU dsu(N);
    string operation;
    int first, second;

    for (int i = 0; i < M; i++) {
        cin >> operation;

        if (operation == "join") {
            cin >> first >> second;
            dsu.join(first - 1, second - 1);
        }
        else if (operation == "add") {
            cin >> first >> second;
            dsu.add(first - 1, second);
        }
        else {
            cin >> first;
            cout << dsu.getExp(first - 1) << "\n";
        }
    }
    return 0;
}