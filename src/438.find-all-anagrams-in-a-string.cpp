/*
 * @lc app=leetcode.cn id=438 lang=cpp
 * @lcpr version=30204
 *
 * [438] 找到字符串中所有字母异位词
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    vector<int> findAnagramsOpt(string s, string p) {
        if (p.size() > s.size()) {
            return {};
        }

        vector<int> diff(26, 0);
        int different = 0;

        auto addDiff = [&](int idx, int delta) {
            int before = diff[idx];
            int after = before + delta;
            if (before == 0 && after != 0) {
                ++different;
            } else if (before != 0 && after == 0) {
                --different;
            }
            diff[idx] = after;
        };

        for (char ch : p) {
            addDiff(ch - 'a', 1);
        }

        vector<int> ans;
        int windowSize = p.size();
        for (int right = 0; right < (int)s.size(); ++right) {
            addDiff(s[right] - 'a', -1);
            if (right >= windowSize) {
                // 固定窗口超过 p 的长度时，移出最左侧字符。
                addDiff(s[right - windowSize] - 'a', 1);
            }
            if (right + 1 >= windowSize && different == 0) {
                ans.push_back(right - windowSize + 1);
            }
        }

        return ans;
    }

public:
    vector<int> findAnagrams(string s, string p) {
        int m=s.length(), n=p.length();
        vector<int> cnt(26, 0);
        int num=0;
        for(auto ch: p) {
            if(cnt[ch-'a'] == 0) {
                num++;
            }
            cnt[ch-'a']++;
        }

        vector<int> ans;
        for(int l=0, r=0; r<m; r++) {
            cnt[s[r]-'a']--;
            if(cnt[s[r]-'a'] == 0) {
                num--;
            } else if(cnt[s[r]-'a'] == -1) {
                num++;
            }
            if(r+1 < n) {
                continue;
            }
            // cout << l << ": " << num << endl;

            if(num == 0) {
                ans.push_back(l);
            }
            cnt[s[l]-'a']++;
            if(cnt[s[l]-'a'] == 0) {
                num--;
            } else if(cnt[s[l]-'a'] == 1) {
                num++;
            }
            l++;
        }
        return ans;
    }
};
// @lc code=end



/*
// @lcpr case=start
// "cbaebabacd"\n"abc"\n
// @lcpr case=end

// @lcpr case=start
// "abab"\n"ab"\n
// @lcpr case=end

 */

