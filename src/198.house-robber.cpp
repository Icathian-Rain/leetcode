/*
 * @lc app=leetcode.cn id=198 lang=cpp
 * @lcpr version=30204
 *
 * [198] 打家劫舍
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    int robOpt(vector<int>& nums) {
        int bestTwoBack = 0;
        int bestOneBack = 0;
        for (int money : nums) {
            // 偷当前房屋只能接在前两间之前的最优结果后面。
            int current = max(bestOneBack, bestTwoBack + money);
            bestTwoBack = bestOneBack;
            bestOneBack = current;
        }
        return bestOneBack;
    }

public:
    int s1(vector<int>& nums) {
        int n=nums.size();
        if(n == 1) return nums[0];
        if(n == 2) return max(nums[0], nums[1]);
        vector<int> dp(n+1, 0);
        dp[1] = nums[0];
        for(int i=2; i<=n; i++) {
            dp[i] = max(dp[i-1], dp[i-2]+nums[i-1]);
        }
        return dp[n];
    }

    int s2(vector<int>& nums) {
        int n=nums.size();
        if(n == 1) return nums[0];
        if(n == 2) return max(nums[0], nums[1]);
        vector<vector<int>> dp(n+1, vector<int>(2, 0));
        for(int i=1; i<=n; i++) {
            dp[i][0] = max(dp[i-1][0], dp[i-1][1]);
            dp[i][1] = dp[i-1][0] + nums[i-1];
        }
        return max(dp[n][0], dp[n][1]);
    }


    int rob(vector<int>& nums) {
    //    return s1(nums);
        return s2(nums);


    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,2,3,1]\n
// @lcpr case=end

// @lcpr case=start
// [2,7,9,3,1]\n
// @lcpr case=end

 */

