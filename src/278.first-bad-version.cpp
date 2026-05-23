/*
 * @lc app=leetcode.cn id=278 lang=cpp
 * @lcpr version=30204
 *
 * [278] 第一个错误的版本
 */


// @lcpr-template-start
#include"../header.h"
bool isBadVersion(int version);
// @lcpr-template-end
// @lc code=start
// The API isBadVersion is defined for you.

using ll=long long;
class Solution {
    int firstBadVersionOpt(int n) {
        int left = 1;
        int right = n;

        while (left < right) {
            int middle = left + (right - left) / 2;
            if (isBadVersion(middle)) {
                right = middle; // middle 可能就是第一个错误版本，必须保留。
            } else {
                left = middle + 1; // middle 及其左侧都不是错误版本。
            }
        }

        return left;
    }

public:
    int firstBadVersion(int n) {
        ll l=1, r=n;
        while(l<r) {
            int m=l+(r-l)/2;
            if(isBadVersion(m)) {
                r=m;
            } else {
                l=m+1;
            }
        }
        return l;
    }
};
// @lc code=end



/*
// @lcpr case=start
// 5\n4\n
// @lcpr case=end

// @lcpr case=start
// 1\n1\n
// @lcpr case=end


// @lcpr case=start
// 2147483647\n2147483647
// @lcpr case=end
 */

