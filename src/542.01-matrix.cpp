/*
 * @lc app=leetcode.cn id=542 lang=cpp
 * @lcpr version=30204
 *
 * [542] 01 矩阵
 */


// @lcpr-template-start
#include "../header.h"
// @lcpr-template-end
// @lc code=start
using pii=pair<int, int>;
const int DIRECT[][2]={{1,0}, {-1, 0}, {0, 1}, {0, -1}};
class Solution {
    vector<vector<int>> updateMatrixOpt(vector<vector<int>>& mat) {
        int m = static_cast<int>(mat.size());
        int n = static_cast<int>(mat[0].size());
        vector<vector<int>> dist(m, vector<int>(n, -1)); // -1 = 未访问
        queue<pii> q;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (mat[i][j] == 0) {
                    dist[i][j] = 0; // 多源起点：全部 0 一次入队
                    q.push({i, j});
                }
            }
        }
        while (!q.empty()) {
            auto [x, y] = q.front(); q.pop();
            for (int d = 0; d < 4; d++) {
                int nx = x + DIRECT[d][0], ny = y + DIRECT[d][1];
                if (nx >= 0 && nx < m && ny >= 0 && ny < n && dist[nx][ny] == -1) {
                    dist[nx][ny] = dist[x][y] + 1; // 填值即标记，首次到达即最近距离
                    q.push({nx, ny});
                }
            }
        }
        return dist;
    }

public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        int m=mat.size(), n=mat[0].size();
        vector<vector<int>> ans(m, vector<int>(n, -1));
        queue<pii> q;
        for(int i=0; i<m; i++) {
            for(int j=0; j<n; j++) {
                if(mat[i][j] == 0) {
                    ans[i][j] = 0;
                    q.push({i, j});
                }
            }
        }

        while(!q.empty()) {
            auto [i, j] = q.front(); q.pop();
            for(int d=0; d<4; d++) {
                int ni=i+DIRECT[d][0], nj=j+DIRECT[d][1];
                if(ni>=0 && ni<m && nj>=0 && nj<n && ans[ni][nj]==-1) {
                    ans[ni][nj]=ans[i][j]+1;
                    q.push({ni, nj});
                }
            }
        }
        return ans; 
    }
};
// @lc code=end



/*
// @lcpr case=start
// [[0,0,0],[0,1,0],[0,0,0]]\n
// @lcpr case=end

// @lcpr case=start
// [[0,0,0],[0,1,0],[1,1,1]]\n
// @lcpr case=end

 */

