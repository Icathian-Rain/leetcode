/*
 * @lc app=leetcode.cn id=217 lang=cpp
 * @lcpr version=30204
 *
 * [217] 存在重复元素
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        int n=nums.size();
        unordered_set<int> st;
        for(int i=0; i<n; i++) {
            if(st.find(nums[i]) != st.end()) {
                return true;
            }
            st.insert(nums[i]);
        }
        return false;


    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,2,3,1]\n
// @lcpr case=end

// @lcpr case=start
// [1,2,3,4]\n
// @lcpr case=end

// @lcpr case=start
// [1,1,1,3,3,4,3,2,4,2]\n
// @lcpr case=end

 */

