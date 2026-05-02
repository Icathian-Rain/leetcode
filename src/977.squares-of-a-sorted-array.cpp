/*
 * @lc app=leetcode.cn id=977 lang=cpp
 * @lcpr version=30204
 *
 * [977] 有序数组的平方
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    vector<int> sortedSquaresOpt(vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        vector<int> ans(n);
        int left = 0;
        int right = n - 1;

        for (int pos = n - 1; pos >= 0; --pos) {
            if (abs(nums[left]) > abs(nums[right])) {
                ans[pos] = nums[left] * nums[left];
                ++left;
            } else {
                ans[pos] = nums[right] * nums[right];
                --right;
            }
        }

        return ans;
    }

public:
    vector<int> sortedSquares(vector<int>& nums) {
        int n=nums.size();
        vector<int> ans(n, 0);

        int right = lower_bound(nums.begin(), nums.end(), 0)-nums.begin();
        int left = right-1;

        // cout << left << " : " << right << endl;

        int idx=0;
        while(left>=0 || right<n) {
            if(left<0) {
                ans[idx] = nums[right]*nums[right];
                right++;
            } else if(right >= n) {
                ans[idx] = nums[left]*nums[left];
                left--;
            } else {
                if(abs(nums[left]) < abs(nums[right])) {
                    ans[idx] = nums[left]*nums[left];
                    left--;
                } else {
                    ans[idx] = nums[right]*nums[right];
                    right++;
                }
            }
            idx++;
        }
        return ans;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [-4,-1,0,3,10]\n
// @lcpr case=end

// @lcpr case=start
// [-7,-3,2,3,11]\n
// @lcpr case=end

 */

