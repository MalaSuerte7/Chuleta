// //Nombres : Francisco Calle, Jimena Mamani, Alexis Raza

// // Problema 1
// #include <iostream>
// #include <vector>
// #include <unordered_map>
// #include <list>

// using namespace std;

// template <typename TV, typename TE>
// class Graph
// {
// private:
//   struct Edge; 

//   struct Vertex
//   {
//     TV data;
//     list<Edge *> edges;
//   };

//   struct Edge
//   {
//     Vertex *origin;
//     Vertex *destination;
//     TE weight;
//   };

//   unordered_map<int, Vertex *> m_vertices;

// public:
//   void insertVertex(int id, TV data)
//   {
//     auto *vertex = new Vertex();
//     vertex->data = data;
//     m_vertices[id] = vertex;
//   }

//   // añado una arista "dirigida" al grafo
//   void createEdge(int originId, int destinationId, TE weight)
//   {
//     auto origin = m_vertices[originId];
//     auto destination = m_vertices[destinationId];

//     if (origin && destination){
//       auto *edge = new Edge();
//       edge->origin = origin;
//       edge->destination = destination;
//       edge->weight = weight;

//       origin->edges.push_back(edge);
//     }
//   }

//   // devuelve el vértice con la etiqueta dada
//   Vertex *getVertex(int id){ return m_vertices[id]; }
// };

// class Solution
// {
// private:
//   Graph<int, int> g;

// public:
//   int problem1(int n, vector<vector<int>> &trust){
//     // agrego vértices al grafo para etiquetas de personas de 1 a n
//     for (int i = 1; i <= n; ++i) g.insertVertex(i, i);

//     // agrego aristas al grafo según las relaciones de confianza
//     for (auto &relation : trust) g.createEdge(relation[0], relation[1], 1); // seteo peso 1 para todas las relaciones de confianza

//     // vector de contador de confianza para cada persona
//     vector<int> trusted_count(n + 1, 0); // inicializo el contador de confianza para cada persona en 0

//     for (auto &relation : trust) trusted_count[relation[1]]++; // incremento el contador para la persona confiada

//     // for anidado para encontrar al juez del pueblo
//     for (int i = 1; i <= n; ++i){
//       if (trusted_count[i] == n - 1) { // si una persona es confiada por todas las demás
//         bool is_judge = true;
//         auto vertex = g.getVertex(i);
//         for (auto &edge : vertex->edges){
//           if (edge->origin->data == i) { // verifico si esa persona no confía en nadie (no tiene relaciones de confianza salientes)
//             is_judge = false;
//             break;
//           }
//         }
//         if (is_judge) return i; // se devuelve la etiqueta del juez del pueblo
//       }
//     }
//     return -1; // si no se encuentra ningún juez del pueblo
//   }
// };

// // TESTS

// /*
// int main()
// {
//   Solution sol;

//   // Caso de prueba
//   int n = 2;
//   vector<vector<int>> trust = {{1, 2}};
//   cout << "Resultado para el caso de prueba: " << sol.problem1(n, trust) << endl; // Salida esperada: 2

//   int n2 = 3;
//   vector<vector<int>> trust2 = {{1, 3}, {2, 3}};
//   cout << "Resultado para el caso de prueba: " << sol.problem1(n2, trust2) << endl; // Salida esperada: 3

//   int n3 = 3;
//   vector<vector<int>> trust3 = {{1, 3}, {2, 3}, {3, 1}};
//   cout << "Resultado para el caso de prueba: " << sol.problem1(n3, trust3) << endl; // Salida esperada: -1

//   return 0;
// }
// */


// // Problema 2
// #include <iostream>
// #include <vector>
// using namespace std;

// // Estructura para un nodo de la cola
// struct Node {
//     int val;
//     Node* next;
// };

// // Implementación de la cola
// class Queue {
//     Node* front;
//     Node* rear;
//     int nodes;

// public:
//     Queue() : nodes(0) { front = rear = nullptr; }

//     int size() { return nodes; }

//     int ofront() { return front->val; }

//     bool empty() {
//         return (!front && !rear) ? true : false;
//     }

//     void enqueue(int homework) {
//         Node* temp = new Node();
//         temp->val = homework;
//         temp->next = nullptr;

//         if (empty()) {
//             front = rear = temp;
//         } else {
//             rear->next = temp;
//             rear = temp;
//         }
//         nodes++;
//     };

//     void dequeue() {
//         if (empty()) {
//             cout << endl << "Queue vacio." << endl;
//         } else {
//             Node* temp = front;
//             front = front->next;
//             if (front == nullptr) {
//                 rear = nullptr;
//             }
//             delete temp;
//             nodes--;
//         }
//     };
// };

// // Estructura para el grafo
// struct Graph {
//     int val; // Número de vértices
//     vector<vector<int>> adyacentes; // Lista de adyacencia

//     Graph(int _val) : val(_val), adyacentes(_val) {}

//     void addEdge(int u, int v) {
//         adyacentes[u].push_back(v);
//         adyacentes[v].push_back(u);
//     }

//     bool bfs(int s, int d) {
//         Queue queue;
//         queue.enqueue(s);
//         // se crea un vector de visitados
//         vector<bool> visitados(this->val, false);
//         visitados[s] = true;
//         // Mientras que no este vacio
//         while (!queue.empty()) {
//             int actual = queue.ofront();
//             queue.dequeue();

//             if (actual == d) {
//                 return true;
//             }

//             for (int adya : adyacentes[actual]) {
//                 if (!visitados[adya]) {
//                     queue.enqueue(adya);
//                     visitados[adya] = true;
//                 }
//             }
//         }
//         return false;
//     }
// };

// class Solution {
// public:
//     bool problem2(int n, vector<vector<int>>& edges, int source, int destination) {
//         Graph grafito(n);
//         for (auto& edge : edges) {
//             grafito.addEdge(edge[0], edge[1]);
//         }
//         return grafito.bfs(source, destination);
//     }
// };

// // int main() {
// //     Solution sol;
// //     vector<vector<int>> edges = {{0,1},{1,2},{2,0}};
// //     cout << sol.problem2(3, edges, 0, 2);
// //     vector<vector<int>> edges2 = {{0,1},{0,2},{3,5},{5,4},{4,3}};
// //     cout << sol.problem2(6, edges2, 0, 5);
// // }

// // Problema 3
// #include <iostream>
// #include <vector>
// #include <unordered_map>
// #include <unordered_set>
// #include <list>
// using namespace std;

// template <typename TV, typename TE>
// class Graph
// {
// private:
//   struct Edge; // predeclaro la estructura de la arista

//   struct Vertex
//   {
//     TV data;
//     list<Edge *> edges; // lista de adyacencia
//     Vertex(TV val) : data(val) {}
//   };

//   struct Edge
//   {
//     Vertex *vertex1;
//     Vertex *vertex2;
//   };

//   unordered_map<int, Vertex *> m_vertexes;

// public:
//   // añado un vértice al grafo
//   void insertVertex(int id, TV data)
//   {
//     auto *vertex = new Vertex{data};
//     m_vertexes[id] = vertex;
//   }

//   // añado una arista no dirigida al grafo
//   void createEdge(int id1, int id2)
//   {
//     auto vertex1 = m_vertexes[id1];
//     auto vertex2 = m_vertexes[id2];

//     if (vertex1 && vertex2)
//     {
//       auto *edge = new Edge();
//       edge->vertex1 = vertex1;
//       edge->vertex2 = vertex2;

//       vertex1->edges.push_back(edge);
//       vertex2->edges.push_back(edge);
//     }
//   }

//   // Función para encontrar el centro del grafo estrella
//   int findCenter(){
//     unordered_map<int, int> count;

//     // contamos las apariciones de cada nodo
//     for (auto &[id, vertex] : m_vertexes) count[id] = vertex->edges.size();

//     // buscamos el nodo que aparece en todas las aristas (n-1 veces)
//     for (auto &[node, cnt] : count){
//       if (cnt == m_vertexes.size() - 1) return node;
//     }

//     // si no se encuentra retornamos -1, pero al final del problema se menciona -> Las aristas dadas representan un grafo estrella válido (en caso de que no)
//     return -1;
//   }
// };

// class Solution
// {
// private:
//   Graph<int, int> g;

// public:
//   int problem3(vector<vector<int>> &edges){
//     unordered_set<int> vertices; // inserción única de vértices en el grafo de manera eficiente (utilizo unordered_set para evitar insertar dos mismo nodos)

//     // inserto vértices y crear aristas según el vector -> edges
//     for (auto &edge : edges){
//       int id1 = edge[0];
//       int id2 = edge[1];

//       // inserto vértices solo si no se han insertado previamente
//       if (vertices.find(id1) == vertices.end()){
//         g.insertVertex(id1, id1);
//         vertices.insert(id1);
//       }

//       if (vertices.find(id2) == vertices.end()){
//         g.insertVertex(id2, id2);
//         vertices.insert(id2);
//       }

//       // creo la arista con los vértices
//       g.createEdge(id1, id2);
//     }

//     return g.findCenter();
//   }
// };

// // TESTS

// /*
// int main()
// {
//   Solution sol;
//   vector<vector<int>> edges = {{1, 2}, {2, 3}, {4, 2}};
//   int center = sol.problem3(edges);
//   cout << "El centro del grafo estrella es: " << center << endl; // Output should be 2

//   vector<vector<int>> edges2 = {{1, 2}, {5, 1}, {1, 3}, {1, 4}};
//   int center2 = sol.problem3(edges2);
//   cout << "El centro del grafo estrella es: " << center2 << endl; // Output should be 1

//   return 0;
// }
// */