/*
 * @lc app=leetcode.cn id=3 lang=cpp
 * @lcpr version=30204
 *
 * [3] 无重复字符的最长子串
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    int lengthOfLongestSubstringOpt(string s) {
        vector<int> lastSeen(256, -1);
        int left = 0;
        int ans = 0;

        for (int right = 0; right < (int)s.size(); ++right) {
            unsigned char ch = static_cast<unsigned char>(s[right]);
            if (lastSeen[ch] >= left) {
                // 重复字符落在当前窗口内，左边界直接跳到上次位置之后。
                left = lastSeen[ch] + 1;
            }
            lastSeen[ch] = right;
            ans = max(ans, right - left + 1);
        }

        return ans;
    }

public:
    int lengthOfLongestSubstring(string s) {
        int n=s.length();
        vector<int> cnt(128, 0);
        int ans=0;
        for(int l=0, r=0; r<n; r++) {
            cnt[s[r]]++;
            while(cnt[s[r]] > 1) {
                cnt[s[l]]--;
                l++;
            }
            ans=max(ans, r-l+1);
        }
        return ans;


    }
};
// @lc code=end



/*
// @lcpr case=start
// "abcabcbb"\n
// @lcpr case=end

// @lcpr case=start
// "bbbbb"\n
// @lcpr case=end

// @lcpr case=start
// "pwwkew"\n
// @lcpr case=end

 */

