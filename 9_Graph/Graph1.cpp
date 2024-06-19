#include <iostream>
#include <vector>
#include <string>
using namespace std;

template <typename K, typename V>
struct HashTable {
    int numBuckets;
    vector<vector<pair<K, V>>> table;

    // Constructor por defecto
    HashTable() : numBuckets(1) { // Tamaño predeterminado de 1
        table.resize(numBuckets);
    }

    // Constructor con tamaño específico
    HashTable(int size) : numBuckets(size) {
        table.resize(numBuckets);
    }

    int hashFunction(const int &key) {
        return key % numBuckets;
    }

    int hashFunction(const string &key) {
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

struct nGraph {
    int val;
    vector<nGraph*> adj;
};

class Graph {
public:
    HashTable<int, vector<nGraph*>> egid;
    Graph() {} 
    Graph(vector<vector<int>> pairs) {
        for(vector<int> pair : pairs){
            insert(pair);
        }
    } 
    
    void insert(vector<int> _pair){
        int u = _pair[0];
        int v = _pair[1];

        if (egid.search(u).empty()) {
            egid.insert(u, {});
        }
        if (egid.search(v).empty()) {
            egid.insert(v, {});
        }

        egid.search(u).push_back(new nGraph{v, {}});
        egid.search(v).push_back(new nGraph{u, {}});
    }

    void remove(vector<int> _pair) {
        int u = _pair[0];
        int v = _pair[1];

        // Comprueba si los nodos existen en la tabla hash
        if (!egid.search(u).empty() && !egid.search(v).empty()) {
            // Elimina la adyacencia de u a v
            auto &adjU = egid.search(u);
            adjU.erase(remove_if(adjU.begin(), adjU.end(), [v](nGraph* node) { return node->val == v; }), adjU.end());

            // Elimina la adyacencia de v a u
            auto &adjV = egid.search(v);
            adjV.erase(remove_if(adjV.begin(), adjV.end(), [u](nGraph* node) { return node->val == u; }), adjV.end());
        }
    }
    
    bool search(vector<int> _pair) {
        int u = _pair[0];
        int v = _pair[1];

        // Comprueba si los nodos existen en la tabla hash
        if (!egid.search(u).empty()) {
            auto &adjU = egid.search(u);
            for (nGraph* node : adjU) {
                if (node->val == v) {
                    return true;
                }
            }
        }
        return false;
    }

    void display() {
        for (int i = 0; i < egid.numBuckets; ++i) {
            cout << "Bucket " << i << ": ";
            for (const auto &pair : egid.table[i]) {
                cout << "[" << pair.first << ": ";
                for (const auto &adjNode : pair.second) {
                    cout << adjNode->val << " ";
                }
                cout << "] ";
            }
            cout << endl;
        }
    }
};

int main() {
    Graph* g = new Graph({{1, 2}, {2, 3}, {1, 3}});
    g->display();
    return 0;
}
