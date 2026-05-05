/*
 * @lc app=leetcode.cn id=1004 lang=cpp
 * @lcpr version=30204
 *
 * [1004] 最大连续1的个数 III
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    int longestOnesOpt(vector<int>& nums, int k) {
        int left = 0;
        int zeroCount = 0;
        int ans = 0;

        for (int right = 0; right < (int)nums.size(); ++right) {
            if (nums[right] == 0) {
                ++zeroCount;
            }

            while (zeroCount > k) {
                // 窗口内 0 的数量超限，移动左边界直到重新合法。
                if (nums[left] == 0) {
                    --zeroCount;
                }
                ++left;
            }

            ans = max(ans, right - left + 1);
        }

        return ans;
    }

public:
    int longestOnes(vector<int>& nums, int k) {
        int n=nums.size();
        int cnt0 = 0;
        int ans = 0;
        for(int l=0, r=0; r<n; r++) {
            if(nums[r] == 0) cnt0++;
            while(cnt0 > k) {
                if(nums[l] == 0) cnt0--;
                l++;
            }

            ans = max(ans, r-l+1);
        }
        return ans;


    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,1,1,0,0,0,1,1,1,1,0]\n2\n
// @lcpr case=end

// @lcpr case=start
// [0,0,1,1,0,0,1,1,1,0,1,1,0,0,0,1,1,1,1]\n3\n
// @lcpr case=end

 */

