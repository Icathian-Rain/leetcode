/*
 * @lc app=leetcode.cn id=605 lang=cpp
 * @lcpr version=30204
 *
 * [605] 种花问题
 */


// @lcpr-template-start
#include "../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    bool canPlaceFlowersOpt(vector<int>& flowerbed, int n) {
        int len = static_cast<int>(flowerbed.size());
        int count = 0;
        for (int i = 0; i < len; i++) {
            // 左右邻居越界视为空地（0）
            int left = (i == 0) ? 0 : flowerbed[i - 1];
            int right = (i == len - 1) ? 0 : flowerbed[i + 1];
            if (flowerbed[i] == 0 && left == 0 && right == 0) {
                count++;
                i++; // 种下后右邻格必然不可种，再跳一格到 i+2
            }
        }
        return count >= n;
    }

public:
    bool canPlaceFlowers(vector<int>& flowerbed, int n) {
        int len = flowerbed.size();
        int pre = -2;
        int sum = 0;
        for(int i=0; i<len; i++) {
            if(flowerbed[i] == 1) {
                int total = i - pre - 3;
                sum += (total+1)/2;
                if(sum >= n) return true;
                pre = i;
            }
        }
        return sum + (len-1-pre)/2 >= n;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,0,0,0,1]\n1\n
// @lcpr case=end

// @lcpr case=start
// [1,0,0,0,1]\n2\n
// @lcpr case=end

// @lcpr case=start
[1,0]\n1\n
// @lcpr case=end
 */

