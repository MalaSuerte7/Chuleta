// P2
#include <iostream>
#include <vector>
using namespace std;

class DisjointSet {
private:
    vector<int> parent;
    vector<int> rank;

public:
    DisjointSet(int n) {
        parent.resize(n + 1);
        rank.resize(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
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

    bool is_connected(int x, int y) {
        return Find(x) == Find(y);
    }
};

class Solution {
public:
    bool possibleBipartition(int n, vector<vector<int>>& dislikes) {
        DisjointSet ds(2 * n);

        for (auto& pair : dislikes) {
            int a = pair[0];
            int b = pair[1];

            if (ds.is_connected(a, b)) {
                return false;
            }

            ds.Union(a, b + n);
            ds.Union(b, a + n);
        }
        return true;
    }
};

int main() {
    Solution sol;
    vector<vector<int>> dis1 = {{1, 2}, {1, 3}, {2, 4}};
    cout << sol.possibleBipartition(4, dis1)<< endl; // Output: true

    vector<vector<int>> dis2 = {{1, 2}, {1, 3}, {2, 3}};
    cout << sol.possibleBipartition(3, dis2)<< endl; // Output: false

    return 0;
}
