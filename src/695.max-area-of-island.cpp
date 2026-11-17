/*
 * @lc app=leetcode.cn id=695 lang=cpp
 * @lcpr version=30204
 *
 * [695] 岛屿的最大面积
 */


// @lcpr-template-start
#include "../header.h"
// @lcpr-template-end
// @lc code=start
using pii=pair<int, int>;
const int DIRECT[][2] = {{1,0}, {-1,0}, {0, 1}, {0, -1}};
class Solution {
    int maxAreaOfIslandOpt(vector<vector<int>>& grid) {
        int m = static_cast<int>(grid.size());
        int n = static_cast<int>(grid[0].size());
        int ans = 0;
        const int dx[] = {1, -1, 0, 0}, dy[] = {0, 0, 1, -1};
        for (int x = 0; x < m; x++) {
            for (int y = 0; y < n; y++) {
                if (grid[x][y] != 1) continue;
                int area = 0;
                queue<pair<int, int>> q;
                grid[x][y] = 0; // 入队即沉岛并计数，每格恰好计一次
                area++;
                q.push({x, y});
                while (!q.empty()) {
                    auto [cx, cy] = q.front(); q.pop();
                    for (int i = 0; i < 4; i++) {
                        int nx = cx + dx[i], ny = cy + dy[i];
                        if (nx >= 0 && nx < m && ny >= 0 && ny < n && grid[nx][ny] == 1) {
                            grid[nx][ny] = 0;
                            area++;
                            q.push({nx, ny});
                        }
                    }
                }
                ans = max(ans, area);
            }
        }
        return ans;
    }

public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int m=grid.size(), n=grid[0].size();
        int ans=0;
        for(int x=0; x<m; x++) {
            for(int y=0; y<n; y++) {
                if(grid[x][y] != 1) continue;
                int sum=0;
                queue<pii> q;
                grid[x][y] = 0;
                sum ++;
                q.push({x, y});
                while(!q.empty()) {
                    auto [cx, cy] = q.front(); q.pop();
                    for(int i=0; i<4; i++) {
                        int nx=cx+DIRECT[i][0], ny=cy+DIRECT[i][1];
                        if(nx>=0 && nx<m && ny>=0 && ny<n && grid[nx][ny]==1) {
                            grid[nx][ny] = 0;
                            sum++;
                            q.push({nx, ny});
                        }
                    }
                }
                ans=max(ans, sum);
            }
        }
        return ans;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [[0,0,1,0,0,0,0,1,0,0,0,0,0],[0,0,0,0,0,0,0,1,1,1,0,0,0],[0,1,1,0,1,0,0,0,0,0,0,0,0],[0,1,0,0,1,1,0,0,1,0,1,0,0],[0,1,0,0,1,1,0,0,1,1,1,0,0],[0,0,0,0,0,0,0,0,0,0,1,0,0],[0,0,0,0,0,0,0,1,1,1,0,0,0],[0,0,0,0,0,0,0,1,1,0,0,0,0]]\n
// @lcpr case=end

// @lcpr case=start
// [[0,0,0,0,0,0,0,0]]\n
// @lcpr case=end

 */

