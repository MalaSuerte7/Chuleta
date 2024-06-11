#include <iostream>
#include <vector>
#include <string>

using namespace std;

template <typename K, typename V>
struct HashTable {
    int numBuckets;
    vector<vector<pair<K, V>>> table;

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

int main() {
    HashTable<string, string> hashTable(10);

    hashTable.insert("nombre", "Juan");
    hashTable.insert("apellido", "Perez");
    hashTable.insert("ciudad", "Madrid");
    hashTable.insert("pais", "España");

    cout << "Tabla Hash:" << endl;
    hashTable.display();

    cout << "Buscar 'nombre': " << hashTable.search("nombre") << endl;
    cout << "Buscar 'ciudad': " << hashTable.search("ciudad") << endl;

    hashTable.remove("ciudad");

    cout << "Tabla Hash después de eliminar 'ciudad':" << endl;
    hashTable.display();

    return 0;
}
