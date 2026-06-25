/*
 * @lc app=leetcode.cn id=1143 lang=cpp
 * @lcpr version=30204
 *
 * [1143] 最长公共子序列
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    int longestCommonSubsequenceOpt(string text1, string text2) {
        int rows = static_cast<int>(text1.size());
        int cols = static_cast<int>(text2.size());
        vector<int> dp(cols + 1, 0);
        for (int i = 1; i <= rows; i++) {
            int diagonal = 0;
            for (int j = 1; j <= cols; j++) {
                int up = dp[j];
                if (text1[i - 1] == text2[j - 1]) {
                    dp[j] = diagonal + 1;
                } else {
                    dp[j] = max(dp[j], dp[j - 1]);
                }
                diagonal = up;
            }
        }
        return dp[cols];
    }

public:
    int longestCommonSubsequence(string text1, string text2) {
        int m=text1.length(), n=text2.length();
        vector<vector<int>> dp(m+1, vector<int>(n+1, 0));
        for(int i=1; i<=m; i++) {
            for(int j=1; j<=n; j++) {
                if(text1[i-1] == text2[j-1]) {
                    dp[i][j] = dp[i-1][j-1]+1;
                } else {
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
                }
            }
        }
        return dp[m][n];

    }
};
// @lc code=end



/*
// @lcpr case=start
// "abcde"\n"ace"\n
// @lcpr case=end

// @lcpr case=start
// "abc"\n"abc"\n
// @lcpr case=end

// @lcpr case=start
// "abc"\n"def"\n
// @lcpr case=end

 */

