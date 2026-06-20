/*
 * @lc app=leetcode.cn id=70 lang=cpp
 * @lcpr version=30204
 *
 * [70] 爬楼梯
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    int climbStairsOpt(int n) {
        int twoStepsBefore = 1;
        int oneStepBefore = 1;
        for (int step = 2; step <= n; step++) {
            // 到达当前阶只能来自前一阶或前两阶，用两个变量滚动保存。
            int current = oneStepBefore + twoStepsBefore;
            twoStepsBefore = oneStepBefore;
            oneStepBefore = current;
        }
        return oneStepBefore;
    }

public:
    int climbStairs(int n) {
        vector<int> dp(n+1, 0);
        dp[0] = 1;
        dp[1] = 1;
        for(int i=2; i<=n; i++) {
            dp[i] = dp[i-1] + dp[i-2];
        }
        return dp[n];
    }
};
// @lc code=end



/*
// @lcpr case=start
// 2\n
// @lcpr case=end

// @lcpr case=start
// 3\n
// @lcpr case=end

 */

