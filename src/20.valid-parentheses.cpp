/*
 * @lc app=leetcode.cn id=20 lang=cpp
 * @lcpr version=30204
 *
 * [20] 有效的括号
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    char matchingOpening(char closing) {
        if(closing == ')') return '(';
        if(closing == ']') return '[';
        if(closing == '}') return '{';
        return '\0';
    }

    bool isValidOpt(string s) {
        stack<char> openings;
        for(char ch: s) {
            if(ch == '(' || ch == '[' || ch == '{') {
                openings.push(ch);
                continue;
            }

            char need = matchingOpening(ch);
            // 右括号必须匹配最近的未闭合左括号，其他字符直接判非法。
            if(need == '\0' || openings.empty() || openings.top() != need) {
                return false;
            }
            openings.pop();
        }

        return openings.empty();
    }

public:
    bool compare(char a, char b) {
        if((a == '(' && b == ')') || (a == '[' && b == ']') || (a == '{' && b == '}')) {
            return true;
        } else {
            return false;
        }
    }
    bool isValid(string s) {
        stack<char> st;
        for(auto ch: s) {
            if(ch == '(' || ch == '[' || ch == '{') {
                st.push(ch);
            } else if(ch == ')' || ch == ']' || ch == '}') {
                if(st.empty()) return false;
                if(compare(st.top(), ch) == false) return false;
                st.pop();
            } else {
                return false;
            }
        }
        if(!st.empty()) return false;
        return true;


    }
};
// @lc code=end



/*
// @lcpr case=start
// "()"\n
// @lcpr case=end

// @lcpr case=start
// "()[]{}"\n
// @lcpr case=end

// @lcpr case=start
// "(]"\n
// @lcpr case=end

// @lcpr case=start
// "([])"\n
// @lcpr case=end

// @lcpr case=start
// "([)]"\n
// @lcpr case=end

// @lcpr case=start
"["
// @lcpr case=end

 */

