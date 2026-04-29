/*
 * @lc app=leetcode.cn id=383 lang=cpp
 * @lcpr version=30204
 *
 * [383] 赎金信
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
        if(ransomNote.size() > magazine.size()) return false;
        vector<int> cnt(26, 0);
        for(auto ch: magazine) {
            cnt[ch-'a']++;
        }
        for(auto ch: ransomNote) {
            cnt[ch-'a']--;
        }
        for(int i=0; i<26; i++) {
            if(cnt[i] < 0) return false;
        }
        return true;
    }
};
// @lc code=end



/*
// @lcpr case=start
// "a"\n"b"\n
// @lcpr case=end

// @lcpr case=start
// "aa"\n"ab"\n
// @lcpr case=end

// @lcpr case=start
// "aa"\n"aab"\n
// @lcpr case=end

 */

