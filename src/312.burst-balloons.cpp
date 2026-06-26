/*
 * @lc app=leetcode.cn id=312 lang=cpp
 * @lcpr version=30204
 *
 * [312] 戳气球
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    int maxCoinsOpt(vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        vector<int> values(n + 2, 1);
        for (int i = 1; i <= n; i++) values[i] = nums[i - 1];

        vector<vector<int>> dp(n + 2, vector<int>(n + 2, 0));
        for (int len = 2; len <= n + 1; len++) {
            for (int left = 0; left + len <= n + 1; left++) {
                int right = left + len;
                for (int last = left + 1; last < right; last++) {
                    // last 是开区间 (left, right) 中最后被戳破的气球。
                    dp[left][right] = max(dp[left][right],
                        dp[left][last] + dp[last][right] + values[left] * values[last] * values[right]);
                }
            }
        }
        return dp[0][n + 1];
    }

public:
    int maxCoins(vector<int>& nums) {
        int n=nums.size();
        vector<int> val(n+2, 0);
        vector<vector<int>> mem(n+2, vector<int>(n+2, -1));

        for(int i=1; i<=n; i++) {
            val[i] = nums[i-1];
        }
        val[0] = val[n+1] = 1;

        function<int(int, int)> dfs = [&](int left, int right) -> int {
            if(left >= right-1) {
                return 0;
            }
            if(mem[left][right] != -1) {
                return mem[left][right];
            }
            for(int i=left+1; i<right; i++) {
                int sum=val[left]*val[i]*val[right];
                sum += dfs(left, i) + dfs(i, right);
                mem[left][right] = max(mem[left][right], sum);
            }
            return mem[left][right];
        };

        return dfs(0, n+1);


    }
};
// @lc code=end



/*
// @lcpr case=start
// [3,1,5,8]\n
// @lcpr case=end

// @lcpr case=start
// [1,5]\n
// @lcpr case=end

 */

