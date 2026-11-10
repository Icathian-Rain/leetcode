/*
 * @lc app=leetcode.cn id=1288 lang=cpp
 * @lcpr version=30204
 *
 * [1288] 删除被覆盖区间
 */


// @lcpr-template-start
#include "../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    int removeCoveredIntervalsOpt(vector<vector<int>>& intervals) {
        // 左端点升序、同起点右端点降序：长区间先出现，同起点的短区间必被覆盖
        sort(intervals.begin(), intervals.end(), [](const vector<int>& a, const vector<int>& b) {
            if (a[0] != b[0]) return a[0] < b[0];
            return a[1] > b[1];
        });
        int covered = 0;
        // maxRight：已处理区间的最大右端点
        int maxRight = intervals[0][1];
        for (int i = 1; i < static_cast<int>(intervals.size()); i++) {
            // 排序已保证左端点条件成立，只需比较右端点
            if (intervals[i][1] <= maxRight) {
                covered++;
            } else {
                maxRight = intervals[i][1];
            }
        }
        return static_cast<int>(intervals.size()) - covered;
    }

public:
    int removeCoveredIntervals(vector<vector<int>>& intervals) {
        int n=intervals.size();
        sort(intervals.begin(), intervals.end(), [](const vector<int>& a, const vector<int>& b){
            if(a[0] == b[0]) return a[1] > b[1];
            return a[0] < b[0];
        });
        int l=intervals[0][0], r=intervals[0][1];
        int ans = 1;
        for(int i=1; i<n; i++) {
            if(intervals[i][1] <= r) {
                continue;
            } else {
                ans ++;
                l = intervals[i][0], r = intervals[i][1];
            }
        }
        return ans;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [[1,4],[3,6],[2,8]]\n
// @lcpr case=end

 */

