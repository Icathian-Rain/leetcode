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
    bool canAttendMeetingsOpt(vector<vector<int>>& intervals) {
        // 按左端点排序后，冲突只可能出现在相邻对之间
        sort(intervals.begin(), intervals.end());
        for (int i = 1; i < static_cast<int>(intervals.size()); i++) {
            // 严格小于：端点相接不算冲突
            if (intervals[i][0] < intervals[i - 1][1]) return false;
        }
        return true;
    }

public:
    bool canAttendMeetings(vector<vector<int>>& intervals) {
        int n = intervals.size();
        sort(intervals.begin(), intervals.end());
        for(int i=1; i<n; i++) {
            if(intervals[i][0] < intervals[i-1][1]) {
                return false;
            }
        }
        return true;
    }
};
// @lc code=end

