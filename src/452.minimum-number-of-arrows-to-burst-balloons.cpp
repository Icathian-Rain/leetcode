/*
 * @lc app=leetcode.cn id=452 lang=cpp
 * @lcpr version=30204
 *
 * [452] 用最少数量的箭引爆气球
 */


// @lcpr-template-start
#include "../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    int findMinArrowShotsOpt(vector<vector<int>>& points) {
        // 按右端点升序；比较器只用 <，坐标可达 ±2^31，相减会溢出
        sort(points.begin(), points.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[1] < b[1];
        });
        int arrows = 1;
        // 第一支箭放在结束最早气球的右端点
        int arrowPos = points[0][1];
        for (int i = 1; i < static_cast<int>(points.size()); i++) {
            // 闭区间相切即引爆，左端点 == 箭位置仍算覆盖，用 >
            if (points[i][0] > arrowPos) {
                arrows++;
                arrowPos = points[i][1];
            }
        }
        return arrows;
    }

public:
    int findMinArrowShots(vector<vector<int>>& points) {
        int n = points.size();
        sort(points.begin(), points.end());
        int l=points[0][0], r = points[0][1];
        int ans = 1;
        for(int i=1; i<n; i++) {
            if(points[i][0] > r) {
                ans ++;
                l = points[i][0], r = points[i][1];
            } else {
                l = points[i][0], r = min(r, points[i][1]);
            }
        }
        return ans;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [[10,16],[2,8],[1,6],[7,12]]\n
// @lcpr case=end

// @lcpr case=start
// [[1,2],[3,4],[5,6],[7,8]]\n
// @lcpr case=end

// @lcpr case=start
// [[1,2],[2,3],[3,4],[4,5]]\n
// @lcpr case=end

 */

