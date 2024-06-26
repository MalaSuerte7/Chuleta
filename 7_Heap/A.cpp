#include <vector>
#include <queue>
#include <unordered_map>
#include <iostream>

using namespace std;

class Solution {
public:
    double maxProbability(int n, vector<vector<int>>& edges, vector<double>& succProb, int start, int end) {
        // Step 1: Build the graph using adjacency list representation
        unordered_map<int, vector<pair<int, double>>> graph;
        for (int i = 0; i < edges.size(); ++i) {
            int a = edges[i][0];
            int b = edges[i][1];
            double prob = succProb[i];
            graph[a].push_back({b, prob});
            graph[b].push_back({a, prob});
        }
        
        // Step 2: Bellman-Ford algorithm to find the maximum probability path from start to end
        vector<double> probabilities(n, 0.0);
        probabilities[start] = 1.0; // Probability of starting at start node is 1
        
        queue<int> q;
        q.push(start);
        
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            
            for (auto& neighbor : graph[node]) {
                int next_node = neighbor.first;
                double prob = neighbor.second;
                
                if (probabilities[node] * prob > probabilities[next_node]) {
                    probabilities[next_node] = probabilities[node] * prob;
                    q.push(next_node);
                }
            }
        }
        
        return probabilities[end];
    }
};

int main() {
    // Example usage
    int n = 3;
    vector<vector<int>> edges = {{0,1},{1,2},{0,2}};
    vector<double> succProb = {0.5, 0.5, 0.2};
    int start = 0;
    int end = 2;
    
    Solution sol;
    double result = sol.maxProbability(n, edges, succProb, start, end);
    
    cout << "Output: " << result << endl;
    
    return 0;
}
