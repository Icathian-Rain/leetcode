/*
 * @lc app=leetcode.cn id=162 lang=cpp
 * @lcpr version=30204
 *
 * [162] 寻找峰值
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    int findPeakElementOpt(vector<int>& nums) {
        int left = 0;
        int right = static_cast<int>(nums.size()) - 1;

        while (left < right) {
            int middle = left + (right - left) / 2;
            if (nums[middle] > nums[middle + 1]) {
                right = middle; // 下降方向左侧一定存在峰值，middle 也要保留。
            } else {
                left = middle + 1; // 上升方向右侧一定存在峰值。
            }
        }

        return left;
    }

public:
    int findPeakElement(vector<int>& nums) {
        int n=nums.size();
        if(n == 1) return 0;

        auto check = [&](int m) {
            if(m == 0) {
                if(nums[m] > nums[m+1]) {
                    return 0;
                } else {
                    return -1;
                }
            } else if(m == n-1) {
                if(nums[m] > nums[m-1]) {
                    return 0;
                } else {
                    return -1;
                }
            } else {
                if(nums[m] > nums[m-1] && nums[m] > nums[m+1]) {
                    return 0;
                } else if(nums[m] < nums[m+1]) {
                    return 1;
                } else {
                    return -1;
                }
            }
        };


        int l=0, r=n;
        while(l<r) {
            int m=l+(r-l)/2;
            int res = check(m);
            if(res == 0) {
                return m;
            } else if(res == -1) {
                r = m;
            } else {
                l = m+1;
            }
        }
        return 0;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,2,3,1]\n
// @lcpr case=end

// @lcpr case=start
// [1,2,1,3,5,6,4]\n
// @lcpr case=end

// @lcpr case=start
// [1]\n
// @lcpr case=end

 */

