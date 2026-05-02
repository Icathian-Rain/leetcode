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

        int left=0;
        int right=n-1;
        int ans = 0;

        while(left<right) {
            int width = right-left;
            int boundedHeight = min(height[left], height[right]);
            ans=max(ans, width*boundedHeight);
            if(height[left] < height[right]) {
                left++;
            } else {
                right--;
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

