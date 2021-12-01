#include <iostream>
#include <vector>
#include <string>
#include <cstdint>

using namespace std;

vector<int> wordsToVec(const string& str) {
    int MAX_INDEX = 'z' + 1;
    vector<int> cnt(MAX_INDEX);
    for (const char& c : str) {
        cnt[c]++;
    }
    return cnt;
}

int64_t substringCounter(const string& cards, const string& sequence) {
    int64_t counter = 0;
    vector<int> vecCards = wordsToVec(cards);

    int start = 0;
    int end = 0;
    bool isOverflow = false;

    while (end <= sequence.size()) {
        //slide end and count
        while (!isOverflow) {
            int addAnagram = end - start;
            counter += addAnagram;
            end++;

            if (end > sequence.size()) {
                break;
            }

            int indexOfLetter = sequence[end - 1];
            vecCards[indexOfLetter]--;

            if (vecCards[indexOfLetter] < 0) {
                isOverflow = true;
            }
        }

        //slide start
        while (isOverflow) {
            int indexOfLetter = sequence[start];
            start++;
            vecCards[indexOfLetter]++;

            if (vecCards[indexOfLetter] == 0) {
                isOverflow = false;
            }
        }
    }
    return counter;
}

int main() {
    int n;
    int m;
    cin >> n >> m;

    string sequence;
    cin >> sequence;

    string cards;
    cin >> cards;

    cout << substringCounter(cards, sequence) << endl;

    return 0;
}