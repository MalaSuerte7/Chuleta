#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

// Nodo principal para: Stack & Queue
template <class T>
struct Node {
    T val;
    Node<T>* next;
};

// QUEUE - BFS
template <class T>
class Queue {
private:
    Node<T>* front;
    Node<T>* rear;
    int nodes;

public:
    Queue() : nodes(0) { front = rear = nullptr; }

    int size() {
        return nodes;
    }

    T _front() {
        return front->val;
    }

    T _rear() {
        return rear->val;
    }

    bool empty() {
        return (!front && !rear) ? true : false;
    }

    void enqueue(T ele) {
        auto* temp = new Node<T>();
        temp->val = ele;
        temp->next = nullptr;

        if (empty()) front = rear = temp;
        else {
            rear->next = temp;
            rear = temp;
        }
        nodes++;
    }

    void dequeue() {
        Node<T>* temp;
        if (empty()) cout << endl << "Queue vacio." << endl;
        else {
            temp = front;
            if (front == rear)
                rear = rear->next;
            front = front->next;
            delete temp;
            nodes--;
        }
    }
};

class Solution {
public:
    double maxProbability(int n, vector<vector<int>>& edges, vector<double>& succProb, int start, int end) {
        // Adj list 
        unordered_map<int, vector<pair<int, double>>> graph; // grafo
        for (int i = 0; i < edges.size(); ++i) {
            //added 
            graph[edges[i][0]].push_back({edges[i][1], succProb[i]});
            graph[edges[i][1]].push_back({edges[i][0], succProb[i]});
        }
        
        //Bellman
        vector<double> probabilities(n, 0.0); 
        probabilities[start] = 1.0; 
        //
        Queue<int> q;
        //
        q.enqueue(start);
        
        while (!q.empty()) {
            int node = q._front();
            q.dequeue();
            
            for (auto& neighbor : graph[node]) {
                // 
                int nextN = neighbor.first;
                double prob = neighbor.second;
                if (probabilities[node] * prob > probabilities[nextN]) {
                    probabilities[nextN] = probabilities[node] * prob;
                    q.enqueue(nextN);
                }
            }
        }
        
        return probabilities[end];
    }
};

// Tests

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
