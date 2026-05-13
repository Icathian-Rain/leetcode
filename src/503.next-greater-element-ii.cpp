/*
 * @lc app=leetcode.cn id=503 lang=cpp
 * @lcpr version=30204
 *
 * [503] 下一个更大元素 II
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    vector<int> nextGreaterElementsOpt(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans(n, -1);
        vector<int> indexes;

        for(int i = 0; i < 2 * n; i++) {
            int index = i % n;
            while(!indexes.empty() && nums[indexes.back()] < nums[index]) {
                ans[indexes.back()] = nums[index];
                indexes.pop_back();
            }
            if(i < n) {
                // 每个下标只入栈一次，第二轮只用于帮助它们找到环形右侧答案。
                indexes.push_back(index);
            }
        }

        return ans;
    }

public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        int n=nums.size();
        vector<int> ans(n, 0);
        stack<int> st;
        for(int i=2*n-1; i>=0; i--) {
            int num=nums[i%n];
            while(!st.empty() && num >= st.top()) {
                st.pop();
            }
            if(st.empty()) {
                ans[i%n] = -1;
            } else {
                ans[i%n] = st.top();
            }
            st.push(num);
        }
        return ans;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,2,1]\n
// @lcpr case=end

// @lcpr case=start
// [1,2,3,4,3]\n
// @lcpr case=end

 */

