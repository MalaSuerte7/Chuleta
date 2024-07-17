// #include <vector>
// #include <unordered_map>
// #include <iostream>

// using namespace std;

// // Nodo principal para: Stack & Queue
// template <class T>
// struct Node {
//     T val;
//     Node<T>* next;
// };

// // QUEUE - BFS
// template <class T>
// class Queue {
// private:
//     Node<T>* front;
//     Node<T>* rear;
//     int nodes;

// public:
//     Queue() : nodes(0) { front = rear = nullptr; }

//     int size() {
//         return nodes;
//     }

//     T _front() {
//         return front->val;
//     }

//     T _rear() {
//         return rear->val;
//     }

//     bool empty() {
//         return (!front && !rear) ? true : false;
//     }

//     void enqueue(T ele) {
//         auto* temp = new Node<T>();
//         temp->val = ele;
//         temp->next = nullptr;

//         if (empty()) front = rear = temp;
//         else {
//             rear->next = temp;
//             rear = temp;
//         }
//         nodes++;
//     }

//     void dequeue() {
//         Node<T>* temp;
//         if (empty()) cout << endl << "Queue vacio." << endl;
//         else {
//             temp = front;
//             if (front == rear)
//                 rear = rear->next;
//             front = front->next;
//             delete temp;
//             nodes--;
//         }
//     }
// };

// class Solution {
// public:
//     double maxProbability(int n, vector<vector<int>>& edges, vector<double>& succProb, int start, int end) {
//         // Adj list
//         unordered_map<int, vector<pair<int, double>>> graph; // grafo
//         for (int i = 0; i < edges.size(); ++i) {
//             //added
//             graph[edges[i][0]].push_back({edges[i][1], succProb[i]});
//             graph[edges[i][1]].push_back({edges[i][0], succProb[i]});
//         }

//         //Bellman
//         vector<double> probabilities(n, 0.0);
//         probabilities[start] = 1.0;
//         //
//         Queue<int> q;
//         //
//         q.enqueue(start);

//         while (!q.empty()) {
//             int node = q._front();
//             q.dequeue();

//             for (auto& neighbor : graph[node]) {
//                 //
//                 int nextN = neighbor.first;
//                 double prob = neighbor.second;
//                 if (probabilities[node] * prob > probabilities[nextN]) {
//                     probabilities[nextN] = probabilities[node] * prob;
//                     q.enqueue(nextN);
//                 }
//             }
//         }

//         return probabilities[end];
//     }
// };

// // Tests

// int main() {
//     Solution sol;

//     vector<vector<int>> edges = {{0,1},{1,2},{0,2}};
//     vector<double> succProb = {0.5, 0.5, 0.2};
//     cout << sol.maxProbability(3, edges, succProb, 0, 2) << endl; // esperado: 0.25

//     vector<vector<int>> edges2 = {{0,1},{1,2},{0,2}};
//     vector<double> succProb2 = {0.5, 0.5, 0.3};
//     cout << sol.maxProbability(3, edges2, succProb2, 0, 2) << endl; // esperado: 0.3

//     vector<vector<int>> edges3 = {{0,1}};
//     vector<double> succProb3 = {0.5};
//     cout << sol.maxProbability(3, edges3, succProb3, 0, 2) << endl; // esperado: 0.0
// }

#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

using namespace std;

class Solution
{
public:
    double maxProbability(int n, vector<vector<int>> &edges, vector<double> &succProb, int start_node, int end_node)
    {
        // vector de probabilidades máximas con todos sus valores en -infinito excepto el nodo de inicio
        vector<double> maxProb(n, -numeric_limits<double>::infinity());
        maxProb[start_node] = 0; // log(1) = 0

        // actualizamos según las n-1 relajaciones
        for (int i = 0; i < n - 1; ++i)
        {
            bool updated = false;
            for (int j = 0; j < edges.size(); ++j)
            {
                int u = edges[j][0];
                int v = edges[j][1];
                double logProb = log(succProb[j]);

                if (maxProb[u] != -numeric_limits<double>::infinity() && maxProb[u] + logProb > maxProb[v])
                {
                    maxProb[v] = maxProb[u] + logProb;
                    updated = true;
                }
                if (maxProb[v] != -numeric_limits<double>::infinity() && maxProb[v] + logProb > maxProb[u])
                {
                    maxProb[u] = maxProb[v] + logProb;
                    updated = true;
                }
            }
            // Si no se actualiza en una iteración, podemos terminar antes
            if (!updated)
                break;
        }

        // Si no hay un camino de start_node a end_node, devolvemos 0
        if (maxProb[end_node] == -numeric_limits<double>::infinity())
        {
            return 0.0;
        }

        // Devolvemos la probabilidad exponencial de logProbabilidad máxima
        return exp(maxProb[end_node]);
    }
};

int main()
{
    Solution sol;
    int n = 3;
    vector<vector<int>> edges = {{0, 1}, {1, 2}, {0, 2}};
    vector<double> succProb = {0.5, 0.5, 0.2};
    int start_node = 0;
    int end_node = 2;

    double result = sol.maxProbability(n, edges, succProb, start_node, end_node);
    cout << "Output: " << result << endl;

    vector<double> succProb2 = {0.5, 0.5, 0.3};
    double result2 = sol.maxProbability(n, edges, succProb2, start_node, end_node);
    cout << "Output: " << result2 << endl;

    return 0;
}
