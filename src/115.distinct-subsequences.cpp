/*
 * @lc app=leetcode.cn id=115 lang=cpp
 * @lcpr version=30204
 *
 * [115] 不同的子序列
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
using ull = unsigned long long;
class Solution {
    int numDistinctOpt(string s, string t) {
        int m = static_cast<int>(s.size());
        int n = static_cast<int>(t.size());
        vector<unsigned long long> dp(n + 1, 0);
        dp[0] = 1;
        for (int i = 1; i <= m; i++) {
            // 倒序避免同一个 s[i - 1] 在本轮被重复使用。
            for (int j = n; j >= 1; j--) {
                if (s[i - 1] == t[j - 1]) {
                    dp[j] += dp[j - 1];
                }
            }
        }
        return static_cast<int>(dp[n]);
    }

public:
    int numDistinct(string s, string t) {
        int m=s.length(), n=t.length();
        // if(m < n) return 0;
        vector<vector<ull>> dp(m+1, vector<ull>(n+1, 0));
        for(int i=0; i<=m; i++) {
            dp[i][n] = 1;
        }
        for(int i=m-1; i>=0; i--) {
            for(int j=n-1; j>=0; j--) {
                if(s[i] == t[j]) {
                    dp[i][j] = dp[i+1][j+1] + dp[i+1][j];
                } else {
                    dp[i][j] = dp[i+1][j];
                }
            }
        }
        return dp[0][0];
    }
};
// @lc code=end



/*
// @lcpr case=start
// "rabbbit"\n"rabbit"\n
// @lcpr case=end

// @lcpr case=start
// "babgbag"\n"bag"\n
// @lcpr case=end

 */

