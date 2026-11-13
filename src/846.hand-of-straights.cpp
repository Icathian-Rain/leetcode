/*
 * @lc app=leetcode.cn id=846 lang=cpp
 * @lcpr version=30204
 *
 * [846] 一手顺子
 */


// @lcpr-template-start
#include "../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    bool isNStraightHandOpt(vector<int>& hand, int groupSize) {
        int n = static_cast<int>(hand.size());
        if (n % groupSize != 0) return false; // 无法整分成等长组
        sort(hand.begin(), hand.end());
        unordered_map<int, int> cnt;
        for (int x : hand) cnt[x]++;
        for (int x : hand) {              // 升序遍历保证先处理最小起点
            if (cnt[x] == 0) continue;    // 已被之前的组消耗完
            for (int j = 0; j < groupSize; j++) {
                auto it = cnt.find(x + j);
                if (it == cnt.end() || it->second == 0) return false; // 连续结构断链
                if (--(it->second) == 0) cnt.erase(it);
            }
        }
        return true;
    }

public:
    bool isNStraightHand(vector<int>& hand, int groupSize) {
        int n=hand.size();
        if(n % groupSize != 0) {
            return false;
        }
        sort(hand.begin(), hand.end());
        unordered_map<int, int> mp;
        for(auto x: hand) {
            mp[x]++;
        }
        for(auto x: hand) {
            if(mp.find(x) == mp.end()) {
                continue;
            }
            for(int j=0; j<groupSize; j++) {
                int num = x+j;
                if(mp.find(num) == mp.end()) {
                    return false;
                }
                mp[num]--;
                if(mp[num] == 0) {
                    mp.erase(num);
                }
            }
        }
        return true;



    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,2,3,6,2,3,4,7,8]\n3\n
// @lcpr case=end

// @lcpr case=start
// [1,2,3,4,5]\n4\n
// @lcpr case=end

 */

