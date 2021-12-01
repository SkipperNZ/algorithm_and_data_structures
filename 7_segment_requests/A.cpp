#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <list>

using namespace std;

const int MOD_VEC = pow(2, 16);
const int MOD_QUERY = pow(2, 30);


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n;
    int a, x, y;
    cin >> n;
    cin >> x >> y >> a;

    size_t m;
    int b, z, t;
    cin >> m;
    cin >> z >> t >> b;

    vector<long long> sumVec(n);

    sumVec[0] = a;
    long long currentVal = a;

    for (size_t i = 1; i < n; i++) {
        currentVal = (currentVal * x + y) % MOD_VEC;
        sumVec[i] = currentVal + sumVec[i - 1];
    }

    vector<long long> queryVec(2 * m);
    currentVal = b;

    for (size_t i = 0; i < 2 * m; i++) {
        queryVec[i] = currentVal % n;
        currentVal = (currentVal * z + t) % MOD_QUERY;
    }

    long long sumOfSum = 0;
    size_t l, r;

    for (size_t i = 0; i < m; i++) {
        l = min(queryVec[2 * i + 1], queryVec[2 * i]);
        r = max(queryVec[2 * i + 1], queryVec[2 * i]);
        if (l == 0) {
            sumOfSum += sumVec[r];
        }
        else {
            sumOfSum += sumVec[r] - sumVec[l - 1];
        }
    }
    cout << sumOfSum << endl;

    return 0;
}