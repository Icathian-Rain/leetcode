/*
 * @lc app=leetcode.cn id=152 lang=cpp
 * @lcpr version=30204
 *
 * [152] 乘积最大子数组
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    int maxProductOpt(vector<int>& nums) {
        int maxEndingHere = nums[0];
        int minEndingHere = nums[0];
        int answer = nums[0];
        for (int i = 1; i < static_cast<int>(nums.size()); i++) {
            int num = nums[i];
            int prevMax = maxEndingHere;
            int prevMin = minEndingHere;
            // 负数会让最大和最小互换角色，所以两者都要维护。
            maxEndingHere = max({num, prevMax * num, prevMin * num});
            minEndingHere = min({num, prevMax * num, prevMin * num});
            answer = max(answer, maxEndingHere);
        }
        return answer;
    }

public:
    int maxProduct(vector<int>& nums) {
        int n=nums.size();
        int mx = nums[0], mn = nums[0], ans = nums[0];
        for(int i=1; i<n; i++) {
            int num = nums[i];
            int premx = mx, premn = mn;
            mx = max({premx*nums[i], nums[i], premn*nums[i]});
            mn = min({premx*nums[i], nums[i], premn*nums[i]});
            ans = max(mx, ans);
        }
        return ans;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [2,3,-2,4]\n
// @lcpr case=end

// @lcpr case=start
// [-2,0,-1]\n
// @lcpr case=end

 */

