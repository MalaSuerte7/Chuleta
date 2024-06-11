#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Mis librerias ------------------------------------------
template <typename K, typename V>
struct HashTable {
    int numBuckets;
    vector<vector<pair<K, V>>> table;

    // Constructor por defecto
    HashTable() : numBuckets(10) { // Tamaño predeterminado de 10
        table.resize(numBuckets);
    }

    HashTable(int size) : numBuckets(size) {
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
};
// --------------------------------------------------------


struct vertice{
    int val;
    vector<int> adj;
};

struct Graph{
    HashTable<int,vector<int>> adjList;
    Graph(){
        
    }  
};

int main(){
    // Solution sol;
    // vector<vector<int>> hi = {{1,2},{1,3},{1,4}};
    // sol.createG(hi);
}