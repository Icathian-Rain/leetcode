/*
 * @lc app=leetcode.cn id=41 lang=cpp
 * @lcpr version=30204
 *
 * [41] 缺失的第一个正数
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int n=nums.size();
        unordered_set<int> st;
        for(int i=0; i<n; i++) {
            st.insert(nums[i]);
        }
        for(int i=1; i<=n+1; i++) {
            if(st.find(i) == st.end()) {
                return i;
            }
        }
        return n+1;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,2,0]\n
// @lcpr case=end

// @lcpr case=start
// [3,4,-1,1]\n
// @lcpr case=end

// @lcpr case=start
// [7,8,9,11,12]\n
// @lcpr case=end

 */

