#include <iostream>
#include <vector>
#include <string>

using namespace std;

void radixSort(vector<string>& vec, const int& k, const int& m) {
    int firstLetter = m - 1;

    // main cycle for k phases
    for (int sortLetter = firstLetter;
        sortLetter > firstLetter - k;
        sortLetter--) {

        //part of counting sort
        vector<int> cnt('z');
        for (auto elem : vec) {
            char c = elem[sortLetter];
            cnt[c]++;
        }

        // index in p - number of char, value in p - start index for this char in sorted vector.
        vector<int> p('z');
        p['a'] = 0;
        for (char c = 'b'; c < 'z'; c++) {
            p[c] = p[c - 1] + cnt[c - 1];
        }

        // create sorted vector in current phase and replace original 
        vector<string> sortedVec(vec.size());
        for (string elem : vec) {
            char c = elem[sortLetter];
            sortedVec[p[c]] = elem;
            p[c]++;
        }
        vec = sortedVec;
    }
}


int main() {
    int n;
    int m;
    int k;

    cin >> n >> m >> k;

    vector<string> target(n);
    for (auto i = 0; i < n; i++) {
        cin >> target[i];
    }

    radixSort(target, k, m);

    for (auto item : target) {
        cout << item << endl;
    }

    return 0;
}