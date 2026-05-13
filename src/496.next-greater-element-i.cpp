/*
 * @lc app=leetcode.cn id=496 lang=cpp
 * @lcpr version=30204
 *
 * [496] 下一个更大元素 I
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    vector<int> nextGreaterElementOpt(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int, int> nextGreater;
        vector<int> decreasing;

        for(int value: nums2) {
            while(!decreasing.empty() && decreasing.back() < value) {
                // 当前 value 是这些等待元素遇到的第一个更大值。
                nextGreater[decreasing.back()] = value;
                decreasing.pop_back();
            }
            decreasing.push_back(value);
        }

        while(!decreasing.empty()) {
            nextGreater[decreasing.back()] = -1;
            decreasing.pop_back();
        }

        vector<int> ans;
        ans.reserve(nums1.size());
        for(int value: nums1) {
            ans.push_back(nextGreater[value]);
        }
        return ans;
    }

public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        int n1=nums1.size(), n2=nums2.size();
        unordered_map<int, int> mp;
        stack<int> st;

        for(int i=n2-1; i>=0; i--) {
            while(!st.empty() && st.top() < nums2[i]) {
                st.pop();
            }
            if(st.empty()) {
                mp[nums2[i]] = -1;
            } else {
                mp[nums2[i]] = st.top();
            }
            st.push(nums2[i]);
        }

        vector<int> ans(n1, 0);
        for(int i=0; i<n1; i++) {
            ans[i] = mp[nums1[i]];
        }
        return ans;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [4,1,2]\n[1,3,4,2].\n
// @lcpr case=end

// @lcpr case=start
// [2,4]\n[1,2,3,4].\n
// @lcpr case=end

 */

