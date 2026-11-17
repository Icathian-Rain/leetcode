/*
 * @lc app=leetcode.cn id=1020 lang=cpp
 * @lcpr version=30204
 *
 * [1020] 飞地的数量
 */


// @lcpr-template-start
#include "../header.h"
// @lcpr-template-end
// @lc code=start
using pii = pair<int, int>;
const int DIRECT[][2] = {{1,0}, {-1,0}, {0, 1}, {0, -1}};
class Solution {
    int numEnclavesOpt(vector<vector<int>>& grid) {
        int m = static_cast<int>(grid.size());
        int n = static_cast<int>(grid[0].size());
        const int dx[] = {1, -1, 0, 0}, dy[] = {0, 0, 1, -1};
        queue<pair<int, int>> q;
        // 只收集四条边上的陆格作为起点：能离开的陆地必与它们连通
        for (int x = 0; x < m; x++) {
            for (int y = 0; y < n; y++) {
                if ((x == 0 || x == m - 1 || y == 0 || y == n - 1) && grid[x][y] == 1) {
                    grid[x][y] = 0; // 入队即沉岛
                    q.push({x, y});
                }
            }
        }
        while (!q.empty()) {
            auto [cx, cy] = q.front(); q.pop();
            for (int i = 0; i < 4; i++) {
                int nx = cx + dx[i], ny = cy + dy[i];
                if (nx >= 0 && nx < m && ny >= 0 && ny < n && grid[nx][ny] == 1) {
                    grid[nx][ny] = 0; // 入队同时沉岛
                    q.push({nx, ny});
                }
            }
        }
        int ans = 0;
        // 清除后剩余的 1 全是飞地
        for (const auto& row : grid) {
            for (int cell : row) ans += cell;
        }
        return ans;
    }

public:
    int numEnclaves(vector<vector<int>>& grid) {
        int m=grid.size(), n=grid[0].size();
        int ans=0;
        for(int x=0; x<m; x++) {
            for(int y=0; y<n; y++) {
                if((x == 0 || x == m-1 || y == 0 || y == n-1) && (grid[x][y] == 1)) {
                    queue<pii> q;
                    q.push({x, y});
                    grid[x][y] = 0;
                    while(!q.empty()) {
                        auto [cx, cy] = q.front(); q.pop();
                        for(int i=0; i<4; i++) {
                            int nx=cx+DIRECT[i][0], ny=cy+DIRECT[i][1];
                            if(nx>=0 && nx<m && ny>=0 && ny<n && grid[nx][ny]==1) {
                                q.push({nx, ny});
                                grid[nx][ny]=0;
                            }
                        }
                    }
                }
            }
        }
        for(int x=0; x<m; x++) {
            for(int y=0; y<n; y++) {
                // cout << grid[x][y] << " ";
                if(grid[x][y] == 1) {
                    ans++;
                }
            }
            // cout << endl;
        }
        return ans;


    }
};
// @lc code=end



/*
// @lcpr case=start
// [[0,0,0,0],[1,0,1,0],[0,1,1,0],[0,0,0,0]]\n
// @lcpr case=end

// @lcpr case=start
// [[0,1,1,0],[0,0,1,0],[0,0,1,0],[0,0,0,0]]\n
// @lcpr case=end

 */

