/*
 * @lc app=leetcode.cn id=790 lang=cpp
 * @lcpr version=30204
 *
 * [790] 多米诺和托米诺平铺
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
const int MOD=1e9+7;
using ll = long long;
class Solution {
    int numTilingsOpt(int n) {
        long long empty = 1;
        long long topMissing = 0;
        long long bottomMissing = 0;
        long long full = 0;
        for (int col = 1; col <= n; col++) {
            // 四个状态分别表示当前列轮廓：空、上缺、下缺、已铺满。
            long long nextEmpty = full;
            long long nextTopMissing = (empty + bottomMissing) % MOD;
            long long nextBottomMissing = (empty + topMissing) % MOD;
            long long nextFull = (empty + topMissing + bottomMissing + full) % MOD;
            empty = nextEmpty;
            topMissing = nextTopMissing;
            bottomMissing = nextBottomMissing;
            full = nextFull;
        }
        return static_cast<int>(full);
    }

public:
    int numTilings(int n) {
        vector<ll> dp(4, 0);
        dp[0]=0;
        dp[1]=0;
        dp[2]=0;
        dp[3]=1;
        for(int i=1; i<=n; i++) {
            vector<ll> tmp(4, 0);
            tmp[0] = dp[3];
            tmp[1] = (dp[0] + dp[2]) % MOD;
            tmp[2] = (dp[0] + dp[1]) % MOD;
            tmp[3] = (dp[0] + dp[1] + dp[2] + dp[3]) % MOD;
            dp.swap(tmp);
        }
        return dp[3];
    }
};
// @lc code=end



/*
// @lcpr case=start
// 3\n
// @lcpr case=end

// @lcpr case=start
// 1\n
// @lcpr case=end

 */

