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

    void remove(K &key) {
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
    vector<nGraph*> adj;
};

class Graph {
public:
    HashTable<int, vector<nGraph*>> egid;

    Graph() {}

    Graph(vector<vector<int>> pairs) {
        for (vector<int> pair : pairs) {
            insert(pair);
        }
    }

    void insert(vector<int> _pair) {
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

    bool search(vector<int> _pair) {
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
        bool bo; //existe camino

        HashTable<int, bool> visited;

        while (!stack.empty()) {
            int vertex = stack.pop();
            if (!visited.search(vertex)) {
                cout << vertex << " ";
                visited.insert(vertex, true);
            }

            for (nGraph* neighbor : egid.search(vertex)) {
                if (!visited.search(neighbor->val)) {
                    stack.push(neighbor->val);
                }
            }
        }
        cout << endl;
        return bo;
    }
};

class Solution {
public:
    vector<bool> checkIfPrerequisite(int numCourses, vector<vector<int>>& prerequisites, vector<vector<int>>& queries) {
        Graph* g = new Graph(prerequisites); // se arma el grafo
        vector<bool> rpts;
        // Se hace un DFS para encontrar el camino
        for(auto val : queries){
            rpts.push_back(g->DFS(val[0], val[1]));
        }
        return rpts;
    }
};

int main() {
    Solution sol1;
    int numCourses1 = 2;
    vector<vector<int>> prerequisites1 = {{1,0}};
    vector<vector<int>> queries1 = {{0,1},{1,0}};
    sol1.checkIfPrerequisite(numCourses1, prerequisites1, queries1);
    // Output: {false},{true}
    cout << endl;
    Solution sol2;
    int numCourses2 = 3;
    vector<vector<int>> prerequisites2 = {{1,2},{1,0},{2,0}};
    vector<vector<int>> queries2 = {{1,0},{1,2}};
    sol2.checkIfPrerequisite(numCourses2, prerequisites2, queries2);
    // Output: {true},{true}

    return 0;
}
