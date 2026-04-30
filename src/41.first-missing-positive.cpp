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
    int s1(vector<int>& nums) {
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

    int s2(vector<int>& nums) {
        int n=nums.size();
        for(int i=0; i<n; i++) {
            while(nums[i] >=1  && nums[i] <= n && nums[nums[i]-1] != nums[i]) {
                swap(nums[i], nums[nums[i]-1]);
            }
        }

        for(int i=0; i<n; i++) {
            if(nums[i] != i+1) {
                return i+1;
            }
        }
        return n+1;
    }

public:
    int firstMissingPositive(vector<int>& nums) {
        // return s1(nums);
        return s2(nums);
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

