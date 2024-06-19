/* Integrantes: Alexis Raza - Francisco Calle - Jimena Mamani */
// Pregunta 1
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    void dfs(vector<vector<char>>& grid, int i, int j) {
        // Si está fuera de los límites o es agua, salimos.
        if (i < 0 || i >= grid.size() || j < 0 || j >= grid[0].size() || grid[i][j] == '0') {
            return;
        }

        // Marcamos la celda como visitada (cambiando '1' a '0').
        grid[i][j] = '0';

        // Realizamos una llamada recursiva para todas las celdas adyacentes (arriba, abajo, izquierda, derecha).
        dfs(grid, i - 1, j); // arriba
        dfs(grid, i + 1, j); // abajo
        dfs(grid, i, j - 1); // izquierda
        dfs(grid, i, j + 1); // derecha
    }

    int numIslands(vector<vector<char>>& grid) {
        int count = 0;
        // Iteramos por cada celda de la matriz.
        for (int i = 0; i < grid.size(); ++i) {
            for (int j = 0; j < grid[0].size(); ++j) {
                // Si encontramos una celda de tierra, incrementamos el contador y llamamos a DFS para marcar toda la isla.
                if (grid[i][j] == '1') {
                    dfs(grid, i, j);
                    ++count;
                }
            }
        }
        return count;
    }
};

int main() {
    Solution sol;
    
    vector<vector<char>> grid1 = {
        {'1', '1', '1', '1', '0'},
        {'1', '1', '0', '1', '0'},
        {'1', '1', '0', '0', '0'},
        {'0', '0', '0', '0', '0'}
    };
    cout << "Número de islas en grid1: " << sol.numIslands(grid1) << endl; // Output: 1
    
    vector<vector<char>> grid2 = {
        {'1', '1', '0', '0', '0'},
        {'1', '1', '0', '0', '0'},
        {'0', '0', '1', '0', '0'},
        {'0', '0', '0', '1', '1'}
    };
    cout << "Número de islas en grid2: " << sol.numIslands(grid2) << endl; // Output: 3

    return 0;
}

// Pregunta 2
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct QueueNode {
    int val;
    QueueNode* next;
    QueueNode() : val(0), next(nullptr) {}
    QueueNode(int _val) : val(_val), next(nullptr) {}
};

class MyQueue {
    QueueNode* front;
    QueueNode* rear;
public:
    MyQueue() : front(nullptr), rear(nullptr) {}

    void enqueue(int x) {
        QueueNode* new_node = new QueueNode(x);
        if (rear == nullptr) {
            front = rear = new_node;
        } else {
            rear->next = new_node;
            rear = new_node;
        }
    }

    int dequeue() {
        if (front == nullptr) return -1;
        QueueNode* temp = front;
        front = front->next;
        if (front == nullptr) {
            rear = nullptr;
        }
        int val = temp->val;
        delete temp;
        return val;
    }

    bool isEmpty() {
        return front == nullptr;
    }
};

struct Stack {
    int val;
    Stack* prev;
    Stack() : val(0), prev(nullptr) {}
    Stack(int _val) : val(_val), prev(nullptr) {}
};

class MyStack {
    Stack* head;
public:
    MyStack() : head(nullptr) {}

    void push(int x) {
        Stack* new_node = new Stack(x);
        if (head == nullptr) {
            head = new_node;
        } else {
            new_node->prev = head;
            head = new_node;
        }
    }

    int pop() {
        if (head == nullptr) return -1;
        Stack* temp = head;
        head = head->prev;
        int val = temp->val;
        delete temp;
        return val;
    }

    bool empty() {
        return head == nullptr;
    }
};

template <typename K, typename V>
class HashTable {
    int numBuckets;
    vector<vector<pair<K, V>>> table;

public:
    HashTable() : numBuckets(1) {
        table.resize(numBuckets);
    }

    HashTable(int size) : numBuckets(size) {
        table.resize(numBuckets);
    }

    int hashFunction(const int& key) const {
        return key % numBuckets;
    }

    int hashFunction(const string& key) const {
        size_t hashValue = 0;
        for (char ch : key) {
            hashValue = hashValue * 31 + ch;
        }
        return hashValue % numBuckets;
    }

    void insert(const K& key, const V& value) {
        int bucketIndex = hashFunction(key);
        for (auto& pair : table[bucketIndex]) {
            if (pair.first == key) {
                pair.second = value;
                return;
            }
        }
        table[bucketIndex].emplace_back(key, value);
    }

    void remove(const K& key) {
        int bucketIndex = hashFunction(key);
        auto& bucket = table[bucketIndex];
        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->first == key) {
                bucket.erase(it);
                return;
            }
        }
    }

    V search(const K& key) const {
        int bucketIndex = hashFunction(key);
        for (const auto& pair : table[bucketIndex]) {
            if (pair.first == key) {
                return pair.second;
            }
        }
        return V();
    }

    void display() const {
        for (int i = 0; i < numBuckets; ++i) {
            cout << "Bucket " << i << ": ";
            for (const auto& pair : table[i]) {
                cout << "[" << pair.first << ": " << pair.second << "] ";
            }
            cout << endl;
        }
    }

    bool empty() const {
        for (const auto& bucket : table) {
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
    HashTable<int, vector<nGraph*>> egid;

public:
    Graph() {}

    Graph(const vector<vector<int>>& pairs) {
        for (const vector<int>& pair : pairs) {
            insert(pair);
        }
    }

    void insert(const vector<int>& _pair) {
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

    bool search(const vector<int>& _pair) {
        int u = _pair[0];
        int v = _pair[1];

        if (!egid.search(u).empty()) {
            auto adjU = egid.search(u);
            for (nGraph* node : adjU) {
                if (node->val == v) {
                    return true;
                }
            }
        }
        return false;
    }

    bool DFS(int start, int end) {
        MyStack stack;
        stack.push(start);

        HashTable<int, bool> visited;

        while (!stack.empty()) {
            int vertex = stack.pop();
            if (!visited.search(vertex)) {
                visited.insert(vertex, true);
                if (vertex == end) return true;
            }

            for (nGraph* neighbor : egid.search(vertex)) {
                if (!visited.search(neighbor->val)) {
                    stack.push(neighbor->val);
                }
            }
        }
        return false;
    }
};

class Solution {
public:
    vector<bool> checkIfPrerequisite(int numCourses, const vector<vector<int>>& prerequisites, const vector<vector<int>>& queries) {
        Graph g(prerequisites); // se arma el grafo
        vector<bool> rpts;
        // Se hace un DFS para encontrar el camino
        for (const auto& val : queries) {
            rpts.push_back(g.DFS(val[0], val[1]));
        }
        return rpts;
    }
};

int main() {
    Solution sol1;
    int numCourses1 = 2;
    vector<vector<int>> prerequisites1 = {{1, 0}};
    vector<vector<int>> queries1 = {{0, 1}, {1, 0}};
    vector<bool> result1 = sol1.checkIfPrerequisite(numCourses1, prerequisites1, queries1);
    for (bool res : result1) {
        cout << (res ? "true" : "false") << " ";
    }
    cout << endl;
    
    Solution sol2;
    int numCourses2 = 3;
    vector<vector<int>> prerequisites2 = {{1, 2}, {1, 0}, {2, 0}};
    vector<vector<int>> queries2 = {{1, 0}, {1, 2}};
    vector<bool> result2 = sol2.checkIfPrerequisite(numCourses2, prerequisites2, queries2);
    for (bool res : result2) {
        cout << (res ? "true" : "false") << " ";
    }
    cout << endl;

    return 0;
}
