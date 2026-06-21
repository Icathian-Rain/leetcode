/*
 * @lc app=leetcode.cn id=740 lang=cpp
 * @lcpr version=30204
 *
 * [740] 删除并获得点数
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    int deleteAndEarnOpt(vector<int>& nums) {
        int maxValue = *max_element(nums.begin(), nums.end());
        vector<int> points(maxValue + 1, 0);
        for (int num : nums) {
            points[num] += num;
        }

        int bestTwoBack = 0;
        int bestOneBack = 0;
        for (int value = 0; value <= maxValue; value++) {
            // 选择 value 会删除 value-1，结构等价于相邻房屋不能同时选。
            int current = max(bestOneBack, bestTwoBack + points[value]);
            bestTwoBack = bestOneBack;
            bestOneBack = current;
        }
        return bestOneBack;
    }

public:
    int deleteAndEarn(vector<int>& nums) {
        int mn = 1e4+1, mx=0;
        vector<int> cnt(1e4+1, 0);
        for(auto num: nums) {
            cnt[num]++;
            mn = min(mn, num);
            mx = max(mx, num);
        }
        int a=0, b=mn*cnt[mn], ans=b;
        for(int i=mn+1; i<=mx; i++) {
            ans = max(b, a+cnt[i]*i);
            a = b;
            b = ans;
        }
        return ans;




    }
};
// @lc code=end



/*
// @lcpr case=start
// [3,4,2]\n
// @lcpr case=end

// @lcpr case=start
// [2,2,3,3,3,4]\n
// @lcpr case=end

 */

