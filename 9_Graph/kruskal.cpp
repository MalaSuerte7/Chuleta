#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Definición de una arista en el grafo
struct Edge {
    int src, dest, weight;

    Edge(int src, int dest, int weight) : src(src), dest(dest), weight(weight) {}
};

// Definición de un grafo
struct Graph {
    int V, E; // número de nodos y aristas
    vector<Edge> edges; // lista de aristas

    // Constructor
    Graph(int V, int E) : V(V), E(E) {}

    // Método para agregar una arista al grafo
    void addEdge(int src, int dest, int weight) {
        edges.push_back(Edge(src, dest, weight));
    }

    // Función para encontrar el conjunto al que pertenece el nodo
    int find(vector<int>& parent, int i) {
        if (parent[i] == -1)
            return i;
        return find(parent, parent[i]);
    }

    // Función para unir dos conjuntos en uno solo
    void Union(vector<int>& parent, int x, int y) {
        int xset = find(parent, x);
        int yset = find(parent, y);
        parent[xset] = yset;
    }

    // Método que implementa el algoritmo de Kruskal para encontrar el MST
    void kruskalMST() {
        vector<Edge> result; // Almacena el MST resultante

        // Ordenar todas las aristas en orden no decreciente de peso
        sort(edges.begin(), edges.end(), [](Edge a, Edge b) {
            return a.weight < b.weight;
        });

        vector<int> parent(V, -1); // Vector para almacenar los padres de los nodos

        int e = 0; // Índice de la arista resultante
        int i = 0; // Índice de la arista actual

        // El MST tendrá V-1 aristas
        while (e < V - 1 && i < E) {
            Edge next_edge = edges[i++];

            int x = find(parent, next_edge.src);
            int y = find(parent, next_edge.dest);

            // Si agregar la arista no forma un ciclo, agregarla al MST
            if (x != y) {
                result.push_back(next_edge);
                Union(parent, x, y);
                ++e;
            }
        }

        // Imprimir el MST resultante
        cout << "Aristas del MST:" << endl;
        for (int i = 0; i < e; ++i)
            cout << result[i].src << " - " << result[i].dest << " \t " << result[i].weight << endl;
    }
};

int main() {
    // Creamos un grafo con 5 nodos y 7 aristas
    Graph g(5, 7);

    // Agregamos algunas aristas
    g.addEdge(0, 1, 2);
    g.addEdge(0, 4, 6);
    g.addEdge(1, 2, 3);
    g.addEdge(1, 3, 8);
    g.addEdge(1, 4, 5);
    g.addEdge(2, 3, 0);
    g.addEdge(3, 4, 9);

    // Llamamos al método kruskalMST para encontrar el MST
    g.kruskalMST();

    return 0;
}
