/*
 * @lc app=leetcode.cn id=34 lang=cpp
 * @lcpr version=30204
 *
 * [34] 在排序数组中查找元素的第一个和最后一个位置
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    vector<int> s1(vector<int>& nums, int target) {
        int n=nums.size();
        int l=0, r=n;
        // 寻找第一个大于等于target的位置
        while(l<r) {
            int m=l+(r-l)/2;
            if(nums[m] >= target) {
                r=m;
            } else {
                l=m+1;
            }
        }

        if(l == n|| nums[l] != target) {
            return {-1, -1};
        }
        int ansL = l;

        l=0, r=n;
        while(l<r) {
            int m=l+(r-l)/2;
            if(nums[m] > target) {
                r=m;
            } else {
                l=m+1;
            }
        }

        int ansR = l-1;
        return {ansL, ansR};
    }

    vector<int> s2(vector<int>& nums, int target) {
        int n=nums.size();
        int ansL=lower_bound(nums.begin(), nums.end(), target)-nums.begin();
        if(ansL == n || nums[ansL]!=target) {
            return {-1, -1};
        }
        int ansR = upper_bound(nums.begin(), nums.end(), target)-nums.begin()-1;
        return {ansL, ansR};
    }

    vector<int> searchRangeOpt(vector<int>& nums, int target) {
        auto first = lower_bound(nums.begin(), nums.end(), target);
        if (first == nums.end() || *first != target) {
            return {-1, -1};
        }

        // upper_bound 指向第一个大于 target 的位置，左移一格就是最后一次出现。
        auto afterLast = upper_bound(nums.begin(), nums.end(), target);
        return {
            static_cast<int>(first - nums.begin()),
            static_cast<int>(afterLast - nums.begin() - 1)
        };
    }
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        // return s1(nums, target);
        return s2(nums, target);
    }
};
// @lc code=end



/*
// @lcpr case=start
// [5,7,7,8,8,10]\n8\n
// @lcpr case=end

// @lcpr case=start
// [5,7,7,8,8,10]\n6\n
// @lcpr case=end

// @lcpr case=start
// []\n0\n
// @lcpr case=end

 */

