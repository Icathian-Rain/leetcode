/*
 * @lc app=leetcode.cn id=56 lang=cpp
 * @lcpr version=30204
 *
 * [56] 合并区间
 */


// @lcpr-template-start
#include "../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    vector<vector<int>> mergeOpt(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end());
        vector<vector<int>> result;
        for (const auto& interval : intervals) {
            // 闭区间端点相等时也重叠；只有严格分离才新增一段。
            if (result.empty() || result.back()[1] < interval[0]) {
                result.push_back(interval);
            } else {
                // 已排序，当前区间只能扩展最后一段的右边界。
                result.back()[1] = max(result.back()[1], interval[1]);
            }
        }
        return result;
    }

public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        int n=intervals.size();
        sort(intervals.begin(), intervals.end());

        vector<vector<int>> ans;
        int l=intervals[0][0], r=intervals[0][1];
        for(int i=1; i<n; i++) {
            if(intervals[i][0] <= r) {
                r = max(r, intervals[i][1]);
            } else {
                ans.push_back({l, r});
                l = intervals[i][0], r = intervals[i][1];
            }
        }
        ans.push_back({l, r});
        return ans;

    }
};
// @lc code=end



/*
// @lcpr case=start
// [[1,3],[2,6],[8,10],[15,18]]\n
// @lcpr case=end

// @lcpr case=start
// [[1,4],[4,5]]\n
// @lcpr case=end

// @lcpr case=start
// [[4,7],[1,4]]\n
// @lcpr case=end

 */

