/*
 * @lc app=leetcode.cn id=1094 lang=cpp
 * @lcpr version=30204
 *
 * [1094] 拼车
 */


// @lcpr-template-start
#include "../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    bool carPoolingOpt(vector<vector<int>>& trips, int capacity) {
        // 值域 0..1000，用差分数组记录每站上下车的人数变化
        int diff[1001] = {0};
        for (const auto& trip : trips) {
            diff[trip[1]] += trip[0];  // from 处上车
            diff[trip[2]] -= trip[0]; // to 处下车，座位立即释放
        }
        int total = 0;
        for (int pos = 0; pos <= 1000; pos++) {
            total += diff[pos]; // 前缀和即瞬时载客量
            if (total > capacity) return false;
        }
        return true;
    }

public:
    bool carPooling(vector<vector<int>>& trips, int capacity) {
        int n=trips.size();
        vector<vector<int>> events;
        for(auto trip: trips) {
            int num = trip[0], from = trip[1], to = trip[2];
            events.push_back({from, num});
            events.push_back({to, -num});
        }
        sort(events.begin(), events.end());
        int total = 0;
        for(auto e: events) {
            total += e[1];
            if(total > capacity) {
                return false;
            }
        }
        return true;


    }
};
// @lc code=end



/*
// @lcpr case=start
// [[2,1,5],[3,3,7]]\n4\n
// @lcpr case=end

// @lcpr case=start
// [[2,1,5],[3,3,7]]\n5\n
// @lcpr case=end

 */

