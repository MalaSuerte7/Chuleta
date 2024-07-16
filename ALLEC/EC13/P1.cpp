#include <iostream>
#include <vector>

using namespace std;

class Stack {
private:
    struct Node {
        int data;
        Node* next;
        Node(int value) : data(value), next(nullptr) {}
    };
    Node* top;
public:
    Stack() : top(nullptr) {}

    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }

    void push(int value) {
        Node* newNode = new Node(value);
        newNode->next = top;
        top = newNode;
    }

    int pop() {
        if (top == nullptr) {
            return -1; 
        }
        int poppedData = top->data;
        Node* temp = top;
        top = top->next;
        delete temp;
        return poppedData;
    }

    bool isEmpty() {
        return top == nullptr;
    }

    void printStack() const {
        Node* current = top;
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
};

class Queue {
private:
    struct Node {
        int data;
        Node* next;
        Node(int value) : data(value), next(nullptr) {}
    };
    Node* front;
    Node* rear;
public:
    Queue() : front(nullptr), rear(nullptr) {}

    ~Queue() {
        while (!isEmpty()) {
            pop();
        }
    }

    void push(int value) {
        Node* newNode = new Node(value);
        if (front == nullptr) {
            front = newNode;
            rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    int pop() {
        if (front == nullptr) {
            return -1; 
        }
        int poppedData = front->data;
        Node* temp = front;
        front = front->next;
        if (front == nullptr) {
            rear = nullptr;
        }
        delete temp;
        return poppedData;
    }

    bool isEmpty() {
        return front == nullptr;
    }

    void printQueue() const {
        Node* current = front;
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
};

class List {
private:
    vector<int> elements;

public:
    void push_back(int value) {
        elements.push_back(value);
    }

    vector<int>::iterator begin() {
        return elements.begin();
    }

    vector<int>::iterator end() {
        return elements.end();
    }
};

class Graph {
private:
    int V; // número de vértices
    vector<List> adj; // lista de adyacencia

public:
    Graph(int V); 
    void addEdge(int v, int w); // agrega una arista al grafo
    void BFS(int s);    
    int BFS2(int s);
};

Graph::Graph(int V) {
    this->V = V;
    adj.resize(V);
}

void Graph::addEdge(int v, int w) {
    adj[v].push_back(w); // Agrega w a la lista de v
}

void Graph::BFS(int s) {
    vector<bool> visited(V, false);
    Queue queue;

    visited[s] = true;
    queue.push(s);

    while (!queue.isEmpty()) {
        s = queue.pop();
        cout << s << " ";

        for (auto adjVertex : adj[s]) {
            if (!visited[adjVertex]) {
                visited[adjVertex] = true;
                queue.push(adjVertex);
            }
        }
    }
    cout << endl;
}

// modificado retornando la cantidad de celdas visitadas
int Graph::BFS2(int s) {
    vector<bool> visited(V, false);
    Queue queue;

    int cantidadVisitadas = 1; // contando la primera celda
    visited[s] = true;
    queue.push(s);

    while (!queue.isEmpty()) {
        s = queue.pop();
        // cout << s << " ";
        for (auto adjVertex : adj[s]) {
            if (!visited[adjVertex]) {
                visited[adjVertex] = true;
                queue.push(adjVertex);
            }
        }
        cantidadVisitadas++;
    }
    return cantidadVisitadas;
}

class Solution {
public:
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        int n = grid.size(); // nxn 
        if (n < 1 || n > 100) return -1;
        int shortestpath = 0;
        Graph graph(n * n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[0][0] == 0) {
                    if (grid[i][j] == 0) {
                        graph.addEdge(i, j);
                    }
                    shortestpath = graph.BFS2(grid[0][0]);
                } else {
                    return -1;
                }
            }
        }
        return shortestpath;
    }
};

int main() {
    // [[0,1],[1,0]]
    vector<vector<int>> grid = {{0,1},{1,0}};
    cout << Solution().shortestPathBinaryMatrix(grid) << endl; // 2

    // [[0,0,0],[1,1,0],[1,1,0]]
    grid = {{0,0,0},{1,1,0},{1,1,0}};
    cout << Solution().shortestPathBinaryMatrix(grid) << endl; // 4

    // [[1,0,0],[1,1,0],[1,1,0]]
    grid = {{1,0,0},{1,1,0},{1,1,0}};
    cout << Solution().shortestPathBinaryMatrix(grid) << endl; // -1
}
