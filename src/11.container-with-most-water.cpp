/*
 * @lc app=leetcode.cn id=11 lang=cpp
 * @lcpr version=30204
 *
 * [11] 盛最多水的容器
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
public:
    int maxArea(vector<int>& height) {
        int n=height.size();
        int ans = 0;
        for(int i=0, j=n-1; i<j; ) {
            ans = max(ans, min(height[i], height[j])*(j-i));
            if(height[i] < height[j]) {
                i++;
            } else {
                j--;
            }
        }
        return ans;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,8,6,2,5,4,8,3,7]\n
// @lcpr case=end

// @lcpr case=start
// [1,1]\n
// @lcpr case=end

 */

