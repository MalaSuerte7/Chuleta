#include <iostream>
#include <vector>
#include <climits>

using namespace std;

// Definición de un nodo en el grafo
struct Node {
    int dest;
    int weight;
    Node* next;

    Node(int dest, int weight) : dest(dest), weight(weight), next(nullptr) {}
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
    void addEdge(int src, int dest, int weight) {
        Node* newNode = new Node(dest, weight);
        newNode->next = adjList[src];
        adjList[src] = newNode;

        // Agregar una arista en la dirección opuesta para un grafo no dirigido
        newNode = new Node(src, weight);
        newNode->next = adjList[dest];
        adjList[dest] = newNode;
    }

    // Método para encontrar el vértice con la clave mínima que no está incluido en el MST
    int minKey(vector<int>& key, vector<bool>& mstSet) {
        int min = INT_MAX, min_index;

        for (int v = 0; v < V; ++v) {
            if (!mstSet[v] && key[v] < min) {
                min = key[v];
                min_index = v;
            }
        }

        return min_index;
    }

    // Método para imprimir el MST
    void printMST(vector<int>& parent, vector<int>& key) {
        cout << "Arista \t Peso\n";
        for (int i = 1; i < V; ++i)
            cout << parent[i] << " - " << i << " \t " << key[i] << " \n";
    }

    // Método que implementa el algoritmo de Prim para encontrar el MST
    void primMST() {
        vector<int> parent(V); // Array para almacenar el MST
        vector<int> key(V); // Claves utilizadas para seleccionar el vértice de peso mínimo
        vector<bool> mstSet(V, false); // Conjunto para representar los vértices incluidos en el MST

        // Inicializar todas las claves como infinito
        // e incluir todos los vértices en el MSTSet como falso
        for (int i = 0; i < V; ++i) {
            key[i] = INT_MAX;
            mstSet[i] = false;
        }

        // La raíz siempre tiene peso cero
        key[0] = 0;
        parent[0] = -1; // La raíz no tiene padre

        // El MST tendrá V vértices
        for (int count = 0; count < V - 1; ++count) {
            // Seleccionar el vértice con la clave mínima no incluido aún en el MST
            int u = minKey(key, mstSet);

            // Agregar el vértice seleccionado al conjunto MST
            mstSet[u] = true;

            // Actualizar las claves de los vértices adyacentes del vértice seleccionado.
            Node* temp = adjList[u];
            while (temp != nullptr) {
                int v = temp->dest;
                int weight = temp->weight;
                if (!mstSet[v] && weight < key[v]) {
                    parent[v] = u;
                    key[v] = weight;
                }
                temp = temp->next;
            }
        }

        // Imprimir el MST construido
        printMST(parent, key);
    }
};

int main() {
    // Creamos un grafo con 5 nodos
    Graph g(5);

    // Agregamos algunas aristas
    g.addEdge(0, 1, 2);
    g.addEdge(0, 4, 6);
    g.addEdge(1, 2, 3);
    g.addEdge(1, 3, 8);
    g.addEdge(1, 4, 5);
    g.addEdge(2, 3, 0);
    g.addEdge(3, 4, 9);

    // Llamamos al método primMST para encontrar el MST
    cout << "Aristas del MST:" << endl;
    g.primMST();

    return 0;
}
