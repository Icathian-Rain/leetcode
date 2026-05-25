/*
 * @lc app=leetcode.cn id=74 lang=cpp
 * @lcpr version=30204
 *
 * [74] 搜索二维矩阵
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    bool searchMatrixOpt(vector<vector<int>>& matrix, int target) {
        int rows = static_cast<int>(matrix.size());
        int cols = static_cast<int>(matrix[0].size());
        int left = 0;
        int right = rows * cols - 1;

        while (left <= right) {
            int middle = left + (right - left) / 2;
            int row = middle / cols;
            int col = middle % cols;
            if (matrix[row][col] == target) {
                return true;
            }
            if (matrix[row][col] < target) {
                left = middle + 1;
            } else {
                right = middle - 1;
            }
        }

        return false;
    }

public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m=matrix.size(), n=matrix[0].size();
        int l=0, r=m;
        while(l<r) {
            int m=l+(r-l)/2;
            if(matrix[m][0] > target) {
                r=m;
            } else {
                l=m+1;
            }
        }

        if(l == 0) return false;
        int i=l-1;
        l=0, r=n;
        while(l<r) {
            int m=l+(r-l)/2;
            if(matrix[i][m] >= target) {
                r=m;
            } else {
                l=m+1;
            }
        }
        if(l == n || matrix[i][l] != target) {
            return false;
        }
        return true;


    }
};
// @lc code=end



/*
// @lcpr case=start
// [[1,3,5,7],[10,11,16,20],[23,30,34,60]]\n3\n
// @lcpr case=end

// @lcpr case=start
// [[1,3,5,7],[10,11,16,20],[23,30,34,60]]\n13\n
// @lcpr case=end

 */

