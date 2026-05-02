/*
 * @lc app=leetcode.cn id=27 lang=cpp
 * @lcpr version=30204
 *
 * [27] 移除元素
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    int removeElementOpt(vector<int>& nums, int val) {
        int write = 0;
        for (int read = 0; read < static_cast<int>(nums.size()); ++read) {
            // [0, write) 始终是不等于 val 的有效前缀。
            if (nums[read] != val) {
                nums[write] = nums[read];
                ++write;
            }
        }

        return write;
    }

public:
    int removeElement(vector<int>& nums, int val) {
        int n=nums.size();
        
        int write=0;
        for(int read=0; read<n; read++) {
            if(nums[read] != val) {
                nums[write] = nums[read];
                write++;
            }
        }
        return write;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [3,2,2,3]\n3\n
// @lcpr case=end

// @lcpr case=start
// [0,1,2,2,3,0,4,2]\n2\n
// @lcpr case=end

 */

