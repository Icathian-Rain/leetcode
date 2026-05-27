/*
 * @lc app=leetcode.cn id=1283 lang=cpp
 * @lcpr version=30204
 *
 * [1283] 使结果不超过阈值的最小除数
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    int smallestDivisorOpt(vector<int>& nums, int threshold) {
        int left = 1;
        int right = *max_element(nums.begin(), nums.end());

        auto canUse = [&](int divisor) {
            int sum = 0;
            for (int value : nums) {
                sum += (value + divisor - 1) / divisor; // 整数上取整。
                if (sum > threshold) {
                    return false;
                }
            }
            return true;
        };

        while (left < right) {
            int middle = left + (right - left) / 2;
            if (canUse(middle)) {
                right = middle; // 除数可行，保留并继续找更小值。
            } else {
                left = middle + 1;
            }
        }

        return left;
    }

public:
    int smallestDivisor(vector<int>& nums, int threshold) {
        int n=nums.size();
        int mx=0;
        for(int i=0; i<n; i++) {
            mx=max(mx, nums[i]);
        }
        auto check=[&](int m) {
            int sum=0;
            for(int i=0; i<n; i++) {
                sum += ceil(1.0*nums[i]/m);
                if(sum > threshold) {
                    return false;
                }
            }
            return true;
        };

        int l=1, r=mx+1;
        while(l<r) {
            int m=l+(r-l)/2;
            if(check(m)) {
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
// [1,2,5,9]\n6\n
// @lcpr case=end

// @lcpr case=start
// [2,3,5,7,11]\n11\n
// @lcpr case=end

// @lcpr case=start
// [19]\n5\n
// @lcpr case=end

 */

