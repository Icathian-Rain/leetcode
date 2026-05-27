/*
 * @lc app=leetcode.cn id=1901 lang=cpp
 * @lcpr version=30204
 *
 * [1901] 寻找峰值 II
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    vector<int> findPeakGridOpt(vector<vector<int>>& mat) {
        int rows = mat.size();
        int left = 0;
        int right = rows - 1;

        while (left < right) {
            int middle = left + (right - left) / 2;
            int col = max_element(mat[middle].begin(), mat[middle].end()) - mat[middle].begin();
            if (mat[middle][col] > mat[middle + 1][col]) {
                right = middle; // 当前行最大值向上不低，峰值一定在上半部分含 middle。
            } else {
                left = middle + 1; // 下方更大，沿上升方向继续寻找峰值。
            }
        }

        int col = max_element(mat[left].begin(), mat[left].end()) - mat[left].begin();
        return {left, col};
    }

public:
    vector<int> findPeakGrid(vector<vector<int>>& mat) {
        int m=mat.size();
        int l=0, r=m;
        while(l<r) {
            int i=l+(r-l)/2;
            int j=max_element(mat[i].begin(), mat[i].end())-mat[i].begin();
            if(i-1>=0 && mat[i][j] < mat[i-1][j]) {
                r = i;
                continue;
            }
            if(i+1<m && mat[i][j] < mat[i+1][j]) {
                l = i+1;
                continue;
            }
            return {i, j};
        }
        return {};


    }
};
// @lc code=end



/*
// @lcpr case=start
// [[1,4],[3,2]]\n
// @lcpr case=end

// @lcpr case=start
// [[10,20,15],[21,30,14],[7,16,32]]\n
// @lcpr case=end

 */

