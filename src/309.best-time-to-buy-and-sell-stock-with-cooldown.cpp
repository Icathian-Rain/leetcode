/*
 * @lc app=leetcode.cn id=309 lang=cpp
 * @lcpr version=30204
 *
 * [309] 买卖股票的最佳时机含冷冻期
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    int maxProfitOpt(vector<int>& prices) {
        int hold = -prices[0];
        int rest = 0;
        int sold = 0;
        for (int i = 1; i < static_cast<int>(prices.size()); i++) {
            int prevHold = hold;
            int prevRest = rest;
            int prevSold = sold;
            // 买入只能来自非冷冻的休息状态，卖出会进入当天卖出状态。
            hold = max(prevHold, prevRest - prices[i]);
            sold = prevHold + prices[i];
            rest = max(prevRest, prevSold);
        }
        return max(rest, sold);
    }

public:
    int maxProfit(vector<int>& prices) {
        int n=prices.size();
        vector<vector<int>> dp(n, vector<int>(4, 0));
        // dp[i][0]: 买入i
        // dp[i][1]: 保持i
        // dp[i][2]: 卖出i
        // dp[i][3]: 冷静期
        dp[0][0] = -prices[0];
        for(int i=1; i<n; i++) {
            dp[i][0] = max(dp[i-1][0], max(dp[i-1][3], dp[i-1][1]) - prices[i]);
            dp[i][1] = max({dp[i-1][1], dp[i-1][3]});
            dp[i][2] = dp[i-1][0]+prices[i];
            dp[i][3] = dp[i-1][2];
        }
        return max({dp[n-1][1], dp[n-1][2], dp[n-1][3]});
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,2,3,0,2]\n
// @lcpr case=end

// @lcpr case=start
// [1]\n
// @lcpr case=end

 */

