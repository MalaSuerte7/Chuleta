// Problema 2
#include <iostream>
#include <vector>
using namespace std;

// Estructura para un nodo de la cola
struct Node {
    int val;
    Node* next;
};

// Implementación de la cola
class Queue {
    Node* front;
    Node* rear;
    int nodes;

public:
    Queue() : nodes(0) { front = rear = nullptr; }

    int size() { return nodes; }

    int ofront() { return front->val; }

    bool empty() {
        return (!front && !rear) ? true : false;
    }

    void enqueue(int homework) {
        Node* temp = new Node();
        temp->val = homework;
        temp->next = nullptr;

        if (empty()) {
            front = rear = temp;
        } else {
            rear->next = temp;
            rear = temp;
        }
        nodes++;
    };

    void dequeue() {
        if (empty()) {
            cout << endl << "Queue vacio." << endl;
        } else {
            Node* temp = front;
            front = front->next;
            if (front == nullptr) {
                rear = nullptr;
            }
            delete temp;
            nodes--;
        }
    };
};

// Estructura para el grafo
struct Graph {
    int val; // Número de vértices
    vector<vector<int>> adyacentes; // Lista de adyacencia

    Graph(int _val) : val(_val), adyacentes(_val) {}

    void addEdge(int u, int v) {
        adyacentes[u].push_back(v);
        adyacentes[v].push_back(u);
    }

    bool bfs(int s, int d) {
        Queue queue;
        queue.enqueue(s);
        // se crea un vector de visitados
        vector<bool> visitados(this->val, false);
        visitados[s] = true;
        // Mientras que no este vacio
        while (!queue.empty()) {
            int actual = queue.ofront();
            queue.dequeue();

            if (actual == d) {
                return true;
            }

            for (int adya : adyacentes[actual]) {
                if (!visitados[adya]) {
                    queue.enqueue(adya);
                    visitados[adya] = true;
                }
            }
        }
        return false;
    }
};

class Solution {
public:
    bool problem2(int n, vector<vector<int>>& edges, int source, int destination) {
        Graph grafito(n);
        for (auto& edge : edges) {
            grafito.addEdge(edge[0], edge[1]);
        }
        return grafito.bfs(source, destination);
    }
};

int main() {
    Solution sol;

    vector<vector<int>> edges = {{0,1},{1,2},{2,0}};
    cout << sol.problem2(3, edges, 0, 2) << endl;
    vector<vector<int>> edges2 = {{0,1},{0,2},{3,5},{5,4},{4,3}};
    cout << sol.problem2(6, edges2, 0, 5);
}
