/*
 * @lc app=leetcode.cn id=240 lang=cpp
 * @lcpr version=30204
 *
 * [240] 搜索二维矩阵 II
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    bool searchMatrixOpt(vector<vector<int>>& matrix, int target) {
        int rows = static_cast<int>(matrix.size());
        int cols = static_cast<int>(matrix[0].size());
        int row = 0;
        int col = cols - 1;

        while (row < rows && col >= 0) {
            if (matrix[row][col] == target) {
                return true;
            }
            if (matrix[row][col] > target) {
                --col; // 当前列下方更大，整列当前候选可排除。
            } else {
                ++row; // 当前行左侧更小，整行当前候选可排除。
            }
        }

        return false;
    }

public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m=matrix.size(), n=matrix[0].size();
        int i=0, j=n-1;
        while(i<m && j>=0) {
            if(matrix[i][j] == target) {
                return true;
            } else if(matrix[i][j] > target) {
                j--;
            } else {
                i++;
            }
        }
        return false;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]]\n5\n
// @lcpr case=end

// @lcpr case=start
// [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]]\n20\n
// @lcpr case=end

 */

