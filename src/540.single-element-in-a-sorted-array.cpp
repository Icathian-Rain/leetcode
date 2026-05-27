/*
 * @lc app=leetcode.cn id=540 lang=cpp
 * @lcpr version=30204
 *
 * [540] 有序数组中的单一元素
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    int singleNonDuplicateOpt(vector<int>& nums) {
        int left = 0;
        int right = static_cast<int>(nums.size()) - 1;

        while (left < right) {
            int middle = left + (right - left) / 2;
            if (middle % 2 == 1) {
                --middle; // 始终让 middle 指向一组候选配对的左端。
            }

            if (nums[middle] == nums[middle + 1]) {
                left = middle + 2; // 当前配对完整，单一元素在右侧。
            } else {
                right = middle; // 配对结构从 middle 开始被破坏，答案在左侧含 middle。
            }
        }

        return nums[left];
    }

public:
    int singleNonDuplicate(vector<int>& nums) {
        int n=nums.size();
        if(n == 1) return nums[0];
        int l=0, r=n;
        while(l<r) {
            int m=l+(r-l)/2;
            if(m%2==1) {
                if(nums[m] != nums[m-1]) {
                    r = m;
                } else {
                    l=m+1;
                }
            } else {
                if(nums[m] != nums[m+1]) {
                    r=m;
                } else {
                    l=m+1;
                }
            }
        }
        return nums[l];
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,1,2,3,3,4,4,8,8]\n
// @lcpr case=end

// @lcpr case=start
// [3,3,7,7,10,11,11]\n
// @lcpr case=end

 */

