/*
 * @lc app=leetcode.cn id=122 lang=cpp
 * @lcpr version=30204
 *
 * [122] 买卖股票的最佳时机 II
 */


// @lcpr-template-start
#include "../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    int maxProfitOpt(vector<int>& prices) {
        int profit = 0;
        for (int i = 1; i < static_cast<int>(prices.size()); i++) {
            // 只收集正差值：每个上升段的涨幅都可通过当天卖当天买无损收入
            profit += max(0, prices[i] - prices[i - 1]);
        }
        return profit;
    }

public:
    int maxProfit(vector<int>& prices) {
        int n=prices.size();
        // dp[i][0]: 不持有
        // dp[i][1]: 持有
        vector<vector<int>> dp(n, vector<int>(2, n));
        dp[0][0] = 0;
        dp[0][1] = -prices[0];
        for(int i=1; i<n; i++) {
            dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i]);
            dp[i][1] = max(dp[i-1][1], dp[i-1][0] - prices[i]);
        } 
        return dp[n-1][0];
    }
};
// @lc code=end



/*
// @lcpr case=start
// [7,1,5,3,6,4]\n
// @lcpr case=end

// @lcpr case=start
// [1,2,3,4,5]\n
// @lcpr case=end

// @lcpr case=start
// [7,6,4,3,1]\n
// @lcpr case=end

 */

