#include <iostream>
#include <vector>
#include <list>
using namespace std;

// HashTable ----------------------
template <typename K, typename V>
struct HashTable {
    int numBuckets;
    vector<vector<pair<K, V>>> table;

    HashTable(int size = 1) : numBuckets(size) {
        table.resize(numBuckets);
    }

    int hashFunction(const K &key) {
        size_t hashValue = 0;
        for (char ch : key) {
            hashValue = hashValue * 31 + ch;
        }
        return hashValue % numBuckets;
    }

    void insert(const K &key, const V &value) {
        int bucketIndex = hashFunction(key);
        for (auto &pair : table[bucketIndex]) {
            if (pair.first == key) {
                pair.second = value;
                return;
            }
        }
        table[bucketIndex].emplace_back(key, value);
    }

    void remove(const K &key) {
        int bucketIndex = hashFunction(key);
        auto &bucket = table[bucketIndex];
        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->first == key) {
                bucket.erase(it);
                return;
            }
        }
    }

    V search(const K &key) {
        int bucketIndex = hashFunction(key);
        for (const auto &pair : table[bucketIndex]) {
            if (pair.first == key) {
                return pair.second;
            }
        }
        return V(); // Devuelve el valor por defecto si no se encuentra
    }

    void display() {
        for (int i = 0; i < numBuckets; ++i) {
            cout << "Bucket " << i << ": ";
            for (const auto &pair : table[i]) {
                cout << "[" << pair.first << ": " << pair.second << "] ";
            }
            cout << endl;
        }
    }

    bool empty() {
        for (const auto &bucket : table) {
            if (!bucket.empty()) {
                return false;
            }
        }
        return true;
    }
};
// --------------------------------

struct vertice{
int val; // valor
vector<vertice*> adj; // vector de adjacencias vector<list<string>>
};

struct edge{
vertice* a; // inicio 
vertice* b; // final
};

class Graph {
HashTable<int, vector<vertice*>> list;
public:
    // Porseacaso
    Graph(){}
    // O(V+E) Search 
    Graph(vector<vector<int>> _into) {
        for(auto p : _into){
            //Creo nodo
            vertice* nv = new vertice;
            
            //Creo edges
            //Los agrego al table  
        }
    }
    // O(1) Insertion
    // O(1) Elimination
    // O(1) Search

};

int main() {
    vector<vector<int>> into = {{1,2},{1,3},{2,3}};   
    Graph g(into);
    return 0;
}
