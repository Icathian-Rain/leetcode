/*
 * @lc app=leetcode.cn id=921 lang=cpp
 * @lcpr version=30204
 *
 * [921] 使括号有效的最少添加
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    int minAddToMakeValidOpt(string s) {
        int missingLeft = 0;
        int unmatchedLeft = 0;

        for(char ch: s) {
            if(ch == '(') {
                unmatchedLeft++;
            } else if(unmatchedLeft > 0) {
                // 当前右括号优先匹配最近尚未闭合的左括号。
                unmatchedLeft--;
            } else {
                missingLeft++;
            }
        }

        return missingLeft + unmatchedLeft;
    }

public:
    int minAddToMakeValid(string s) {
        int ans=0;
        int left=0;
        for(auto ch: s) {
            if(ch == '(') {
                left++;
            } else {
                if(left > 0) {
                    left--;
                } else {
                    ans++;
                }
            }
        }
        return ans+left;
    }
};
// @lc code=end



/*
// @lcpr case=start
// "())"\n
// @lcpr case=end

// @lcpr case=start
// "((("\n
// @lcpr case=end

 */

