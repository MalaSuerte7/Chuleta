#include <iostream>
#include <vector>
#include <list>
#include <limits>
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

struct vertice {
    int val; // valor
    vector<vertice*> adj; // vector de adjacencias vector<list<string>>
};

struct edge {
    vertice* a; // inicio 
    vertice* b; // final
};

class Graph {
    HashTable<int, vector<vertice*>> list;
    int numVertices;
    vector<vector<int>> dist;

public:
    // Constructor por defecto
    Graph() {}

    // Constructor para inicializar el grafo con una matriz de adyacencia
    Graph(const vector<vector<int>> &_into) : numVertices(_into.size()), dist(_into) {
        for (int i = 0; i < numVertices; ++i) {
            for (int j = 0; j < numVertices; ++j) {
                if (i != j && dist[i][j] == 0) {
                    dist[i][j] = numeric_limits<int>::max();
                }
            }
        }
    }

    // Algoritmo de Floyd-Warshall
    void floydWarshall() {
        for (int k = 0; k < numVertices; ++k) {
            for (int i = 0; i < numVertices; ++i) {
                for (int j = 0; j < numVertices; ++j) {
                    if (dist[i][k] != numeric_limits<int>::max() && dist[k][j] != numeric_limits<int>::max() && dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }
    }

    // Imprimir la matriz de distancias
    void printDistances() {
        for (int i = 0; i < numVertices; ++i) {
            for (int j = 0; j < numVertices; ++j) {
                if (dist[i][j] == numeric_limits<int>::max()) {
                    cout << "INF ";
                } else {
                    cout << dist[i][j] << " ";
                }
            }
            cout << endl;
        }
    }
};

int main() {
    vector<vector<int>> into = {
        {0, 3, numeric_limits<int>::max(), 7},
        {8, 0, 2, numeric_limits<int>::max()},
        {5, numeric_limits<int>::max(), 0, 1},
        {2, numeric_limits<int>::max(), numeric_limits<int>::max(), 0}
    };

    Graph g(into);
    g.floydWarshall();
    g.printDistances();

    return 0;
}
