/*
 * @lc app=leetcode.cn id=704 lang=cpp
 * @lcpr version=30204
 *
 * [704] 二分查找
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    int searchOpt(vector<int>& nums, int target) {
        int left = 0;
        int right = static_cast<int>(nums.size()) - 1;

        while (left <= right) {
            int middle = left + (right - left) / 2;
            if (nums[middle] == target) {
                return middle;
            }
            if (nums[middle] < target) {
                left = middle + 1;
            } else {
                right = middle - 1;
            }
        }

        return -1; // 闭区间被排空，说明目标不存在。
    }

public:
    int s1(vector<int>& nums, int target) {
        int n=nums.size();
        int l=0, r=n;
        while(l<r) {
            int m=l+(r-l)/2;
            if(nums[m] == target) {
                return m;
            } else if(nums[m] < target) {
                l = m+1;
            } else {
                r = m;
            }
        }
        return -1;
    }

    int s2(vector<int>& nums, int target) {
        int n=nums.size();
        int m = lower_bound(nums.begin(), nums.end(), target) - nums.begin();
        if(m == n || nums[m] != target) {
            return -1;
        }
        return m;
    }

    int search(vector<int>& nums, int target) {
        // return s1(nums, target);
        return s2(nums, target);

    }
};
// @lc code=end



/*
// @lcpr case=start
// [-1,0,3,5,9,12]\n9\n
// @lcpr case=end

// @lcpr case=start
// [-1,0,3,5,9,12]\n2\n
// @lcpr case=end

 */
