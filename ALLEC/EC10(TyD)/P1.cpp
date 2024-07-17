// MAL 3/6
//P1
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

struct TrieNode{
    unordered_map<char, TrieNode *> edges;
    bool ended;
    TrieNode() : ended(false) {}
    ~TrieNode() {}

    void insert(TrieNode *node, string word){
      if (word.empty()){
        node->ended = true;
        return;
      }
      node->edges[word[0]] = new TrieNode();
      insert(node->edges[word[0]], word.substr(1));
    }

    string find(TrieNode *node, string word){
      string prefix = "";
      for (const auto c : word){
        if (node->edges.find(c) == node->edges.end()) return prefix;
        node = node->edges.at(c);
        prefix += c;
      }
      return "";
    }
  };

class Trie{
private:  
  TrieNode *root;

public:
  Trie(){ root = new TrieNode();}
  // insert auxiliar
  void insert(string word){
    root->insert(root, word);
  }
  // find auxiliar
  string find(string word){
    return root->find(root, word);
  }
  ~Trie() {}
};

class Solution{
private:
    Trie t;

public:
  string longestCommonPrefix(vector<string> &strs){
    for (auto &word : strs){
      t.insert(word);
    }
    return t.find(strs[0]);
  }
};

// TESTS


int main(){
    Solution s;
    vector<string> letters = {"flower", "flow", "flight"};
    string lstCommPrfx = s.longestCommonPrefix(letters);
    cout<< lstCommPrfx << endl;

    vector<string> letters2 = {"dog", "racecar", "car"};
    string lstCommPrfx2 = s.longestCommonPrefix(letters2);

    cout<< lstCommPrfx2 << endl;

    return 0;
}
