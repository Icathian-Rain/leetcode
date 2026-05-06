/*
 * @lc app=leetcode.cn id=713 lang=cpp
 * @lcpr version=30204
 *
 * [713] 乘积小于 K 的子数组
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    int numSubarrayProductLessThanKOpt(vector<int>& nums, int k) {
        if (k <= 1) {
            return 0;
        }

        int left = 0;
        int product = 1;
        int ans = 0;

        for (int right = 0; right < (int)nums.size(); ++right) {
            product *= nums[right];
            while (product >= k) {
                // 保持窗口乘积严格小于 k，之后以 right 结尾的子数组都合法。
                product /= nums[left];
                ++left;
            }

            ans += right - left + 1;
        }

        return ans;
    }

public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        int n=nums.size();
        int mul=1;
        int ans=0;
        for(int l=0, r=0; r<n; r++) {
            mul *= nums[r];
            while(l <= r && mul >= k) {
                mul /= nums[l];
                l++;
            }

            ans += (r-l+1);
        }
        return ans;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [10,5,2,6]\n100\n
// @lcpr case=end

// @lcpr case=start
// [1,2,3]\n0\n
// @lcpr case=end

 */

