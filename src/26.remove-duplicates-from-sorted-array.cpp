/*
 * @lc app=leetcode.cn id=26 lang=cpp
 * @lcpr version=30204
 *
 * [26] 删除有序数组中的重复项
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    int removeDuplicatesOpt(vector<int>& nums) {
        if (nums.empty()) {
            return 0;
        }

        int write = 1;
        for (int read = 1; read < static_cast<int>(nums.size()); ++read) {
            if (nums[read] != nums[write - 1]) {
                nums[write] = nums[read];
                ++write;
            }
        }

        return write;
    }

public:
    int removeDuplicates(vector<int>& nums) {
        int n=nums.size();

        int slow=1, fast=1;
        while(fast<n) {
            if(nums[slow-1] != nums[fast]) {
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
// [1,1,2]\n
// @lcpr case=end

// @lcpr case=start
// [0,0,1,1,1,2,2,3,3,4]\n
// @lcpr case=end

 */

