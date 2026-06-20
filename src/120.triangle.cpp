/*
 * @lc app=leetcode.cn id=120 lang=cpp
 * @lcpr version=30204
 *
 * [120] 三角形最小路径和
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    int minimumTotalOpt(vector<vector<int>>& triangle) {
        vector<int> dp = triangle.back();
        for (int row = static_cast<int>(triangle.size()) - 2; row >= 0; row--) {
            for (int col = 0; col <= row; col++) {
                // 从下一层相邻两个位置中选择更小的后续路径。
                dp[col] = min(dp[col], dp[col + 1]) + triangle[row][col];
            }
        }
        return dp[0];
    }

public:
    int s1(vector<vector<int>>& triangle) {
        int n=triangle.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));
        dp[0][0] = triangle[0][0];
        for(int i=1; i<n; i++) {
            for(int j=0; j<=i; j++) {
                if(j == 0) {
                    dp[i][j] = dp[i-1][j] + triangle[i][j];
                } else if(j == i) {
                    dp[i][j] = dp[i-1][j-1] + triangle[i][j];
                } else {
                    dp[i][j] = min(dp[i-1][j], dp[i-1][j-1]) + triangle[i][j];
                }
            }
        }
        int ans=INT_MAX;
        for(int j=0; j<n; j++) {
            ans = min(ans, dp[n-1][j]);
        }
        return ans;
    }

    int s2(vector<vector<int>>& triangle) {
        int n=triangle.size();
        vector<int> dp(n, 0);
        dp[0] = triangle[0][0];
        for(int i=1; i<n; i++) {
            vector<int> nxt(n, 0);
            for(int j=0; j<=i; j++) {
                if(j == 0) {
                    nxt[j] = dp[j] + triangle[i][j];
                } else if(j == i) {
                    nxt[j] = dp[j-1] + triangle[i][j];
                } else {
                    nxt[j] = min(dp[j], dp[j-1]) + triangle[i][j];
                }
            }
            dp = nxt;
        }
        int ans=INT_MAX;
        for(int j=0; j<n; j++) {
            ans = min(ans, dp[j]);
        }
        return ans;
    }

    int minimumTotal(vector<vector<int>>& triangle) {
        // return s1(triangle);
        return s2(triangle);
    }
};
// @lc code=end



/*
// @lcpr case=start
// [[2],[3,4],[6,5,7],[4,1,8,3]]\n
// @lcpr case=end

// @lcpr case=start
// [[-10]]\n
// @lcpr case=end

 */

