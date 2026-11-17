/*
 * @lc app=leetcode.cn id=463 lang=cpp
 * @lcpr version=30204
 *
 * [463] 岛屿的周长
 */


// @lcpr-template-start
#include "../header.h"
// @lcpr-template-end
// @lc code=start
using pii = pair<int, int>;
const int DIRECT[][2] = {{1,0}, {-1,0}, {0, 1}, {0, -1}};
class Solution {
    int islandPerimeterOpt(vector<vector<int>>& grid) {
        int m = static_cast<int>(grid.size());
        int n = static_cast<int>(grid[0].size());
        int ans = 0;
        const int dx[] = {1, -1, 0, 0}, dy[] = {0, 0, 1, -1};
        for (int x = 0; x < m; x++) {
            for (int y = 0; y < n; y++) {
                if (grid[x][y] != 1) continue;
                for (int i = 0; i < 4; i++) {
                    int nx = x + dx[i], ny = y + dy[i];
                    // 越界或水：该方向是暴露边
                    if (nx < 0 || nx >= m || ny < 0 || ny >= n || grid[nx][ny] == 0) {
                        ans++;
                    }
                }
            }
        }
        return ans;
    }

public:
    int islandPerimeter(vector<vector<int>>& grid) {
        int m=grid.size(), n=grid[0].size();
        int ans=0;
        for(int x=0; x<m; x++) {
            for(int y=0; y<n; y++) {
                if(grid[x][y] != 1) continue;
                for(int i=0; i<4; i++) {
                    int nx=x+DIRECT[i][0], ny=y+DIRECT[i][1];
                    if(nx<0 || nx >= m || ny < 0 || ny >= n || grid[nx][ny] == 0) {
                        ans++;
                    }
                }
            }
        }
        return ans;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [[0,1,0,0],[1,1,1,0],[0,1,0,0],[1,1,0,0]]\n
// @lcpr case=end

// @lcpr case=start
// [[1]]\n
// @lcpr case=end

// @lcpr case=start
// [[1,0]]\n
// @lcpr case=end

 */

