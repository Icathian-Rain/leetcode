/*
 * @lc app=leetcode.cn id=150 lang=cpp
 * @lcpr version=30204
 *
 * [150] 逆波兰表达式求值
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    int applyOperation(int left, int right, const string& op) {
        if(op == "+") return left + right;
        if(op == "-") return left - right;
        if(op == "*") return left * right;
        return left / right;
    }

    int evalRPNOpt(vector<string>& tokens) {
        vector<int> values;

        for(const string& token: tokens) {
            if(token.size() == 1 && (token == "+" || token == "-" || token == "*" || token == "/")) {
                int right = values.back();
                values.pop_back();
                int left = values.back();
                values.pop_back();
                // 注意操作数顺序：先弹出的是右操作数。
                values.push_back(applyOperation(left, right, token));
            } else {
                values.push_back(stoi(token));
            }
        }

        return values.back();
    }

public:
    int evalRPN(vector<string>& tokens) {
        stack<int> st;
        for(auto tok: tokens) {
            if(tok == "+") {
                int num1 = st.top();st.pop();
                int num2 = st.top();st.pop();
                st.push(num2+num1);
            } else if(tok == "-") {
                int num1 = st.top();st.pop();
                int num2 = st.top();st.pop();
                st.push(num2-num1);
            } else if(tok == "*") {
                int num1 = st.top();st.pop();
                int num2 = st.top();st.pop();
                st.push(num2*num1);
            } else if(tok == "/") {
                int num1 = st.top();st.pop();
                int num2 = st.top();st.pop();
                st.push(num2/num1);
            } else {
                int num = stoi(tok.c_str());
                st.push(num);
            }
        }
        int ans=st.top();st.pop();
        return ans;
    }
};
// @lc code=end



/*
// @lcpr case=start
// ["2","1","+","3","*"]\n
// @lcpr case=end

// @lcpr case=start
// ["4","13","5","/","+"]\n
// @lcpr case=end

// @lcpr case=start
// ["10","6","9","3","+","-11","*","/","*","17","+","5","+"]\n
// @lcpr case=end

 */

