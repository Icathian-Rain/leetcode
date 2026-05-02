/*
 * @lc app=leetcode.cn id=80 lang=cpp
 * @lcpr version=30204
 *
 * [80] 删除有序数组中的重复项 II
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    int removeDuplicatesOpt(vector<int>& nums) {
        int write = 0;
        for (int num : nums) {
            if (write < 2 || num != nums[write - 2]) {
                nums[write] = num;
                ++write;
            }
        }

        return write;
    }
public:
    int removeDuplicates(vector<int>& nums) {
        int n=nums.size();
        if(n < 2) {
            return n;
        }
        int slow=2, fast=2;
        while(fast < n) {
            // 检测
            if((nums[slow-1] != nums[fast]) || (nums[slow-2] != nums[fast])) {
                nums[slow] = nums[fast];
                slow++;
            }
            fast++;
        }
        return slow;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,1,1,2,2,3]\n
// @lcpr case=end

// @lcpr case=start
// [0,0,1,1,1,1,2,3,3]\n
// @lcpr case=end

 */

