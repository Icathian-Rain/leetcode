/*
 * @lc app=leetcode.cn id=200 lang=cpp
 * @lcpr version=30204
 *
 * [200] 岛屿数量
 */


// @lcpr-template-start
#include "../header.h"
// @lcpr-template-end
// @lc code=start
const int DIRECT[][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
class Solution {
    void dfs(vector<vector<char>>& grid, int x, int y) {
        int m=grid.size(), n=grid[0].size();
        grid[x][y] = '0';
        for(int i=0; i<4; i++) {
            int nx=x+DIRECT[i][0], ny=y+DIRECT[i][1];
            if(nx >= 0 && nx < m && ny >= 0 && ny < n && grid[nx][ny] == '1') {
                dfs(grid, nx, ny);
            }
        }
        return ;
    }
    int numIslandsOpt(vector<vector<char>>& grid) {
        int m = static_cast<int>(grid.size());
        int n = static_cast<int>(grid[0].size());
        int ans = 0;
        const int dx[] = {1, -1, 0, 0}, dy[] = {0, 0, 1, -1};
        for (int x = 0; x < m; x++) {
            for (int y = 0; y < n; y++) {
                if (grid[x][y] != '1') continue;
                ans++; // 遇到新岛：一次 BFS 恰好淹没一座
                queue<pair<int, int>> q;
                grid[x][y] = '0'; // 入队即沉岛，改写即访问标记
                q.push({x, y});
                while (!q.empty()) {
                    auto [cx, cy] = q.front(); q.pop();
                    for (int i = 0; i < 4; i++) {
                        int nx = cx + dx[i], ny = cy + dy[i];
                        if (nx >= 0 && nx < m && ny >= 0 && ny < n && grid[nx][ny] == '1') {
                            grid[nx][ny] = '0'; // 防止重复入队
                            q.push({nx, ny});
                        }
                    }
                }
            }
        }
        return ans;
    }

public:
    int numIslands(vector<vector<char>>& grid) {
        int m=grid.size(), n=grid[0].size();
        int ans=0;
        for(int x=0; x<m; x++) {
            for(int y=0; y<n; y++) {
                if(grid[x][y] == '1') {
                    // cout << x <<":" << y << endl;
                    dfs(grid, x, y);
                    ans++;
                }
            }
        }
        return ans;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [['1','1','1','1','0'],['1','1','0','1','0'],['1','1','0','0','0'],['0','0','0','0','0']]\n
// @lcpr case=end

// @lcpr case=start
// [['1','1','0','0','0'],['1','1','0','0','0'],['0','0','1','0','0'],['0','0','0','1','1']]\n
// @lcpr case=end

 */

