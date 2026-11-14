/*
 * @lc app=leetcode.cn id=252 lang=cpp
 * @lcpr version=30204
 *
 * [252] 会议室
 */


// @lcpr-template-start
#include "../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    int minMeetingRoomsOpt(vector<vector<int>>& intervals) {
        vector<pair<int, int>> events; // {时刻, 变化量}
        for (const auto& iv : intervals) {
            events.push_back({iv[0], 1});   // 占用
            events.push_back({iv[1], -1});  // 释放
        }
        // pair 字典序：同一时刻 -1 在 +1 前，先释放后占用，端点相接可共用
        sort(events.begin(), events.end());
        int total = 0, ans = 0;
        for (const auto& [time, delta] : events) {
            total += delta;
            ans = max(ans, total); // 峰值即所需房间数
        }
        return ans;
    }

public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        int n=intervals.size();
        vector<vector<int>> events;
        for(auto interval: intervals) {
            int begin = interval[0], end = interval[1];
            events.push_back({begin, 1});
            events.push_back({end, -1});
        }
        sort(events.begin(), events.end());
        int total = 0;
        int ans = 0;
        for(auto e: events) {
            total += e[1];
            ans = max(ans, total);
        }
        return ans;
    }
};
// @lc code=end

