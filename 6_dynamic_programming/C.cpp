#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <list>
#include <sstream>

using namespace std;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> sequence(n);
    vector<int> dp(n, 1);
    vector<int> subSequence;
    vector<int> track(n, 0);

    for (size_t i = 0; i < n; i++) {
        cin >> sequence[i];
    }

    for (size_t i = 1; i < n; i++) {
        for (size_t j = 0; j < i; j++) {
            if (sequence[j] < sequence[i] && dp[i] < dp[j] + 1) {
                dp[i] = dp[j] + 1;
                track[i] = j;
            }
        }
    }

    auto maxSubseq = max_element(begin(dp), end(dp));

    cout << *maxSubseq << endl;

    size_t indexSubseqEnd = distance(dp.begin(), maxSubseq);
    int maxSubseqCnt = *maxSubseq;

    while (maxSubseqCnt > 0) {
        subSequence.push_back(sequence[indexSubseqEnd]);
        indexSubseqEnd = track[indexSubseqEnd];
        maxSubseqCnt--;
    }

    reverse(subSequence.begin(), subSequence.end());

    for (size_t i = 0; i < subSequence.size(); i++) {
        cout << subSequence[i] << " ";
    }

    return 0;
}