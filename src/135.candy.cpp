/*
 * @lc app=leetcode.cn id=135 lang=cpp
 * @lcpr version=30204
 *
 * [135] 分发糖果
 */


// @lcpr-template-start
#include "../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    int candyOpt(vector<int>& ratings) {
        int n = static_cast<int>(ratings.size());
        vector<int> left(n, 1);
        // 左向约束：比左邻评分高则比左邻多一颗
        for (int i = 1; i < n; i++) {
            if (ratings[i] > ratings[i - 1]) left[i] = left[i - 1] + 1;
        }
        int ans = 0, right = 0;
        // 右向约束滚动计算，逐位取 max 合并双向要求
        for (int i = n - 1; i >= 0; i--) {
            if (i < n - 1 && ratings[i] > ratings[i + 1]) right++;
            else right = 1;
            ans += max(left[i], right); // max 是双向约束下的必要下限
        }
        return ans;
    }

public:
    int candy(vector<int>& ratings) {
        int n=ratings.size();
        vector<int> left(n);
        for(int i=0; i<n; i++) {
            if(i>0 && ratings[i] > ratings[i-1]) {
                left[i] = left[i-1]+1;
            } else {
                left[i] = 1;
            }
        }
        int right = 0, ans = 0;
        for(int i=n-1; i>=0; i--) {
            if(i<n-1 && ratings[i] > ratings[i+1]) {
                right = right + 1;
            } else {
                right = 1;
            }
            ans += max(left[i], right);
        }
        return ans;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,0,2]\n
// @lcpr case=end

// @lcpr case=start
// [1,2,2]\n
// @lcpr case=end

 */

