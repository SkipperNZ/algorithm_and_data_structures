#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <list>

using namespace std;


const int MOD_A = 16'714'589;
const int MUL_A = 23;
const int ADD_A = 21'563;

const int MUL_ONE_U = 17;
const int MUL_TWO_U = 2;
const int ADD_U = 751;

const int MUL_ONE_V = 13;
const int MUL_TWO_V = 5;
const int ADD_V = 593;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n;
    size_t m;
    int a;

    cin >> n >> m;
    cin >> a;

    vector<int> vec(n);
    vec[0] = a;

    for (size_t i = 1; i < n; i++) {
        long long element = MUL_A * vec[i - 1] + ADD_A;
        vec[i] = element % MOD_A;
    }

    vector<vector<int>> tableOfMin(n);

    vector<size_t> twoPowIndex(n + 1);
    twoPowIndex[0] = 0;

    for (size_t i = 1; i <= n; ++i) {
        twoPowIndex[i] = twoPowIndex[i - 1];

        if ((1u << (twoPowIndex[i] + 1)) <= i) {
            twoPowIndex[i]++;
        }
    }


    for (size_t i = 0; i < n; ++i) {
        tableOfMin[i].resize(twoPowIndex.back() + 1);
        tableOfMin[i][0] = vec[i];
    }

    int powTwo = 2;

    for (size_t j = 1; j <= twoPowIndex.back(); ++j) {
        for (size_t i = 0; i + powTwo - 1 < n; ++i) {
            tableOfMin[i][j] = min(tableOfMin[i][j - 1], tableOfMin[i + powTwo / 2][j - 1]);
        }
        powTwo *= 2;
    }


    size_t u, v;
    size_t l, r;
    size_t ans = 0;
    int k;
    cin >> u >> v;

    for (size_t i = 0; i < m; ++i) {
        l = u - 1;
        r = v - 1;
        if (l > r) {
            swap(l, r);
        }
        if (r - l == 0) {
            ans = vec[l];
        }
        else {
            k = twoPowIndex[r - l + 1];
            ans = min(tableOfMin[l][k], tableOfMin[r - pow(2, k) + 1][k]);
        }
        if (i < m - 1) {
            u = MUL_ONE_U * u + ADD_U + ans + MUL_TWO_U * (i + 1);
            u = u % n;
            u += 1;

            v = MUL_ONE_V * v + ADD_V + ans + MUL_TWO_V * (i + 1);
            v = v % n;
            v += 1;
        }
    }

    cout << u << " " << v << " " << ans << "\n";

    return 0;
}