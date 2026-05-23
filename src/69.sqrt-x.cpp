/*
 * @lc app=leetcode.cn id=69 lang=cpp
 * @lcpr version=30204
 *
 * [69] x 的平方根 
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
using ll = long long;
class Solution {
    int mySqrtOpt(int x) {
        int left = 0;
        int right = x;
        int ans = 0;

        while (left <= right) {
            int middle = left + (right - left) / 2;
            if (1LL * middle * middle <= x) {
                ans = middle; // middle 可行，继续尝试更大的整数平方根。
                left = middle + 1;
            } else {
                right = middle - 1;
            }
        }

        return ans;
    }

public:
    int mySqrt(int x) {
        // if(x == 0) return 0;
        ll l=0, r=1LL*x+1;
        while(l<r) {
            // 寻找最后一个小于等于 sqrt(x)的数
            // 第一个大于sqrt(x) 位置减一
            ll m=l+(r-l)/2;
            if(1LL*m*m > 1LL*x) {
                r=m;
            } else {
                l=m+1;
            }
        }
        return l-1;
    }
};
// @lc code=end



/*
// @lcpr case=start
// 4\n
// @lcpr case=end

// @lcpr case=start
// 8\n
// @lcpr case=end


// @lcpr case=start
// 2147483647\n
// @lcpr case=end
 */

