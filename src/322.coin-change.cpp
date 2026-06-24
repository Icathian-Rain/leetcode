/*
 * @lc app=leetcode.cn id=322 lang=cpp
 * @lcpr version=30204
 *
 * [322] 零钱兑换
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    int coinChangeOpt(vector<int>& coins, int amount) {
        const int impossible = amount + 1;
        vector<int> dp(amount + 1, impossible);
        dp[0] = 0;
        for (int coin : coins) {
            for (int value = coin; value <= amount; value++) {
                // coin 可以重复使用，所以容量从小到大更新。
                dp[value] = min(dp[value], dp[value - coin] + 1);
            }
        }
        return dp[amount] == impossible ? -1 : dp[amount];
    }

public:
    int coinChange(vector<int>& coins, int amount) {
        int MAX = amount + 1;
        int n=coins.size();
        vector<int> dp(amount+1, MAX);
        dp[0] = 0;
        for(int i=0; i<=amount; i++) {
            for(int j=0; j<coins.size(); j++) {
                if(coins[j] <= i) {
                    dp[i] = min(dp[i], dp[i-coins[j]] + 1);
                }
            }
        }
        return dp[amount] > amount ? -1 : dp[amount];



    }
};
// @lc code=end



/*
// @lcpr case=start
// [1, 2, 5]\n11\n
// @lcpr case=end

// @lcpr case=start
// [2]\n3\n
// @lcpr case=end

// @lcpr case=start
// [1]\n0\n
// @lcpr case=end

 */

