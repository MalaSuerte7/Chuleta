#include <iostream>
#include <vector>
using namespace std;

class TrieNode {
public:
    vector<TrieNode*> children;
    bool isEndOfWord;

    TrieNode() : children(26, nullptr), isEndOfWord(false) {}
};

class Trie {
public:
    TrieNode* root;

    Trie() {
        root = new TrieNode();
    }

    void insert(string word) {
        TrieNode* node = root;
        for (char c : word) {
            int index = c - 'a';
            if (node->children[index] == nullptr) {
                node->children[index] = new TrieNode();
            }
            node = node->children[index];
        }
        node->isEndOfWord = true;
    }

    bool search(string word) {
        TrieNode* node = root;
        for (char c : word) {
            int index = c - 'a';
            if (node->children[index] == nullptr) {
                return false;
            }
            node = node->children[index];
        }
        return node->isEndOfWord;
    }

    bool startsWith(string prefix) {
        TrieNode* node = root;
        for (char c : prefix) {
            int index = c - 'a';
            if (node->children[index] == nullptr) {
                return false;
            }
            node = node->children[index];
        }
        return true;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */

int main() {
    Trie* trie = new Trie();
    trie->insert("apple");
    cout << boolalpha << trie->search("apple") << endl;   // return True
    cout << boolalpha << trie->search("app") << endl;     // return False
    cout << boolalpha << trie->startsWith("app") << endl; // return True
    trie->insert("app");
    cout << boolalpha << trie->search("app") << endl;     // return True
    return 0;
}
