/*
 * @lc app=leetcode.cn id=218 lang=cpp
 * @lcpr version=30204
 *
 * [218] 天际线问题
 */


// @lcpr-template-start
#include "../header.h"
// @lcpr-template-end
// @lc code=start
using pii = pair<int, int>;
class Solution {
    vector<vector<int>> getSkylineOpt(vector<vector<int>>& buildings) {
        vector<pair<int, int>> events;
        events.reserve(buildings.size() * 2);
        for (const auto& building : buildings) {
            events.push_back({building[0], -building[2]});
            events.push_back({building[1], building[2]});
        }
        sort(events.begin(), events.end());
        multiset<int> activeHeights{0}; // 地面哨兵保证可随时读取最大高度。
        vector<vector<int>> result;
        int previousHeight = 0;
        for (size_t i = 0; i < events.size();) {
            int x = events[i].first;
            // 同一横坐标的增删全部完成后，再输出该位置的最终高度。
            while (i < events.size() && events[i].first == x) {
                int height = events[i].second;
                if (height < 0) activeHeights.insert(-height);
                else activeHeights.erase(activeHeights.find(height));
                ++i;
            }
            int currentHeight = *activeHeights.rbegin();
            if (currentHeight != previousHeight) {
                result.push_back({x, currentHeight});
                previousHeight = currentHeight;
            }
        }
        return result;
    }

public:
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
        vector<pii> events;
        for(auto &b: buildings) {
            events.push_back({b[0], -b[2]});
            events.push_back({b[1], b[2]});
        }
        sort(events.begin(), events.end());
        multiset<int> s;
        s.insert(0);
        vector<vector<int>> ans;
        int pre = 0, n = events.size();
        for(int i=0; i<n;) {
            int x=events[i].first;
            // 处理同一位置横坐标的点
            while(i<n && events[i].first == x) {
                int h=events[i].second;
                if(h<0) {
                    s.insert(-h);
                } else {
                    s.erase(s.find(h));
                }
                i++;
            }
            int cur = *s.rbegin();
            if(cur != pre) {
                ans.push_back({x, cur});
                pre = cur;
            }
        }
        return ans;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [[2,9,10],[3,7,15],[5,12,12],[15,20,10],[19,24,8]]\n
// @lcpr case=end

// @lcpr case=start
// [[0,2,3],[2,5,3]]\n
// @lcpr case=end

 */
