#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <list>

using namespace std;


class FenwickTree {
public:
    FenwickTree(vector<long long>& sumVec) {
        vec.resize(sumVec.size());
        for (auto i = 0; i < sumVec.size(); i++) {
            size_t lb = func(i);
            if (lb == 0) {
                vec[i] = sumVec[i];
            }
            else {
                vec[i] = sumVec[i] - sumVec[lb - 1];
            }
        }

    }


    void add(size_t i, long long x) {
        while (i < vec.size()) {
            vec[i] += x;
            i = i | (i + 1);

        }
    }


    long long rsq(size_t l, size_t r) {
        if (l == 0) {
            return get(r);
        }
        return get(r) - get(l - 1);
    }


private:
    vector<long long> vec;

    size_t func(size_t i) {
        return i & (i + 1);
    }

    long long get(int i) {
        long long ans = 0;
        while (i >= 0)
        {
            ans += vec[i];
            i = func(i) - 1;
        }
        return ans;
    }

};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n;
    cin >> n;

    vector<long long> sumVec(n);
    vector<long long> vec(n);

    cin >> vec[0];
    sumVec[0] = vec[0];

    for (size_t i = 1; i < n; i++) {
        cin >> vec[i];
        sumVec[i] = sumVec[i - 1] + vec[i];
    }

    size_t index;
    string operation;
    long long x;
    FenwickTree t(sumVec);

    while (cin >> operation) {
        cin >> index >> x;
        if (operation == "sum") {
            cout << t.rsq(index - 1, x - 1) << "\n";
        }
        else {
            t.add(index - 1, x - vec[index - 1]);
            vec[index - 1] = x;
        }
    }
    return 0;
}