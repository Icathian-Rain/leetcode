/*
 * @lc app=leetcode.cn id=416 lang=cpp
 * @lcpr version=30204
 *
 * [416] 分割等和子集
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    bool canPartitionOpt(vector<int>& nums) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if (sum % 2 != 0) return false;

        int target = sum / 2;
        vector<bool> dp(target + 1, false);
        dp[0] = true;
        for (int num : nums) {
            // 每个数只能使用一次，所以容量必须从大到小更新。
            for (int value = target; value >= num; value--) {
                dp[value] = dp[value] || dp[value - num];
            }
        }
        return dp[target];
    }

public:
    bool canPartition(vector<int>& nums) {
        int n=nums.size();
        int sum = 0, maxNum;
        for(auto num: nums) {
            sum += num;
            maxNum = max(maxNum, num);
        }
        if(sum %2 != 0) {
            return false;
        }
        int target = sum/2;
        if(maxNum > target) {
            return false;
        }

        vector<bool> dp(target+1, false);
        dp[0]=true;
        for(int i=0; i<n; i++) {
            int num = nums[i];
            for(int j=target; j>=num; j--) {
                dp[j] = dp[j]|dp[j-num];
            }
        }
        return dp[target];





    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,5,11,5]\n
// @lcpr case=end

// @lcpr case=start
// [1,2,3,5]\n
// @lcpr case=end

 */

