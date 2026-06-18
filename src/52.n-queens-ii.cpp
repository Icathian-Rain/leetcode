/*
 * @lc app=leetcode.cn id=52 lang=cpp
 * @lcpr version=30204
 *
 * [52] N 皇后 II
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    int totalNQueensOpt(int n) {
        int count = 0;
        vector<bool> cols(n, false);
        vector<bool> diag1(2 * n - 1, false);
        vector<bool> diag2(2 * n - 1, false);

        function<void(int)> dfs = [&](int row) {
            if (row == n) {
                ++count;
                return;
            }

            for (int col = 0; col < n; ++col) {
                int leftDiag = row - col + n - 1;
                int rightDiag = row + col;
                if (cols[col] || diag1[leftDiag] || diag2[rightDiag]) {
                    continue;
                }
                cols[col] = diag1[leftDiag] = diag2[rightDiag] = true;
                dfs(row + 1);
                cols[col] = diag1[leftDiag] = diag2[rightDiag] = false; // 只计数，不需要维护完整棋盘。
            }
        };

        dfs(0);
        return count;
    }

public:
    int totalNQueens(int n) {
        // vector<vector<string>> ans;
        int ans = 0;
        vector<string> path(n, string(n, '.'));
        vector<bool> cols(n, false);
        vector<bool> rect(2*n-1, false);
        vector<bool> rect2(2*n-1, false);


        function<void(int)> dfs = [&](int row) -> void {
            if(row == n) {
                // ans.push_back(path);
                ans++;
                return ;
            }

            for(int col=0; col<n; col++) {
                // 坐标为(row, col)
                // check
                if(cols[col] == false && rect[row-col+n-1] == false && rect2[row+col] == false) {
                    cols[col] = true;
                    rect[row-col+n-1] = true;
                    rect2[row+col] = true;
                    path[row][col] = 'Q';
                    dfs(row+1);
                    path[row][col] = '.';
                    cols[col] = false;
                    rect[row-col+n-1] = false;
                    rect2[row+col] = false;
                }
            }
        };

        dfs(0);
        return ans;
    }
};
// @lc code=end



/*
// @lcpr case=start
// 4\n
// @lcpr case=end

// @lcpr case=start
// 1\n
// @lcpr case=end

 */

