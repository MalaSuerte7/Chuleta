#include <iostream>
#include <vector>
using namespace std;

// Definición de un nodo en el grafo
struct Node {
    int data;
    Node* next;
    Node(int data) : data(data), next(nullptr) {}
};

// Definición de un grafo
struct Graph {
    int V; // número de nodos
    vector<Node*> adjList; // lista de adyacencia

    // Constructor
    Graph(int V) : V(V) {
        adjList.resize(V, nullptr);
    }

    // Método para agregar una arista al grafo
    void addEdge(int u, int v) {
        // Agregar v a la lista de adyacencia de u
        Node* newNode = new Node(v);
        newNode->next = adjList[u];
        adjList[u] = newNode;

        // Agregar u a la lista de adyacencia de v (si el grafo es no dirigido)
        newNode = new Node(u);
        newNode->next = adjList[v];
        adjList[v] = newNode;
    }

    // Método para eliminar una arista del grafo
    void removeEdge(int u, int v) {
        // Eliminar v de la lista de adyacencia de u
        Node* prev = nullptr;
        Node* current = adjList[u];
        while (current && current->data != v) {
            prev = current;
            current = current->next;
        }
        if (current) {
            if (prev)
                prev->next = current->next;
            else
                adjList[u] = current->next;
            delete current;
        }

        // Eliminar u de la lista de adyacencia de v (si el grafo es no dirigido)
        prev = nullptr;
        current = adjList[v];
        while (current && current->data != u) {
            prev = current;
            current = current->next;
        }
        if (current) {
            if (prev)
                prev->next = current->next;
            else
                adjList[v] = current->next;
            delete current;
        }
    }

    // Método para imprimir el grafo
    void printGraph() {
        for (int i = 0; i < V; ++i) {
            cout << "Nodo " << i << " -> ";
            Node* temp = adjList[i];
            while (temp) {
                cout << temp->data << " ";
                temp = temp->next;
            }
            cout << endl;
        }
    }
};

int main() {
    // Creamos un grafo con 5 nodos
    Graph g(5);
    // Agregamos algunas aristas
    g.addEdge(0, 1);
    g.addEdge(0, 4);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 3);
    g.addEdge(3, 4);

    // Imprimimos el grafo
    cout << "Grafo original:" << endl;
    g.printGraph();

    // Eliminamos una arista
    g.removeEdge(1, 4);

    // Imprimimos el grafo después de eliminar la arista
    cout << "\nGrafo después de eliminar la arista (1, 4):" << endl;
    g.printGraph();

    return 0;
}
