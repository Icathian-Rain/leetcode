/*
 * @lc app=leetcode.cn id=76 lang=cpp
 * @lcpr version=30204
 *
 * [76] 最小覆盖子串
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    string minWindowOpt(string s, string t) {
        vector<int> diff(256, 0);
        int missingTypes = 0;

        auto addDiff = [&](unsigned char ch, int delta) {
            int before = diff[ch];
            int after = before + delta;
            if (before == 0 && after > 0) {
                ++missingTypes;
            } else if (before > 0 && after == 0) {
                --missingTypes;
            }
            diff[ch] = after;
        };

        for (unsigned char ch : t) {
            addDiff(ch, 1);
        }

        int bestLen = (int)s.size() + 1;
        int bestLeft = -1;
        int left = 0;

        for (int right = 0; right < (int)s.size(); ++right) {
            addDiff((unsigned char)s[right], -1);

            while (missingTypes == 0) {
                // 当前窗口已覆盖 t，先记录答案，再尝试移出左端缩短窗口。
                if (right - left + 1 < bestLen) {
                    bestLen = right - left + 1;
                    bestLeft = left;
                }
                addDiff((unsigned char)s[left], 1);
                ++left;
            }
        }

        return bestLeft == -1 ? "" : s.substr(bestLeft, bestLen);
    }

public:
    string minWindow(string s, string t) {
        int m=s.length(), n=t.length();
        vector<int> diff(256, 0);
        int different = 0;
        auto addDiff = [&](int idx, int delta) {
            int before = diff[idx];
            diff[idx] = diff[idx] + delta;
            int after = diff[idx];
            if(before == 0 && after > 0) {
                different++;
            } else if(before > 0 && after == 0) {
                different--;
            }
        };

        for(auto ch: t) {
            addDiff(ch, 1);
        }

        int len=m+1;
        int ansL=-1;


        for(int l=0, r=0; r<m; r++) {
            addDiff(s[r], -1);
            while(different == 0) {
                if(r-l+1 < len) {
                    len = r-l+1;
                    ansL = l;
                }
                addDiff(s[l], 1);
                l++;
            }
        }
        if(ansL == -1) return "";
        return s.substr(ansL, len);
    }
};
// @lc code=end



/*
// @lcpr case=start
// "ADOBECODEBANC"\n"ABC"\n
// @lcpr case=end

// @lcpr case=start
// "a"\n"a"\n
// @lcpr case=end

// @lcpr case=start
// "a"\n"aa"\n
// @lcpr case=end

 */

