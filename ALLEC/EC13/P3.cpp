#include <iostream>
#include <queue>
#include <vector>
#include <cmath>
#include <unordered_set>
#include <limits.h>

using namespace std;

class Solution {
public:
    int minCost(vector<vector<int>>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();
        
        vector<vector<int>> costs(rows, vector<int>(cols, INT_MAX));
        costs[0][0] = 0;

        priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;
        pq.push({0, {0, 0}});
        
        int dir[4][2] = {{0,1}, {1,0}, {0,-1}, {-1,0}};
        
        while (!pq.empty()) {
            auto [cost, cell] = pq.top();
            pq.pop();
            int x = cell.first;
            int y = cell.second;
            
            if (x == rows - 1 && y == cols - 1) return cost;

            for (int d = 0; d < 4; ++d) {
                int nx = x + dir[d][0];
                int ny = y + dir[d][1];
                
                if (nx >= 0 && ny >= 0 && nx < rows && ny < cols) {
                    int newCost = cost + (grid[x][y] != d + 1);
                    if (newCost < costs[nx][ny]) {
                        costs[nx][ny] = newCost;
                        pq.push({newCost, {nx, ny}});
                    }
                }
            }
        }
        return -1;
    }
};

int main() {
    Solution sol;
    
    vector<vector<int>> grid1 = {{1,2,3},{4,5,6},{7,8,9}};
    cout << sol.minCost(grid1) << endl; // esperado: 4
    
    vector<vector<int>> grid2 = {{1,2,3},{4,5,6}};
    cout << sol.minCost(grid2) << endl; // esperado: 3
    
    vector<vector<int>> grid3 = {{1}};
    cout << sol.minCost(grid3) << endl; // esperado: 0
}
