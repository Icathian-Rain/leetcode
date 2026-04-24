/*
 * @lc app=leetcode.cn id=242 lang=cpp
 * @lcpr version=30204
 *
 * [242] 有效的字母异位词
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
public:
    bool isAnagram(string s, string t) {
        vector<int> cnt(26, 0);
        for(auto ch: s) {
            cnt[ch-'a']++;
        }

        for(auto ch: t) {
            cnt[ch-'a']--;
        }

        for(int i=0; i<26; i++) {
            if(cnt[i] != 0) return false;
        }
        return true;
    }
};
// @lc code=end



/*
// @lcpr case=start
// "anagram"\n"nagaram"\n
// @lcpr case=end

// @lcpr case=start
// "rat"\n"car"\n
// @lcpr case=end

 */

