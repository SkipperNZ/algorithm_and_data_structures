#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <list>

using namespace std;


struct VecValue {
    long long value;
    long long setted;
    long long upd;

    long long getValue() const {
        if (this->setted != INT64_MAX) {
            return this->setted + this->upd;
        }
        else {
            return this->value + this->upd;
        }
    }


    void setValue(VecValue& other) {
        if (other.setted != INT64_MAX) {
            this->setted = other.setted;
            this->upd = 0;
        }
        this->upd += other.upd;
    }


    void updValue() {
        if (this->setted != INT64_MAX) {
            this->value = this->setted;
        }
        this->value += this->upd;
        this->setted = INT64_MAX;
        this->upd = 0;
    }
};


class SegmentTree {
public:
    SegmentTree(vector<long long> a) {

        addSize = 1;
        while (addSize < a.size()) {
            addSize *= 2;
        }

        segmentVec.resize(2 * addSize - 1, { INT64_MAX, INT64_MAX, 0 });

        for (size_t i = 0; i < a.size(); ++i) {
            segmentVec[i + addSize - 1] = { a[i], INT64_MAX, 0 };
        }

        long long minValue;

        for (int i = addSize - 2; i >= 0; --i) {
            minValue = min(segmentVec[2 * i + 1].getValue(), segmentVec[2 * i + 2].getValue());
            segmentVec[i] = { minValue, INT64_MAX, 0 };
        }
    }


    void set(size_t left, size_t right, long long value) {
        set(0, 0, addSize - 1, left, right, value);
    }

    void update(size_t left, size_t right, long long value) {
        update(0, 0, addSize - 1, left, right, value);
    }

    long long rmq(size_t left, size_t right) {
        return rmq(0, 0, addSize - 1, left, right);
    }


private:
    vector<VecValue> segmentVec;
    size_t addSize;

    void set(size_t i, size_t leftVec, size_t rightVec,
        size_t left, size_t right, long long value) {

        push(i, leftVec, rightVec);

        if (leftVec >= left && rightVec <= right) {
            segmentVec[i].setted = value;
            segmentVec[i].upd = 0;
        }
        else if (leftVec <= right && rightVec >= left) {

            size_t midVec = (leftVec + rightVec) / 2;

            set(2 * i + 1, leftVec, midVec, left, right, value);
            set(2 * i + 2, midVec + 1, rightVec, left, right, value);

            long long minValue = min(segmentVec[2 * i + 1].getValue(),
                segmentVec[2 * i + 2].getValue());

            segmentVec[i] = { minValue, INT64_MAX, 0 };
        }

    };


    void update(size_t i, size_t leftVec, size_t rightVec,
        size_t left, size_t right, long long value) {

        push(i, leftVec, rightVec);

        if (leftVec >= left && rightVec <= right) {
            segmentVec[i].upd += value;
        }
        else if (leftVec <= right && rightVec >= left) {

            size_t midVec = (leftVec + rightVec) / 2;

            update(2 * i + 1, leftVec, midVec, left, right, value);
            update(2 * i + 2, midVec + 1, rightVec, left, right, value);

            long long minValue = min(segmentVec[2 * i + 1].getValue(),
                segmentVec[2 * i + 2].getValue());

            segmentVec[i] = { minValue, INT64_MAX, 0 };
        }
    };


    void push(size_t i, size_t left, size_t right) {
        if (left == right) {
            segmentVec[i].updValue();
        }
        else {
            segmentVec[2 * i + 1].setValue(segmentVec[i]);
            segmentVec[2 * i + 2].setValue(segmentVec[i]);
            segmentVec[i].updValue();
        }
    }


    long long rmq(size_t i, size_t leftVec, size_t rightVec,
        size_t left, size_t right) {

        push(i, leftVec, rightVec);

        if (leftVec > right || rightVec < left) {
            return INT64_MAX;
        }
        else if (leftVec >= left && rightVec <= right) {
            return segmentVec[i].getValue();
        }
        else {
            size_t midVec = (leftVec + rightVec) / 2;
            return min(rmq(2 * i + 1, leftVec, midVec, left, right),
                rmq(2 * i + 2, midVec + 1, rightVec, left, right));
        }
    }
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n;
    cin >> n;

    vector<long long> vec(n);
    cin >> vec[0];

    for (size_t i = 1; i < n; ++i) {
        cin >> vec[i];
    }

    size_t left;
    size_t right;
    string operation;
    long long x;
    SegmentTree t(vec);

    while (cin >> operation) {
        cin >> left >> right;
        if (operation == "min") {
            cout << t.rmq(left - 1, right - 1) << "\n";
        }
        else if (operation == "set") {
            cin >> x;
            t.set(left - 1, right - 1, x);
        }
        else {
            cin >> x;
            t.update(left - 1, right - 1, x);
        }
    }
    return 0;
}