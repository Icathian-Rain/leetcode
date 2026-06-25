/*
 * @lc app=leetcode.cn id=300 lang=cpp
 * @lcpr version=30204
 *
 * [300] 最长递增子序列
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    int lengthOfLISOpt(vector<int>& nums) {
        vector<int> tails;
        for (int num : nums) {
            // tails[len - 1] 记录长度为 len 的递增子序列的最小结尾。
            auto it = lower_bound(tails.begin(), tails.end(), num);
            if (it == tails.end()) {
                tails.push_back(num);
            } else {
                *it = num;
            }
        }
        return static_cast<int>(tails.size());
    }

public:
    int lengthOfLIS(vector<int>& nums) {
        int n=nums.size();
        vector<int> dp(n+1, 1);
        int ans = 1;
        for(int i=1; i<=n; i++) {
            for(int j=i-1; j>=1; j--) {
                if(nums[i-1] > nums[j-1]) {
                    dp[i] = max(dp[i], dp[j]+1);
                }
            }
            ans = max(ans, dp[i]);
        }
        return ans;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [10,9,2,5,3,7,101,18]\n
// @lcpr case=end

// @lcpr case=start
// [0,1,0,3,2,3]\n
// @lcpr case=end

// @lcpr case=start
// [7,7,7,7,7,7,7]\n
// @lcpr case=end

 */

