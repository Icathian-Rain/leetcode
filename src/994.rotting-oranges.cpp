/*
 * @lc app=leetcode.cn id=994 lang=cpp
 * @lcpr version=30204
 *
 * [994] 腐烂的橘子
 */


// @lcpr-template-start
#include "../header.h"
// @lcpr-template-end
// @lc code=start
using pii=pair<int, int>;
const int DIRECT[][2]={{1,0}, {-1, 0}, {0, 1}, {0, -1}};
class Solution {
    int orangesRottingOpt(vector<vector<int>>& grid) {
        int m = static_cast<int>(grid.size());
        int n = static_cast<int>(grid[0].size());
        queue<pii> q;
        int fresh = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 2) q.push({i, j}); // 多源同时入队
                else if (grid[i][j] == 1) fresh++;
            }
        }
        int minutes = 0;
        while (!q.empty() && fresh > 0) { // fresh 归零提前停，防止末层多算 1 分钟
            int sz = static_cast<int>(q.size());
            for (int i = 0; i < sz; i++) { // 一次处理整层
                auto [x, y] = q.front(); q.pop();
                for (int d = 0; d < 4; d++) {
                    int nx = x + DIRECT[d][0], ny = y + DIRECT[d][1];
                    if (nx >= 0 && nx < m && ny >= 0 && ny < n && grid[nx][ny] == 1) {
                        grid[nx][ny] = 2; // 改值即标记
                        fresh--;
                        q.push({nx, ny});
                    }
                }
            }
            minutes++;
        }
        return fresh == 0 ? minutes : -1;
    }

public:
    int orangesRotting(vector<vector<int>>& grid) {
        int m=grid.size(), n=grid[0].size();
        queue<pii> q;
        int ans=0;
        int cnt=0;
        for(int i=0; i<m; i++) {
            for(int j=0; j<n; j++) {
                if(grid[i][j] == 2) {
                    q.push({i, j});
                } else if(grid[i][j] == 1) {
                    cnt++;
                }
            }
        }

        while(!q.empty() && cnt>0) {
            int sz=q.size();
            for(int i=0; i<sz; i++) {
                auto [x, y]=q.front(); q.pop();
                for(int j=0; j<4; j++) {
                    int nx=x+DIRECT[j][0], ny=y+DIRECT[j][1];
                    if(nx>=0 && nx<m && ny>=0 && ny<n && grid[nx][ny]==1) {
                        cnt--;
                        grid[nx][ny]=2;
                        q.push({nx, ny});
                    }
                }
            }
            ans++;
        }
        return cnt == 0 ? ans : -1;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [[2,1,1],[1,1,0],[0,1,1]]\n
// @lcpr case=end

// @lcpr case=start
// [[2,1,1],[0,1,1],[1,0,1]]\n
// @lcpr case=end

// @lcpr case=start
// [[0,2]]\n
// @lcpr case=end

 */

