/*
 * @lc app=leetcode.cn id=45 lang=cpp
 * @lcpr version=30204
 *
 * [45] 跳跃游戏 II
 */


// @lcpr-template-start
#include "../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    int jumpOpt(vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        int ans = 0;
        int farthest = 0; // 本层内能到达的最远下标
        int boundary = 0; // 当前层右端点：已用 ans 步恰好覆盖到这里
        // 扫到 n-2 即可：站在最后一个下标时不需要再跳
        for (int i = 0; i < n - 1; i++) {
            farthest = max(farthest, i + nums[i]);
            if (i == boundary) {        // 本层候选收集完，结算一步
                ans++;
                boundary = farthest;
                if (boundary >= n - 1) break; // 已能到达终点，无需继续
            }
        }
        return ans;
    }

public:
    int jump(vector<int>& nums) {
        int n=nums.size();
        int l=0, r=0;
        int end = 0;
        int ans = 0;
        for(l=0; l<n-1 && l<=r; l++) {
            r = max(r, l+nums[l]);
            if(l == end) {
                end = r;
                ans++;
            }
        }
        return ans;
        
    }
};
// @lc code=end



/*
// @lcpr case=start
// [2,3,1,1,4]\n
// @lcpr case=end

// @lcpr case=start
// [2,3,0,1,4]\n
// @lcpr case=end

 */

