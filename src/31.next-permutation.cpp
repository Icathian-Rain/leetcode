/*
 * @lc app=leetcode.cn id=31 lang=cpp
 * @lcpr version=30204
 *
 * [31] 下一个排列
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    void nextPermutationOpt(vector<int>& nums) {
        int pivot = static_cast<int>(nums.size()) - 2;
        while (pivot >= 0 && nums[pivot] >= nums[pivot + 1]) {
            --pivot;
        }

        if (pivot >= 0) {
            int successor = static_cast<int>(nums.size()) - 1;
            while (nums[successor] <= nums[pivot]) {
                --successor;
            }
            swap(nums[pivot], nums[successor]);
        }

        // pivot 右侧原本是降序，翻转后得到最小后缀。
        reverse(nums.begin() + pivot + 1, nums.end());
    }

public:
    void nextPermutation(vector<int>& nums) {
        int n=nums.size();
        int i=n-2;
        while(i>=0 && nums[i] >= nums[i+1]) {
            i--;
        }
        if(i >= 0) {
            int j=n-1;
            while(j >= 0 && nums[j] <= nums[i]) {
                j--;
            }
            swap(nums[i], nums[j]);
        }
        reverse(nums.begin()+i+1, nums.end());


    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,2,3]\n
// @lcpr case=end

// @lcpr case=start
// [3,2,1]\n
// @lcpr case=end

// @lcpr case=start
// [1,1,5]\n
// @lcpr case=end

 */

