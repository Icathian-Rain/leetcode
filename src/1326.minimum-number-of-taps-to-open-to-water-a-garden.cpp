/*
 * @lc app=leetcode.cn id=1326 lang=cpp
 * @lcpr version=30204
 *
 * [1326] 灌溉花园的最少水龙头数目
 */


// @lcpr-template-start
#include "../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    int minTapsOpt(int n, vector<int>& ranges) {
        // rightMost[i]：左端点为 i 的水龙头能覆盖到的最远右端点
        vector<int> rightMost(n + 1);
        iota(rightMost.begin(), rightMost.end(), 0);
        for (int i = 0; i <= n; i++) {
            int left = max(0, i - ranges[i]);   // 浇灌区间截断到 [0, n]
            int right = min(n, i + ranges[i]);
            rightMost[left] = max(rightMost[left], right);
        }
        int ans = 0;
        int far = 0;       // 本层候选能延伸的最远右端
        int boundary = 0; // 已选水龙头恰好连续覆盖到的边界
        for (int i = 0; i < n; i++) {
            far = max(far, rightMost[i]);
            if (far == i) return -1; // 出现覆盖不到的空隙
            if (i == boundary) {     // 当前层结算：需要新开一个水龙头
                ans++;
                boundary = far;
            }
        }
        return ans;
    }

public:
    int minTaps(int n, vector<int>& ranges) {
        vector<int> rightMost(n+1);
        iota(rightMost.begin(), rightMost.end(), 0);
        for(int i=0; i<=n; i++) {
            int left = max(0, i-ranges[i]);
            int right = min(n, i+ranges[i]);
            rightMost[left] = max(rightMost[left], right);
        }
        int l=0, r=0, ans=0, pre=0;
        for(l=0; l<n; l++) {
            r = max(r, rightMost[l]);
            if(l == r) return -1;
            if(l == pre) {
                ans++;
                pre = r;
            }
        }
        return ans;


    }
};
// @lc code=end



/*
// @lcpr case=start
// 5\n[3,4,1,1,0,0]\n
// @lcpr case=end

// @lcpr case=start
// 3\n[0,0,0,0]\n
// @lcpr case=end

 */

