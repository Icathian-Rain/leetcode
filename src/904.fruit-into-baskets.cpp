/*
 * @lc app=leetcode.cn id=904 lang=cpp
 * @lcpr version=30204
 *
 * [904] 水果成篮
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    int totalFruitOpt(vector<int>& fruits) {
        unordered_map<int, int> count;
        int left = 0;
        int ans = 0;

        for (int right = 0; right < (int)fruits.size(); ++right) {
            ++count[fruits[right]];
            while (count.size() > 2) {
                // 窗口内类型超过两个，持续移出左端水果直到重新合法。
                --count[fruits[left]];
                if (count[fruits[left]] == 0) {
                    count.erase(fruits[left]);
                }
                ++left;
            }
            ans = max(ans, right - left + 1);
        }

        return ans;
    }

public:
    int totalFruit(vector<int>& fruits) {
        int n=fruits.size();
        unordered_map<int, int> cnt;

        int ans=1;
        for(int l=0, r=0; r<n; r++) {
            cnt[fruits[r]]++;
            while(cnt.size() > 2) {
                cnt[fruits[l]]--;
                if(cnt[fruits[l]] == 0) {
                    cnt.erase(fruits[l]);
                }
                l++;
            }
            ans=max(ans, r-l+1);
        }
        return ans;



    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,2,1]\n
// @lcpr case=end

// @lcpr case=start
// [0,1,2,2]\n
// @lcpr case=end

// @lcpr case=start
// [1,2,3,2,2]\n
// @lcpr case=end

// @lcpr case=start
// [3,3,3,1,2,1,1,2,3,3,4]\n
// @lcpr case=end

 */

