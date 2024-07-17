#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class DisjointSet {
private:
    vector<int> parent;
    vector<int> rank;

public:
    DisjointSet(int n) {
        parent.resize(n);
        rank.resize(n, 1);
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }

    int Find(int x) {
        if (parent[x] != x) {
            parent[x] = Find(parent[x]);
        }
        return parent[x];
    }

    void Union(int x, int y) {
        int rootX = Find(x);
        int rootY = Find(y);

        if (rootX != rootY) {
            if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }
};

class Solution {
public:
    bool isBipartite(vector<vector<int>>& graph) {
        int n = graph.size();
        DisjointSet ds(n);

        for (int u = 0; u < n; ++u) {
            for (int v : graph[u]) {
                if (ds.Find(u) == ds.Find(v)) {
                    return false; // Si u y v están en el mismo conjunto, no es bipartito
                }
                ds.Union(graph[u][0], v); // Colocamos u y v en diferentes conjuntos
            }
        }

        return true;
    }
};

int main() {
    Solution sol;

    // Ejemplo 1
    vector<vector<int>> graph1 = {{1,2,3},{0,2},{0,1,3},{0,2}};
    cout << sol.isBipartite(graph1) << endl; // Output: false

    // Ejemplo 2
    vector<vector<int>> graph2 = {{1,3},{0,2},{1,3},{0,2}};
    cout << sol.isBipartite(graph2) << endl; // Output: true

    return 0;
}
