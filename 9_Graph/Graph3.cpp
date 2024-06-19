#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>

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
    MyStack() {
        this->head = nullptr;
    }

    void push(int x) {
        Stack* new_node = new Stack(x);
        if (head == nullptr) {
            this->head = new_node;
        } else {
            new_node->prev = this->head;
            this->head = new_node;
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
struct HashTable {
    int numBuckets;
    vector<vector<pair<K, V>>> table;

    HashTable() : numBuckets(1) {
        table.resize(numBuckets);
    }

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
        return V();
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
    vector<pair<nGraph*, int>> adj; // Almacena adyacencias junto con los pesos
};

class Graph {
public:
    HashTable<int, vector<pair<nGraph*, int>>> egid; // Grafo dirigido ponderado

    Graph() {}

    Graph(vector<vector<int>> pairs, vector<int> weights) {
        for (size_t i = 0; i < pairs.size(); ++i) {
            insert(pairs[i], weights[i]);
        }
    }

    void insert(vector<int> _pair, int weight) {
        int u = _pair[0];
        int v = _pair[1];

        if (egid.search(u).empty()) {
            egid.insert(u, {});
        }
        if (egid.search(v).empty()) {
            egid.insert(v, {});
        }

        egid.search(u).emplace_back(new nGraph{v, {}}, weight);
    }

    void remove(vector<int> _pair) {
        int u = _pair[0];
        int v = _pair[1];

        if (!egid.search(u).empty() && !egid.search(v).empty()) {
            auto &adjU = egid.search(u);
            adjU.erase(remove_if(adjU.begin(), adjU.end(), [v](const pair<nGraph*, int> &node) { return node.first->val == v; }), adjU.end());

            auto &adjV = egid.search(v);
            adjV.erase(remove_if(adjV.begin(), adjV.end(), [u](const pair<nGraph*, int> &node) { return node.first->val == u; }), adjV.end());
        }
    }

    bool search(vector<int> _pair) {
        int u = _pair[0];
        int v = _pair[1];

        if (!egid.search(u).empty()) {
            auto &adjU = egid.search(u);
            for (const auto &node : adjU) {
                if (node.first->val == v) {
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
                    cout << adjNode.first->val << " (peso: " << adjNode.second << ") ";
                }
                cout << "] ";
            }
            cout << endl;
        }
    }

    void DFSUtil(int v, HashTable<int, bool> &visited, vector<int> &order) {
        visited.insert(v, true);
        for (const auto &neighbor : egid.search(v)) {
            if (!visited.search(neighbor.first->val)) {
                DFSUtil(neighbor.first->val, visited, order);
            }
        }
        order.push_back(v);
    }

    Graph getTranspose() {
        Graph g;
        for (int i = 0; i < egid.numBuckets; ++i) {
            for (const auto &pair : egid.table[i]) {
                int u = pair.first;
                for (const auto &v : pair.second) {
                    g.insert({v.first->val, u}, v.second);
                }
            }
        }
        return g;
    }

    bool isStronglyConnected() {
        vector<int> order;
        HashTable<int, bool> visited;

        for (int i = 0; i < egid.numBuckets; ++i) {
            for (const auto &pair : egid.table[i]) {
                if (!visited.search(pair.first)) {
                    DFSUtil(pair.first, visited, order);
                }
            }
        }

        Graph gT = getTranspose();
        visited = HashTable<int, bool>();

        while (!order.empty()) {
            int v = order.back();
            order.pop_back();
            if (!visited.search(v)) {
                vector<int> tempOrder;
                gT.DFSUtil(v, visited, tempOrder);
                if (tempOrder.size() != egid.numBuckets) {
                    return false;
                }
            }
        }
        return true;
    }

    void DFS(int start) {
        MyStack stack;
        stack.push(start);

        HashTable<int, bool> visited;

        while (!stack.empty()) {
            int vertex = stack.pop();
            if (!visited.search(vertex)) {
                cout << vertex << " ";
                visited.insert(vertex, true);
            }

            for (const auto &neighbor : egid.search(vertex)) {
                if (!visited.search(neighbor.first->val)) {
                    stack.push(neighbor.first->val);
                }
            }
        }
        cout << endl;
    }

    void BFS(int start) {
        MyQueue queue;
        queue.enqueue(start);

        HashTable<int, bool> visited;
        visited.insert(start, true);

        while (!queue.isEmpty()) {
            int vertex = queue.dequeue();
            cout << vertex << " ";

            for (const auto &neighbor : egid.search(vertex)) {
                if (!visited.search(neighbor.first->val)) {
                    queue.enqueue(neighbor.first->val);
                    visited.insert(neighbor.first->val, true);
                }
            }
        }
        cout << endl;
    }

    void Dijkstra(int start) {
        HashTable<int, int> distances;
        HashTable<int, bool> visited;
        MyQueue pq;

        for (int i = 0; i < egid.numBuckets; ++i) {
            for (const auto &pair : egid.table[i]) {
                distances.insert(pair.first, numeric_limits<int>::max());
            }
        }
        distances.insert(start, 0);
        pq.enqueue(start);

        while (!pq.isEmpty()) {
            int u = pq.dequeue();
            visited.insert(u, true);

            for (const auto &neighbor : egid.search(u)) {
                int v = neighbor.first->val;
                int weight = neighbor.second;

                if (!visited.search(v) && distances.search(u) + weight < distances.search(v)) {
                    distances.insert(v, distances.search(u) + weight);
                    pq.enqueue(v);
                }
            }
        }

        for (int i = 0; i < distances.numBuckets; ++i) {
            for (const auto &pair : distances.table[i]) {
                cout << "Distancia del nodo " << start << " al nodo " << pair.first << " es " << pair.second << endl;
            }
        }
    }
};

int main() {
    Graph* g = new Graph({{1, 2}, {2, 3}, {3, 1}, {3, 4}, {4, 3}}, {10, 5, 15, 20, 25});
    g->display();
    cout << "DFS starting from vertex 1: ";
    g->DFS(1);
    cout << "BFS starting from vertex 1: ";
    g->BFS(1);
    cout << "Is the graph strongly connected? " << (g->isStronglyConnected() ? "Yes" : "No") << endl;
    cout << "Dijkstra starting from vertex 1:" << endl;
    g->Dijkstra(1);
    return 0;
}
