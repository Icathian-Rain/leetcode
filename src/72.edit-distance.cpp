/*
 * @lc app=leetcode.cn id=72 lang=cpp
 * @lcpr version=30204
 *
 * [72] 编辑距离
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    int minDistanceOpt(string word1, string word2) {
        int rows = static_cast<int>(word1.size());
        int cols = static_cast<int>(word2.size());
        vector<int> dp(cols + 1, 0);
        for (int j = 0; j <= cols; j++) dp[j] = j;

        for (int i = 1; i <= rows; i++) {
            int diagonal = dp[0];
            dp[0] = i;
            for (int j = 1; j <= cols; j++) {
                int up = dp[j];
                if (word1[i - 1] == word2[j - 1]) {
                    dp[j] = diagonal;
                } else {
                    // 删除、插入、替换分别来自上方、左方、左上方。
                    dp[j] = min({up, dp[j - 1], diagonal}) + 1;
                }
                diagonal = up;
            }
        }
        return dp[cols];
    }

public:
    int minDistance(string word1, string word2) {
        int m=word1.size(), n=word2.size();
        vector<vector<int>> dp(m+1, vector<int>(n+1, 0));
        for(int i=0; i<=m; i++) dp[i][0] = i;
        for(int j=0; j<=n; j++) dp[0][j] = j;
        for(int i=1; i<=m; i++) {
            for(int j=1; j<=n; j++) {
                if(word1[i-1] == word2[j-1]) {
                    dp[i][j] = dp[i-1][j-1];
                } else {
                    dp[i][j] = min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]})+1;
                }
            }
        }
        return dp[m][n];
    }
};
// @lc code=end



/*
// @lcpr case=start
// "horse"\n"ros"\n
// @lcpr case=end

// @lcpr case=start
// "intention"\n"execution"\n
// @lcpr case=end

 */

