/*
 * @lc app=leetcode.cn id=55 lang=cpp
 * @lcpr version=30204
 *
 * [55] 跳跃游戏
 */


// @lcpr-template-start
#include "../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    bool canJumpOpt(vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        // farthest：目前能到达的最远下标；可达性单调，无需回退
        int farthest = 0;
        for (int i = 0; i < n; i++) {
            // i 超出可达边界：从这里开始全部不可达
            if (i > farthest) return false;
            farthest = max(farthest, i + nums[i]);
        }
        return true;
    }

public:
    bool canJump(vector<int>& nums) {
        int n=nums.size();
        int l=0, r=0;
        for(l=0; l<n && l<=r; l++) {
            r = max(r, l+nums[l]);
        }
        return l == n;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [2,3,1,1,4]\n
// @lcpr case=end

// @lcpr case=start
// [3,2,1,0,4]\n
// @lcpr case=end

 */

