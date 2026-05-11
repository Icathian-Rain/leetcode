/*
 * @lc app=leetcode.cn id=32 lang=cpp
 * @lcpr version=30204
 *
 * [32] 最长有效括号
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    int longestValidParenthesesOpt(string s) {
        stack<int> indexes;
        indexes.push(-1);
        int ans = 0;

        for(int i = 0; i < (int)s.size(); i++) {
            if(s[i] == '(') {
                indexes.push(i);
            } else {
                indexes.pop();
                if(indexes.empty()) {
                    // 当前右括号无法匹配，成为下一段合法区间的左边界。
                    indexes.push(i);
                } else {
                    ans = max(ans, i - indexes.top());
                }
            }
        }

        return ans;
    }

public:
    int longestValidParentheses(string s) {
        int n=s.length();
        stack<int> st;
        int ans=0;
        st.push(-1);
        for(int i=0; i<n; i++) {
            if(s[i] == '(') {
                st.push(i);
            } else {
                st.pop();
                if(st.empty()) {
                    st.push(i);
                } else {
                    ans = max(ans, i-st.top());
                }
            }
        }
        return ans;

    }
};
// @lc code=end



/*
// @lcpr case=start
// "(()"\n
// @lcpr case=end

// @lcpr case=start
// ")()())"\n
// @lcpr case=end

// @lcpr case=start
// ""\n
// @lcpr case=end

 */

