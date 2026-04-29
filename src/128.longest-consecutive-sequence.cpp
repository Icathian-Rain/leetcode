/*
 * @lc app=leetcode.cn id=128 lang=cpp
 * @lcpr version=30204
 *
 * [128] 最长连续序列
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        int n=nums.size();
        if(n == 0) return 0;
        unordered_set<int> st;
        for(auto num: nums) {
            st.insert(num);
        }

        int ans=1;
        for(auto num: st) {
            if(st.find(num-1) != st.end()) {
                continue;
            }

            int len=1;
            int cur=num+1;
            while(st.find(cur) != st.end()) {
                len++;
                cur++;
            }
            ans=max(ans, len);
        }
        return ans;

    }
};
// @lc code=end



/*
// @lcpr case=start
// [100,4,200,1,3,2]\n
// @lcpr case=end

// @lcpr case=start
// [0,3,7,2,5,8,4,6,0,1]\n
// @lcpr case=end

// @lcpr case=start
// [1,0,1,2]\n
// @lcpr case=end

 */

