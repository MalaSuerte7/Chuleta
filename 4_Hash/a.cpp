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

    bool empty() {
        for (const auto &bucket : table) {
            if (!bucket.empty()) {
                return false;
            }
        }
        return true;
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

    cout << "¿Está vacía la tabla hash?: " << (hashTable.empty() ? "Sí" : "No") << endl;

    return 0;
}

/**
 * Operaciones disponibles en la tabla hash:
 * 
 * 1. `insert(const K &key, const V &value)`: Inserta una clave y su valor asociado en la tabla hash.
 *    - Si la clave ya existe, se actualiza el valor.
 * 
 * 2. `remove(const K &key)`: Elimina la clave y su valor asociado de la tabla hash.
 *    - Si la clave no existe, no se realiza ninguna acción.
 * 
 * 3. `search(const K &key)`: Busca el valor asociado a una clave en la tabla hash.
 *    - Devuelve el valor si la clave se encuentra, de lo contrario devuelve un valor por defecto.
 * 
 * 4. `display()`: Muestra el contenido de la tabla hash, imprimiendo cada bucket y los pares clave-valor que contiene.
 * 
 * 5. `empty()`: Verifica si la tabla hash está vacía.
 *    - Devuelve `true` si todos los buckets están vacíos, de lo contrario devuelve `false`.
 */
