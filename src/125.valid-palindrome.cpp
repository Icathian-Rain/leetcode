/*
 * @lc app=leetcode.cn id=125 lang=cpp
 * @lcpr version=30204
 *
 * [125] 验证回文串
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    bool isNumber(char ch) {
        return ch >= '0' && ch <= '9';
    }
    bool isLetter(char ch) {
        return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
    }

    char lower(char ch) {
        if(ch >= 'A' && ch <= 'Z') {
            return ch-'A'+'a';
        } else {
            return ch;
        }
    }

    bool isValid(char ch) {
        return isNumber(ch) || isLetter(ch);
    }

public:
    bool isPalindrome(string s) {
        int n=s.length();
        for(int i=0, j=n-1; i<j; i++, j--) {
            while(i < j && !isValid(s[i])) {
                i++;
            }
            while(j > i && !isValid(s[j])) {
                j--;
            }
            if(lower(s[i]) != lower(s[j])) {
                return false;
            }
        }
        return true;
    }
};
// @lc code=end



/*
// @lcpr case=start
// "A man, a plan, a canal: Panama"\n
// @lcpr case=end

// @lcpr case=start
// "race a car"\n
// @lcpr case=end

// @lcpr case=start
// " "\n
// @lcpr case=end

 */

