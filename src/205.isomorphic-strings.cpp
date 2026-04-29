/*
 * @lc app=leetcode.cn id=205 lang=cpp
 * @lcpr version=30204
 *
 * [205] 同构字符串
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
public:
    bool isIsomorphic(string s, string t) {
        int n=s.length();
        vector<int> s2t(128, -1), t2s(128, -1);
        for(int i=0; i<n; i++) {
            char ch1 = s[i], ch2=t[i];
            if(s2t[ch1] == -1 && t2s[ch2] == -1) {
                s2t[ch1] = ch2;
                t2s[ch2] = ch1;
            } else {
                if(s2t[ch1] != ch2 || t2s[ch2] != ch1) {
                    return false;
                }
            }
        }
        return true;
    }
};
// @lc code=end



/*
// @lcpr case=start
// "egg"\n"add"\n
// @lcpr case=end

// @lcpr case=start
// "f11"\n"b23"\n
// @lcpr case=end

// @lcpr case=start
// "paper"\n"title"\n
// @lcpr case=end

 */

