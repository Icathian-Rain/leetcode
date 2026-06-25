/*
 * @lc app=leetcode.cn id=91 lang=cpp
 * @lcpr version=30204
 *
 * [91] 解码方法
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    int numDecodingsOpt(string s) {
        int n = static_cast<int>(s.size());
        int twoBack = 1;
        int oneBack = s[0] == '0' ? 0 : 1;
        for (int i = 2; i <= n; i++) {
            int current = 0;
            if (s[i - 1] != '0') current += oneBack;
            int twoDigits = (s[i - 2] - '0') * 10 + (s[i - 1] - '0');
            // 两位数必须落在 10..26 才能作为一个字母。
            if (twoDigits >= 10 && twoDigits <= 26) current += twoBack;
            twoBack = oneBack;
            oneBack = current;
        }
        return oneBack;
    }

public:
    int numDecodings(string s) {
        int n=s.length();
        vector<int> dp(n+1, 0);
        dp[0] = 1;
        auto test = [&](int idx, int len) -> bool {
            if(idx < 0) return false;
            if(len == 1) {
                return s[idx] != '0';
            } else {
                return s[idx] == '1' || (s[idx] == '2' && s[idx+1] <= '6');
            }
        };

        for(int i=1; i<=n; i++) {
            if(test(i-1, 1)) dp[i] += dp[i-1];
            if(test(i-2, 2)) dp[i] += dp[i-2];
        }
        return dp[n];


    }
};
// @lc code=end



/*
// @lcpr case=start
// "12"\n
// @lcpr case=end

// @lcpr case=start
// "226"\n
// @lcpr case=end

// @lcpr case=start
// "06"\n
// @lcpr case=end

 */

