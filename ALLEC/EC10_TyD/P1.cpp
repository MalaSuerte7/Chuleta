#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

struct TrieNode {
    unordered_map<char, TrieNode *> children;
    int count;
    TrieNode() : count(0) {}
};

class Trie {
private:
    TrieNode *root;

public:
    Trie() {
        root = new TrieNode();
    }

    void insert(const string &word) {
        TrieNode *node = root;
        for (const char &c : word) {
            if (node->children.find(c) == node->children.end()) {
                node->children[c] = new TrieNode();
            }
            node = node->children[c];
            node->count++;
        }
    }

    string getLongestCommonPrefix(const vector<string> &strs) {
        TrieNode *node = root;
        string prefix = "";
        for (const char &c : strs[0]) {
            if (node->children.find(c) != node->children.end() && node->children[c]->count == strs.size()) {
                prefix += c;
                node = node->children[c];
            } else {
                break;
            }
        }
        return prefix;
    }

    ~Trie() {
        delete root;
    }
};

class Solution {
public:
    string longestCommonPrefix(vector<string> &strs) {
        if (strs.empty()) return "";

        Trie t;
        for (const string &word : strs) {
            t.insert(word);
        }
        return t.getLongestCommonPrefix(strs);
    }
};

// TESTS
int main() {
    Solution s;
    vector<string> letters = {"flower", "flow", "flight"};
    string lstCommPrfx = s.longestCommonPrefix(letters);
    cout << lstCommPrfx << endl; // Output: "fl"

    vector<string> letters2 = {"dog", "racecar", "car"};
    string lstCommPrfx2 = s.longestCommonPrefix(letters2);
    cout << lstCommPrfx2 << endl; // Output: ""

    return 0;
}
