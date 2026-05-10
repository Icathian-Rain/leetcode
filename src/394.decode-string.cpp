/*
 * @lc app=leetcode.cn id=394 lang=cpp
 * @lcpr version=30204
 *
 * [394] 字符串解码
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    string decodeStringOpt(string s) {
        stack<int> repeatStack;
        stack<string> prefixStack;
        string current;
        int repeat = 0;

        for(char ch: s) {
            if(isdigit(ch)) {
                repeat = repeat * 10 + (ch - '0');
            } else if(ch == '[') {
                repeatStack.push(repeat);
                prefixStack.push(current);
                repeat = 0;
                current.clear();
            } else if(ch == ']') {
                int times = repeatStack.top();
                repeatStack.pop();
                string prefix = prefixStack.top();
                prefixStack.pop();

                string expanded;
                while(times--) {
                    expanded += current;
                }
                // 闭合一层括号后，恢复外层前缀并接上当前层展开结果。
                current = prefix + expanded;
            } else {
                current.push_back(ch);
            }
        }

        return current;
    }

public:
    string getDigits(string& s, int& ptr) {
        string res = "";
        while(ptr < s.size() && isdigit(s[ptr])) {
            res.push_back(s[ptr]);
            ptr++;
        }
        return res;
    }

    string getString(vector<string>& v) {
        string res = "";
        for(auto str: v) {
            res += str;
        }
        return res;
    }

    string decodeString(string s) {
        int n=s.size();
        
        vector<string> stk;
        int ptr = 0;
        while(ptr < n) {
            char ch = s[ptr];
            if(isdigit(ch)) {
                // 如果是数字，则获取整个数字进栈
                string digits = getDigits(s, ptr);
                stk.push_back(digits);
            } else if(isalpha(ch) || ch == '[') {
                // 字母进栈
                stk.push_back(string(1, ch));
                ptr++;
            } else {
                ptr++;

                // 获取需要翻倍的字符组合
                vector<string> sub;
                while(stk.back() != "[") {
                    sub.push_back(stk.back());
                    stk.pop_back();
                }
                stk.pop_back();
                reverse(sub.begin(), sub.end());
                string tmp = getString(sub);

                int times = stoi(stk.back());
                stk.pop_back();

                string ans="";
                while(times--) ans+=tmp;
                stk.push_back(ans);
            }
        }

        return getString(stk);
    }
};
// @lc code=end



/*
// @lcpr case=start
// "3[a]2[bc]"\n
// @lcpr case=end

// @lcpr case=start
// "3[a2[c]]"\n
// @lcpr case=end

// @lcpr case=start
// "2[abc]3[cd]ef"\n
// @lcpr case=end

// @lcpr case=start
// "abc3[cd]xyz"\n
// @lcpr case=end

 */

