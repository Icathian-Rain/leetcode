/*
 * @lc app=leetcode.cn id=844 lang=cpp
 * @lcpr version=30204
 *
 * [844] 比较含退格的字符串
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    int nextValidIndex(const string& text, int index) {
        int skip = 0;
        while(index >= 0) {
            if(text[index] == '#') {
                skip++;
            } else if(skip > 0) {
                skip--;
            } else {
                break;
            }
            index--;
        }
        return index;
    }

    bool backspaceCompareOpt(string s, string t) {
        int left = (int)s.size() - 1;
        int right = (int)t.size() - 1;

        while(left >= 0 || right >= 0) {
            left = nextValidIndex(s, left);
            right = nextValidIndex(t, right);

            if(left < 0 || right < 0) {
                return left == right;
            }
            if(s[left] != t[right]) {
                return false;
            }

            left--;
            right--;
        }

        return true;
    }

public:
    bool backspaceCompare(string s, string t) {
        int fast=0, slow=0;
        int len1=s.length();
        for(;fast<len1; fast++) {
            if(s[fast] == '#') {
                if(slow > 0) {
                    slow--;
                }
            } else {
                s[slow] = s[fast];
                slow++;
            }
        }
        int slen = slow;
        
        fast=0, slow=0;
        int len2=t.length();
        for(;fast<len2; fast++) {
            if(t[fast] == '#') {
                if(slow > 0) {
                    slow--;
                }
            } else {
                t[slow] = t[fast];
                slow++;
            }
        }
        int tlen=slow;

        if(slen != tlen) return false;
        for(int i=0; i<slen; i++) {
            if(s[i] != t[i]) {
                return false;
            }
        }
        return true;
    }
};
// @lc code=end



/*
// @lcpr case=start
// "ab#c"\n"ad#c"\n
// @lcpr case=end

// @lcpr case=start
// "ab##"\n"c#d#"\n
// @lcpr case=end

// @lcpr case=start
// "a#c"\n"b"\n
// @lcpr case=end

 */

