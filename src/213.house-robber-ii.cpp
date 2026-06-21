/*
 * @lc app=leetcode.cn id=213 lang=cpp
 * @lcpr version=30204
 *
 * [213] 打家劫舍 II
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    int robRange(const vector<int>& nums, int left, int right) {
        int bestTwoBack = 0;
        int bestOneBack = 0;
        for (int i = left; i <= right; i++) {
            // 偷当前房屋时，前一间不能偷，只能接前两间之前的最优结果。
            int current = max(bestOneBack, bestTwoBack + nums[i]);
            bestTwoBack = bestOneBack;
            bestOneBack = current;
        }
        return bestOneBack;
    }

    int robOpt(vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        if (n == 1) return nums[0];
        // 环形限制拆成两个线性场景：不选最后一间，或不选第一间。
        return max(robRange(nums, 0, n - 2), robRange(nums, 1, n - 1));
    }

public:
    int rob(vector<int>& nums) {
        int n=nums.size();
        if(n == 1) return nums[0];
        if(n == 2) return max(nums[0], nums[1]);
        int ans = 0;
        vector<int> dp(n, 0);
        dp[0] = nums[0];
        dp[1] = max(nums[0], nums[1]);
        for(int i=2; i<=n-2; i++) {
            dp[i] = max(dp[i-1], dp[i-2]+nums[i]);
        }
        ans = max(ans, dp[n-2]);

        dp.assign(n, 0);
        dp[1] = nums[1];
        dp[2] = max(nums[1], nums[2]);
        for(int i=3; i<=n-1; i++) {
            dp[i] = max(dp[i-1], dp[i-2]+nums[i]);
        }
        ans = max(ans, dp[n-1]);
        return ans;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [2,3,2]\n
// @lcpr case=end

// @lcpr case=start
// [1,2,3,1]\n
// @lcpr case=end

// @lcpr case=start
// [1,2,3]\n
// @lcpr case=end

 */

