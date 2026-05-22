/*
 * @lc app=leetcode.cn id=35 lang=cpp
 * @lcpr version=30204
 *
 * [35] 搜索插入位置
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    int searchInsertOpt(vector<int>& nums, int target) {
        int left = 0;
        int right = static_cast<int>(nums.size());

        while (left < right) {
            int middle = left + (right - left) / 2;
            if (nums[middle] < target) {
                left = middle + 1;
            } else {
                right = middle;
            }
        }

        return left; // 第一个大于等于 target 的位置，也是插入位置。
    }

public:
    int s1(vector<int>& nums, int target) {
        // 找到第一个大于等于target的位置
        int n=nums.size();
        int l=0, r=n;
        while(l<r) {
            int m=l+(r-l)/2;
            if(nums[m] < target) {
                l = m+1;
            } else {
                r = m;
            }
        }
        return l;
    }

    int s2(vector<int>& nums, int target) {
        return lower_bound(nums.begin(), nums.end(), target)-nums.begin();
    }
    int searchInsert(vector<int>& nums, int target) {
        // return s1(nums, target);
        return s2(nums, target);
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,3,5,6]\n5\n
// @lcpr case=end

// @lcpr case=start
// [1,3,5,6]\n2\n
// @lcpr case=end

// @lcpr case=start
// [1,3,5,6]\n7\n
// @lcpr case=end

 */
