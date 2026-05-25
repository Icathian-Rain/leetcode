/*
 * @lc app=leetcode.cn id=1351 lang=cpp
 * @lcpr version=30204
 *
 * [1351] 统计有序矩阵中的负数
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    int countNegativesOpt(vector<vector<int>>& grid) {
        int rows = static_cast<int>(grid.size());
        int cols = static_cast<int>(grid[0].size());
        int col = cols - 1;
        int ans = 0;

        for (int row = 0; row < rows; ++row) {
            while (col >= 0 && grid[row][col] < 0) {
                --col; // 当前列在这一行已为负，下一行只会更小，可以继续左移。
            }
            ans += cols - 1 - col;
        }

        return ans;
    }

public:
    int countNegatives(vector<vector<int>>& grid) {
        int m=grid.size(), n=grid[0].size();
        int j=n-1;
        int ans=0;
        for(int i=0; i<m; i++) {
            while(j>=0 && grid[i][j] < 0) {
                j--;
            }
            ans += n-1-j;
        }
        return ans;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [[4,3,2,-1],[3,2,1,-1],[1,1,-1,-2],[-1,-1,-2,-3]]\n
// @lcpr case=end

// @lcpr case=start
// [[3,2],[1,0]]\n
// @lcpr case=end

 */

