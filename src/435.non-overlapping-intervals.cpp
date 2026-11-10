/*
 * @lc app=leetcode.cn id=435 lang=cpp
 * @lcpr version=30204
 *
 * [435] 无重叠区间
 */


// @lcpr-template-start
#include "../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    int s1(vector<vector<int>>& intervals) {
        // [1, 3], [2, 5], [6, 7]
        // 左端点排序
        int n=intervals.size();
        sort(intervals.begin(), intervals.end());
        int ans=0, r=intervals[0][1];
        for(int i=1; i<n; i++) {
            if(intervals[i][0] < r) {
                ans ++;
                r = min(r, intervals[i][1]);
            } else {
                r = intervals[i][1];
            }
        }
        return ans;
    }

    int s2(vector<vector<int>>& intervals) {
        // [1, 3], [2, 5], [6, 7]
        // 右端点排序
        int n=intervals.size();
        sort(intervals.begin(), intervals.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[1] < b[1];
        });
        int cnt=1, r=intervals[0][1];
        for(int i=1; i<n; i++) {
            if(intervals[i][0] >= r) {
                cnt++;
                r = intervals[i][1];
            }
        }
        return n-cnt;
    }

    int eraseOverlapIntervalsOpt(vector<vector<int>>& intervals) {
        // 按右端点升序：结束最早的区间一定可以保留在某个最优解中
        sort(intervals.begin(), intervals.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[1] < b[1];
        });
        int keep = 1;
        // endSoFar：当前保留链的结束位置
        int endSoFar = intervals[0][1];
        for (int i = 1; i < static_cast<int>(intervals.size()); i++) {
            // 端点接触不算重叠，起点 >= 结束位置即可直接保留
            if (intervals[i][0] >= endSoFar) {
                keep++;
                endSoFar = intervals[i][1];
            }
        }
        return static_cast<int>(intervals.size()) - keep;
    }

public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        // return s1(intervals);
        return s2(intervals);
    }
};
// @lc code=end



/*
// @lcpr case=start
// [[1,2],[2,3],[3,4],[1,3]]\n
// @lcpr case=end

// @lcpr case=start
// [ [1,2], [1,2], [1,2] ]\n
// @lcpr case=end

// @lcpr case=start
// [ [1,2], [2,3] ]\n
// @lcpr case=end

 */

