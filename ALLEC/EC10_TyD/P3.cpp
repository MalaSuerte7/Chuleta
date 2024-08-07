#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class DisjoinSet {
public:
    virtual ~DisjoinSet() {}
    virtual void MakeSet(int x) = 0;
    virtual int Find(int x) = 0;
    virtual void Union(int x, int y) = 0;
    virtual bool isConnected(int x, int y) = 0;
};

template <typename T>
class DisjoinSetArray: public DisjoinSet {
private:
    int *parent;
    int n;
public:
    DisjoinSetArray(T* data, int n) {
        parent = new int[n];
        MakeSet(n);
    }

    void MakeSet(int x) override {
        for (int i = 0; i < x; ++i)
            parent[i] = i;
    }

    int Find(int x) override {
        if (x != parent[x]) {
            parent[x] = Find(parent[x]);
        }
        return parent[x];
    }

    void Union(int x, int y) override {
        int xset = Find(x);
        int yset = Find(y);

        if (xset != yset)
            parent[yset] = xset;
    }

    bool isConnected(int x, int y) override {
        return Find(x) == Find(y);
    }

    ~DisjoinSetArray() override {
        delete[] parent;
    }
};

class Solution {
public:
    bool validPath(int n, vector<vector<int>>& edges, int source, int destination) {
        if (n < 1 || n > 2 * pow(10, 5)) return false;
        if (edges.size() < 0 || edges.size() > 2 * pow(10, 5)) return false;
        if (source < 0 || source > n - 1) return false;
        if (destination < 0 || destination > n - 1) return false;

        DisjoinSetArray<int> sets(nullptr, n);

        for (int i = 0; i < edges.size(); i++) {
            sets.Union(edges[i][0], edges[i][1]);
        }

        return sets.isConnected(source, destination);
    }
};

int main() {
    vector<vector<int>> v1 = {{0,1},{1,2},{2,0}};
    cout << Solution().validPath(3, v1, 0, 2) << endl; // Output: true (1)

    vector<vector<int>> v2 = {{0,1},{0,2},{3,5},{5,4},{4,3}};
    cout << Solution().validPath(6, v2, 0, 5) << endl; // Output: false (0)

    return 0;
}
