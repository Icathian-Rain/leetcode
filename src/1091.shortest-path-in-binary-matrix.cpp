/*
 * @lc app=leetcode.cn id=1091 lang=cpp
 * @lcpr version=30204
 *
 * [1091] 二进制矩阵中的最短路径
 */


// @lcpr-template-start
#include "../header.h"
// @lcpr-template-end
// @lc code=start
using pii=pair<int, int>;
const int DIRECT[][2] = {{1,0}, {-1,0}, {0,1}, {0,-1}, {1,1}, {1, -1}, {-1, -1}, {-1, 1}};
class Solution {
    int shortestPathBinaryMatrixOpt(vector<vector<int>>& grid) {
        int n = static_cast<int>(grid.size());
        if (grid[0][0] != 0) return -1; // 起点是墙
        vector<vector<int>> dist(n, vector<int>(n, -1)); // -1 = 未访问，也是失败返回值
        queue<pii> q;
        // 8方向
        const int dx[] = {1, -1, 0, 0, 1, 1, -1, -1};
        const int dy[] = {0, 0, 1, -1, 1, -1, 1, -1};
        dist[0][0] = 1; // 节点数口径：起点即 1
        q.push({0, 0});
        while (!q.empty()) {
            auto [x, y] = q.front(); q.pop();
            for (int d = 0; d < 8; d++) {
                int nx = x + dx[d], ny = y + dy[d];
                if (nx >= 0 && nx < n && ny >= 0 && ny < n
                    && grid[nx][ny] == 0 && dist[nx][ny] == -1) {
                    dist[nx][ny] = dist[x][y] + 1; // 填值即标记
                    q.push({nx, ny});
                }
            }
        }
        return dist[n - 1][n - 1]; // 不可达时是 -1
    }

public:
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        if(grid[0][0] != 0) return -1;
        int n=grid.size();
        vector<vector<int>> dist(n, vector<int>(n, -1));
        queue<pii> q;
        q.push({0, 0});
        dist[0][0]=1;
        while(!q.empty()) {
            auto [x, y]=q.front(); q.pop();
            for(int i=0; i<8; i++) {
                int nx=x+DIRECT[i][0], ny=y+DIRECT[i][1];
                if(nx>=0 && nx<n && ny>=0 && ny<n && grid[nx][ny]==0 && dist[nx][ny] ==-1) {
                    dist[nx][ny] = dist[x][y]+1;
                    q.push({nx, ny});
                }
            }
        }
        return dist[n-1][n-1];
        
    }
};
// @lc code=end



/*
// @lcpr case=start
// [[0,1],[1,0]]\n
// @lcpr case=end

// @lcpr case=start
// [[0,0,0],[1,1,0],[1,1,0]]\n
// @lcpr case=end

// @lcpr case=start
// [[1,0,0],[1,1,0],[1,1,0]]\n
// @lcpr case=end

 */

