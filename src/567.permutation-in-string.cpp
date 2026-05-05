/*
 * @lc app=leetcode.cn id=567 lang=cpp
 * @lcpr version=30204
 *
 * [567] 字符串的排列
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    bool checkInclusionOpt(string s1, string s2) {
        if (s1.size() > s2.size()) {
            return false;
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

        for (char ch : s1) {
            addDiff(ch - 'a', 1);
        }

        int windowSize = s1.size();
        for (int right = 0; right < (int)s2.size(); ++right) {
            addDiff(s2[right] - 'a', -1);
            if (right >= windowSize) {
                // 始终只保留和 s1 等长的窗口。
                addDiff(s2[right - windowSize] - 'a', 1);
            }
            if (right + 1 >= windowSize && different == 0) {
                return true;
            }
        }

        return false;
    }

public:
    bool checkInclusion(string s1, string s2) {
        int n=s1.length(), m=s2.length();
        vector<int> cnt(26, 0);
        int num=0;
        for(auto ch: s1) {
            if(cnt[ch-'a'] == 0) {
                num++;
            }
            cnt[ch-'a']++;
        }

        for(int l=0, r=0; r<m; r++) {
            cnt[s2[r]-'a']--;
            if(cnt[s2[r]-'a'] == 0) {
                num--;
            } else if(cnt[s2[r]-'a'] == -1) {
                num++;
            }

            if(r+1 < n) continue;

            // cout << l << " : " << num << endl;
            if(num == 0) return true;

            cnt[s2[l]-'a']++;
            if(cnt[s2[l]-'a'] == 0) {
                num--;
            } else if(cnt[s2[l]-'a'] == 1) {
                num++;
            }
            l++;
        }
        return false;



    }
};
// @lc code=end



/*
// @lcpr case=start
// "eidbaooo"\n
// @lcpr case=end

// @lcpr case=start
// "eidboaoo"\n
// @lcpr case=end

 */

