/*
 * @lc app=leetcode.cn id=238 lang=cpp
 * @lcpr version=30204
 *
 * [238] 除自身以外数组的乘积
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start

class Solution {
    vector<int> s1(vector<int>& nums) {
        int n = nums.size();
        vector<int> rightmul(n, 1);
        int mul = 1;
        for(int i=n-1; i>=0; i--) {
            rightmul[i] = mul;
            mul *= nums[i];
        }

        vector<int> ans(n, 1);
        mul = 1;
        for(int i=0; i<n; i++) {
            ans[i] = mul*rightmul[i];
            mul *= nums[i];
        }
        return ans;
    }

    vector<int> s2(vector<int>& nums) {
        int n=nums.size();
        vector<int> ans(n, 1);
        int mul=1;
        for(int i=0; i<n; i++) {
            ans[i] = mul;
            mul *= nums[i];
        }

        mul = 1;
        for(int i=n-1; i>=0; i--) {
            ans[i] *= mul;
            mul *= nums[i];
        }
        return ans;
        


    }
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        // return s1(nums);
        return s2(nums);

    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,2,3,4]\n
// @lcpr case=end

// @lcpr case=start
// [-1,1,0,-3,3]\n
// @lcpr case=end

 */

