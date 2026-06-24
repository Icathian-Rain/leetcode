/*
 * @lc app=leetcode.cn id=494 lang=cpp
 * @lcpr version=30204
 *
 * [494] 目标和
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    int findTargetSumWaysOpt(vector<int>& nums, int target) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if (abs(target) > sum || (sum + target) % 2 != 0) return 0;

        int positive = (sum + target) / 2;
        vector<int> dp(positive + 1, 0);
        dp[0] = 1;
        for (int num : nums) {
            // 每个数只能分配一次符号，所以倒序统计方案数。
            for (int value = positive; value >= num; value--) {
                dp[value] += dp[value - num];
            }
        }
        return dp[positive];
    }

public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int sum=0;
        for(auto num: nums) {
            sum += num;
        }
        // x - (sum-x) = target
        // x = (sum+target)/2
        if((sum+target)%2 != 0) return 0;
        if(abs(target) > sum) return 0;

        int x=(sum+target)/2;
        vector<int> dp(x+1, 0);
        dp[0] = 1;
        for(int i=0; i<nums.size(); i++) {
            int num=nums[i];
            for(int j=x; j>=num; j--) {
                dp[j] += dp[j-num];
            }
        }
        return dp[x];
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,1,1,1,1]\n3\n
// @lcpr case=end

// @lcpr case=start
// [1]\n1\n
// @lcpr case=end

 */

