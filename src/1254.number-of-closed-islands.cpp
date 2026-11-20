/*
 * @lc app=leetcode.cn id=1254 lang=cpp
 * @lcpr version=30204
 *
 * [1254] 统计封闭岛屿的数目
 */


// @lcpr-template-start
#include "../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    // 返回 (x, y) 所在块是否完全不触边界；块内所有格子本趟全部标记为 -1
    bool dfsOpt(vector<vector<int>>& grid, int x, int y) {
        int m = static_cast<int>(grid.size());
        int n = static_cast<int>(grid[0].size());
        if (x < 0 || x >= m || y < 0 || y >= n) return false; // 触界即不封闭
        if (grid[x][y] != 0) return true;   // 水或已访问：不构成触界
        grid[x][y] = -1;                    // 改值即标记
        // 必须先全部求值再聚合：短路 && 会跳过后续递归导致块标记不完整
        bool d = dfsOpt(grid, x + 1, y);
        bool u = dfsOpt(grid, x - 1, y);
        bool r = dfsOpt(grid, x, y + 1);
        bool l = dfsOpt(grid, x, y - 1);
        return d && u && r && l;
    }

    int closedIslandOpt(vector<vector<int>>& grid) {
        int m = static_cast<int>(grid.size());
        int n = static_cast<int>(grid[0].size());
        int ans = 0;
        for (int x = 0; x < m; x++) {
            for (int y = 0; y < n; y++) {
                if (grid[x][y] == 0 && dfsOpt(grid, x, y)) ans++; // 遇未访问陆地块判定一次
            }
        }
        return ans;
    }

public:
    bool dfs(vector<vector<int>>& grid, int x, int y) {
        int m=grid.size(), n=grid[0].size();
        if(x < 0 || x >= m || y < 0 || y >= n) {
            return false;
        }

        if(grid[x][y] != 0) return true;
        grid[x][y] = -1;
        bool res1 = dfs(grid, x+1, y);
        bool res2 = dfs(grid, x-1, y);
        bool res3 = dfs(grid, x, y+1);
        bool res4 = dfs(grid, x, y-1);
        return res1 && res2 && res3 && res4;
    }


public:
    int closedIsland(vector<vector<int>>& grid) {
        int m=grid.size(), n=grid[0].size();
        int ans=0;
        for(int x=0; x<m; x++) {
            for(int y=0; y<n; y++) {
                if(grid[x][y] == 0 && dfs(grid, x, y)) {
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
// [[1,1,1,1,1,1,1,0],[1,0,0,0,0,1,1,0],[1,0,1,0,1,1,1,0],[1,0,0,0,0,1,0,1],[1,1,1,1,1,1,1,0]]\n
// @lcpr case=end

// @lcpr case=start
// [[0,0,1,0,0],[0,1,0,1,0],[0,1,1,1,0]]\n
// @lcpr case=end

// @lcpr case=start
// [[1,1,1,1,1,1,1],[1,0,0,0,0,0,1],[1,0,1,1,1,0,1],[1,0,1,0,1,0,1],[1,0,1,1,1,0,1],[1,0,0,0,0,0,1],[1,1,1,1,1,1,1]]\n
// @lcpr case=end

 */

