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

const string BARRIER = " ";


vector<int> pfunction(const string& fullString) {
    vector<int> pVec(fullString.size(), 0);

    for (size_t i = 1; i < fullString.size(); i++) {
        size_t k = pVec[i - 1];
        while (k > 0 && fullString[i] != fullString[k]) {
            k = pVec[k - 1];
        }
        if (fullString[i] == fullString[k]) {
            k++;
        }
        pVec[i] = k;
    }
    return pVec;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string pString;
    string tString;
    cin >> pString >> tString;

    string fullString = pString + BARRIER + tString;
    vector<int> pVec = pfunction(fullString);
    vector<size_t> ansver;

    for (int i = pString.size() + 1; i < pVec.size(); i++) {
        if (pVec[i] == pString.size()) {
            ansver.push_back(i - pString.size() * 2 + 1);
        }
    }

    cout << ansver.size() << "\n";
    for (int element : ansver) {
        cout << element << " ";
    }

    return 0;
}