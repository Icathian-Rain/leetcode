/*
 * @lc app=leetcode.cn id=209 lang=cpp
 * @lcpr version=30204
 *
 * [209] 长度最小的子数组
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    int minSubArrayLenOpt(int target, vector<int>& nums) {
        int n = nums.size();
        int ans = n + 1;
        long long windowSum = 0;
        int left = 0;

        for (int right = 0; right < n; ++right) {
            windowSum += nums[right];
            while (windowSum >= target) {
                // 当前窗口已达标，先记录长度，再收缩左边界寻找更短答案。
                ans = min(ans, right - left + 1);
                windowSum -= nums[left];
                ++left;
            }
        }

        return ans == n + 1 ? 0 : ans;
    }

public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int n=nums.size();
        int ans=n+1;
        int sum=0;
        for(int l=0, r=0; r<n; r++) {
            sum += nums[r];
            while(l<=r && sum >= target) {
                ans = min(ans, r-l+1);
                sum -= nums[l];
                l++;
            }
        }
        return ans==n+1 ? 0: ans;

    }
};
// @lc code=end



/*
// @lcpr case=start
// 7\n[2,3,1,2,4,3]\n
// @lcpr case=end

// @lcpr case=start
// 4\n[1,4,4]\n
// @lcpr case=end

// @lcpr case=start
// 11\n[1,1,1,1,1,1,1,1]\n
// @lcpr case=end

 */

