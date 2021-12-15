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

const int FIRST_LETTER = 'a';
const size_t ALPHABET = 26;


class Trie {
public:
    Trie(size_t wordsCnt) : size(1) {
        next.resize(1);
        next[0].resize(ALPHABET, 0);
        levelWord.resize(wordsCnt, -1);
    }

    void insert(const string& str, size_t wordNum) {

        uint32_t level = 0;

        for (char ch : str) {
            ch -= FIRST_LETTER;

            if (next[level][ch] == 0) {
                next[level][ch] = size;
                size++;
            }
            if (next.size() < size) {
                vector<uint32_t> nextLevelVec(ALPHABET, 0);
                next.push_back(nextLevelVec);
            }
            level = next[level][ch];
        }
        if (level >= isTerminal.size()) {
            levelWord.resize(level + 1, -1);
        }
        levelWord[level] = wordNum;
    }


    vector<size_t> getSubstring(const string& str, size_t left) {

        uint32_t level = 0;
        vector<size_t> result;

        for (size_t i = left; i < str.size(); i++) {
            char ch = str[i];
            ch -= FIRST_LETTER;
            if (next[level][ch] == 0) {
                break;
            }
            level = next[level][ch];
            if (levelWord[level] != -1) {
                result.push_back(levelWord[level]);
            }
        }
        return result;
    }

private:
    uint32_t size;
    vector<vector<uint32_t>> next;
    vector<bool> isTerminal;
    vector<int> levelWord;
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string text;
    cin >> text;

    size_t M;
    cin >> M;

    Trie trie = Trie(M);
    string word;

    for (uint32_t i = 0; i < M; i++) {
        cin >> word;
        trie.insert(word, i);
    }
    vector<bool> result(M, false);
    for (uint32_t i = 0; i < text.size(); i++) {
        for (auto element : trie.getSubstring(text, i)) {
            result[element] = true;
        }
    }
    for (bool element : result) {
        if (element) {
            cout << "Yes" << "\n";
        }
        else {
            cout << "No" << "\n";
        }
    }
    return 0;
}