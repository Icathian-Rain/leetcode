/*
 * @lc app=leetcode.cn id=169 lang=cpp
 * @lcpr version=30204
 *
 * [169] 多数元素
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    // 哈希表，时间复杂度O(n),空间复杂度非O(1)
    int s1(vector<int>& nums) {
        int n=nums.size();
        unordered_map<int, int>cnt;
        for(int i=0; i<n; i++) {
            cnt[nums[i]]++;
            if(cnt[nums[i]] > n/2) {
                return nums[i];
            }
        }
        return -1;
    }

    // 时间复杂度O(n),空间复杂度非O(1) 题解

public:
    int majorityElement(vector<int>& nums) {
        return s1(nums);
    }
};
// @lc code=end



/*
// @lcpr case=start
// [3,2,3]\n
// @lcpr case=end

// @lcpr case=start
// [2,2,1,1,1,2,2]\n
// @lcpr case=end

 */

