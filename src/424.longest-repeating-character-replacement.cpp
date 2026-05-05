/*
 * @lc app=leetcode.cn id=424 lang=cpp
 * @lcpr version=30204
 *
 * [424] 替换后的最长重复字符
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    int characterReplacementOpt(string s, int k) {
        vector<int> count(26, 0);
        int left = 0;
        int maxCount = 0;
        int ans = 0;

        for (int right = 0; right < (int)s.size(); ++right) {
            int idx = s[right] - 'A';
            ++count[idx];
            maxCount = max(maxCount, count[idx]);

            if (right - left + 1 - maxCount > k) {
                // 替换次数超限时右移左边界；maxCount 保持历史最大值即可。
                --count[s[left] - 'A'];
                ++left;
            }

            ans = max(ans, right - left + 1);
        }

        return ans;
    }

public:
    int characterReplacement(string s, int k) {
        int n=s.length();
        vector<int> cnt(26, 0);
        int maxCnt = 0;

        int ans=0;
        for(int l=0, r=0; r<n; r++) {
            cnt[s[r]-'A']++;
            maxCnt = max(maxCnt, cnt[s[r]-'A']);
            if(r-l+1-maxCnt > k) {
                cnt[s[l]-'A']--;
                l++;
            }
            ans = max(ans, r-l+1);
        }
        return ans;
    }
};
// @lc code=end



/*
// @lcpr case=start
// "ABAB"\n2\n
// @lcpr case=end

// @lcpr case=start
// "AABABBA"\n1\n
// @lcpr case=end

 */

