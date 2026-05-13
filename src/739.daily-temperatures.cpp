/*
 * @lc app=leetcode.cn id=739 lang=cpp
 * @lcpr version=30204
 *
 * [739] 每日温度
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    vector<int> dailyTemperaturesOpt(vector<int>& temperatures) {
        int n = temperatures.size();
        vector<int> ans(n, 0);
        vector<int> indexes;

        for(int i = 0; i < n; i++) {
            while(!indexes.empty() && temperatures[indexes.back()] < temperatures[i]) {
                int previous = indexes.back();
                indexes.pop_back();
                // 保存下标才能回填等待天数，而不只是知道更高温度是多少。
                ans[previous] = i - previous;
            }
            indexes.push_back(i);
        }

        return ans;
    }

public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n=temperatures.size();
        stack<int> st;
        vector<int> ans(n, 0);
        for(int i=n-1; i>=0; i--) {
            int tem = temperatures[i];
            while(!st.empty() && tem>=temperatures[st.top()]) {
                st.pop();
            }
            if(!st.empty()) {
                ans[i] = st.top() - i;
            }
            st.push(i);
        }
        return ans;


    }
};
// @lc code=end



/*
// @lcpr case=start
// [73,74,75,71,69,72,76,73]\n
// @lcpr case=end

// @lcpr case=start
// [30,40,50,60]\n
// @lcpr case=end

// @lcpr case=start
// [30,60,90]\n
// @lcpr case=end

 */

