/*
 * @lc app=leetcode.cn id=42 lang=cpp
 * @lcpr version=30204
 *
 * [42] 接雨水
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    int trapOpt(vector<int>& height) {
        int left = 0;
        int right = (int)height.size() - 1;
        int leftMax = 0;
        int rightMax = 0;
        int ans = 0;

        while(left < right) {
            if(height[left] < height[right]) {
                leftMax = max(leftMax, height[left]);
                // 右侧已有更高边界，左侧当前位置的水量只由 leftMax 决定。
                ans += leftMax - height[left];
                left++;
            } else {
                rightMax = max(rightMax, height[right]);
                // 左侧已有不低于右侧的边界，右侧当前位置的水量只由 rightMax 决定。
                ans += rightMax - height[right];
                right--;
            }
        }

        return ans;
    }

public:
    int trap(vector<int>& height) {
        int n=height.size();
        vector<int> lm(n, 0);
        lm[0]=height[0];
        for(int i=1; i<n; i++) {
            lm[i] = max(lm[i-1], height[i]);
        }

        vector<int> rm(n, 0);
        rm[n-1]=height[n-1];
        for(int i=n-2; i>=0; i--) {
            rm[i] = max(rm[i+1], height[i]);
        }

        int ans=0;
        for(int i=0; i<n; i++) {
            ans+=min(lm[i], rm[i])-height[i];
        }
        return ans;



    }
};
// @lc code=end



/*
// @lcpr case=start
// [0,1,0,2,1,0,1,3,2,1,2,1]\n
// @lcpr case=end

// @lcpr case=start
// [4,2,0,3,2,5]\n
// @lcpr case=end

 */

