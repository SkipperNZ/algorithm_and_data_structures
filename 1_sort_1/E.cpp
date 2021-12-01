#include <iostream>
#include <string>
#include <set>
#include <map>

using namespace std;

class RomanParser {
public:
    int parse(const string& roman) {
        int result = 0;
        size_t LENGTH = roman.length();

        for (size_t i = 0; i < LENGTH; i++) {
            if ((i + 1 < LENGTH) &&
                isSubstration(roman[i], roman[i + 1])) {
                result -= coreNums[roman[i]];
            }
            else {
                result += coreNums[roman[i]];
            }
        }
        return result;
    }

private:
    map<char, int> coreNums = {
        {'I', 1},
        {'V', 5},
        {'X', 10},
        {'L', 50}
    };

    bool isSubstration(const char& lhs, const char& rhs) {
        return coreNums[lhs] < coreNums[rhs];
    }
};

struct King {
    string name;
    string romanNumber;
    int arabianNumber;
};

ostream& operator<<(ostream& stream, const King& king) {
    stream << king.name << ' ' << king.romanNumber;
    return stream;
}

bool operator<(const King& lhs, const King& rhs) {
    if (lhs.name == rhs.name) {
        return lhs.arabianNumber < rhs.arabianNumber;
    }
    return lhs.name < rhs.name;
}

int main() {
    int n;
    cin >> n;
    cin.ignore(1);

    RomanParser romanParser;
    set<King> kings;

    for (auto i = 0; i < n; i++) {
        string name;
        string romanNumber;

        getline(cin, name, ' ');
        getline(cin, romanNumber);

        kings.insert({ name, romanNumber,
            romanParser.parse(romanNumber) });
    }

    for (const auto& king : kings) {
        cout << king << endl;
    }

    return 0;
}