/*
 * @lc app=leetcode.cn id=57 lang=cpp
 * @lcpr version=30204
 *
 * [57] 插入区间
 */


// @lcpr-template-start
#include "../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    vector<vector<int>> insertOpt(vector<vector<int>>& intervals, vector<int>& newInterval) {
        vector<vector<int>> result;
        const int n = static_cast<int>(intervals.size());
        int index = 0;
        // 第一段严格位于新区间左侧，端点相等必须留给合并段。
        while (index < n && intervals[index][1] < newInterval[0]) {
            result.push_back(intervals[index++]);
        }

        int left = newInterval[0];
        int right = newInterval[1];
        // right 随合并扩张，每次都与最新右边界比较。
        while (index < n && intervals[index][0] <= right) {
            left = min(left, intervals[index][0]);
            right = max(right, intervals[index][1]);
            ++index;
        }
        result.push_back({left, right});

        // 原列表有序且互不重叠，剩余区间可直接复制。
        while (index < n) {
            result.push_back(intervals[index++]);
        }
        return result;
    }

public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        int n=intervals.size();
        vector<vector<int>> ans;
        int i=0;
        while(i<n && intervals[i][1] < newInterval[0]) {
            ans.push_back(intervals[i]);
            i++;
        }

        int l=newInterval[0], r = newInterval[1];
        while(i<n && intervals[i][0] <= r) {
            l = min(l, intervals[i][0]);
            r = max(r, intervals[i][1]);
            i++;
        }
        ans.push_back({l, r});
        while(i<n) {
            ans.push_back(intervals[i]);
            i++;
        }
        return ans;


    }
};
// @lc code=end



/*
// @lcpr case=start
// [[1,3],[6,9]]\n[2,5]\n
// @lcpr case=end

// @lcpr case=start
// [[1,2],[3,5],[6,7],[8,10],[12,16]]\n[4,8]\n
// @lcpr case=end

 */

