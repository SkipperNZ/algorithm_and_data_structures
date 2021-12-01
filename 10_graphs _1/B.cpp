#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <list>
#include <sstream>
#include <map>

using namespace std;

string PATIENT_ZERO = "polycarp";


void dfs(map<string, vector<string>>& graph, string& vertex,
    map<string, size_t>& repostChainCnt, size_t currentStep) {

    repostChainCnt[vertex] = currentStep;

    for (auto& neighborVertex : graph[vertex]) {
        if (repostChainCnt[neighborVertex] <= currentStep) {
            dfs(graph, neighborVertex, repostChainCnt, currentStep + 1);
        }
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t repostCount;
    cin >> repostCount;

    map<string, vector<string>> graph;

    string subscriber;
    string  postOwner;

    for (size_t i = 0; i < repostCount; i++) {
        cin >> subscriber >> postOwner >> postOwner;
        transform(subscriber.begin(), subscriber.end(), subscriber.begin(), tolower);
        transform(postOwner.begin(), postOwner.end(), postOwner.begin(), tolower);

        graph[postOwner].push_back(subscriber);
    }

    map<string, size_t> repostChainCnt;
    for (auto vertex : graph) {
        repostChainCnt[vertex.first] = 0;
    }

    dfs(graph, PATIENT_ZERO, repostChainCnt, 1);

    size_t largestChain = 0;

    for (auto chainLen : repostChainCnt) {
        largestChain = max(largestChain, chainLen.second);
    }

    cout << largestChain << endl;

    return 0;
}