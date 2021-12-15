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


vector<int> zFunction(const string& ourString) {
    vector<int> zVec(ourString.size(), 0);
    int left = 0;
    int right = 0;

    for (int i = 1; i < ourString.size(); i++) {
        zVec[i] = max(0, min(right - i, zVec[i - left]));
        while (i + zVec[i] < ourString.size() &&
            ourString[zVec[i]] == ourString[i + zVec[i]]) {
            zVec[i]++;
        }
        if (i + zVec[i] > right) {
            left = i;
            right = zVec[i] + i;
        }
    }
    return zVec;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string ourString;
    cin >> ourString;
    vector<int> vectorZfunc = zFunction(ourString);

    for (size_t i = 1; i < vectorZfunc.size(); i++) {
        cout << vectorZfunc[i] << " ";
    }

    return 0;
}