/*
 * @lc app=leetcode.cn id=746 lang=cpp
 * @lcpr version=30204
 *
 * [746] 使用最小花费爬楼梯
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    int minCostClimbingStairsOpt(vector<int>& cost) {
        int n = cost.size();
        int costToPrev2 = 0;
        int costToPrev1 = 0;
        for (int step = 2; step <= n; step++) {
            // 到达 step 可以从 step-1 或 step-2 跨来，离开那一级时才付费。
            int current = min(costToPrev1 + cost[step - 1],
                              costToPrev2 + cost[step - 2]);
            costToPrev2 = costToPrev1;
            costToPrev1 = current;
        }
        return costToPrev1;
    }

public:
    int minCostClimbingStairs(vector<int>& cost) {
        int n=cost.size();
        vector<int> dp(n+1, 0);
        dp[0] = 0;
        dp[1] = cost[0];
        for(int i=2; i<=n; i++) {
            dp[i] = min(dp[i-1], dp[i-2]) + cost[i-1];
        }
        return min(dp[n], dp[n-1]);
        
    }
};
// @lc code=end



/*
// @lcpr case=start
// [10,15,20]\n
// @lcpr case=end

// @lcpr case=start
// [1,100,1,1,1,100,1,1,100,1]\n
// @lcpr case=end

 */

