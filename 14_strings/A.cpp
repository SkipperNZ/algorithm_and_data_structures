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

const char FIRST_LETTER = 'a' - 1;
const uint32_t P = 29;
const uint32_t MOD = 2'001'337;

long long getHash(const vector<long long>& hash,
    const vector<long long>& powP,
    uint32_t left, uint32_t right) {
    if (left == 0)
    {
        return hash[right];
    }
    else {
        return (hash[right] - (hash[left - 1] * powP[right - left + 1]) % MOD + MOD) % MOD;
    }


}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string ourString;
    uint32_t M;
    uint32_t leftFirst;
    uint32_t rightFirst;
    uint32_t leftSecond;
    uint32_t rightSecond;

    cin >> ourString;
    cin >> M;

    vector<long long> hash(ourString.size());
    vector<long long> powP(ourString.size());
    hash[0] = ourString[0] - FIRST_LETTER;
    powP[0] = 1;

    for (uint32_t i = 1; i < ourString.size(); i++) {
        hash[i] = (hash[i - 1] * P + ourString[i] - FIRST_LETTER) % MOD;
        powP[i] = (powP[i - 1] * P) % MOD;
    }

    for (uint32_t i = 0; i < M; i++) {
        cin >> leftFirst >> rightFirst >> leftSecond >> rightSecond;
        if (getHash(hash, powP, leftFirst - 1, rightFirst - 1) ==
            getHash(hash, powP, leftSecond - 1, rightSecond - 1)) {
            cout << "Yes" << "\n";
        }
        else {
            cout << "No" << "\n";
        }
    }

    return 0;
}