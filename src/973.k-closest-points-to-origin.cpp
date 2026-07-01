/*
 * @lc app=leetcode.cn id=973 lang=cpp
 * @lcpr version=30204
 *
 * [973] 最接近原点的 K 个点
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
using pii = pair<int, int>;
class Solution {
    vector<vector<int>> kClosestOpt(vector<vector<int>>& points, int k) {
        priority_queue<pii> heap;
        for (int i = 0; i < points.size(); ++i) {
            int x = points[i][0], y = points[i][1];
            int distance = x * x + y * y;
            heap.push({distance, i});
            // 保留当前距离最小的 k 个点，堆顶是其中最远的候选。
            if (heap.size() > k) {
                heap.pop();
            }
        }

        vector<vector<int>> ans;
        while (!heap.empty()) {
            int index = heap.top().second;
            heap.pop();
            ans.push_back(points[index]);
        }
        return ans;
    }

public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        int n=points.size();
        auto cmp = [](const pii& a, const pii& b) -> bool{
            return a.first < b.first;
        };

        priority_queue<pii, vector<pii>, decltype(cmp)> pq;
        for(int i=0; i<n; i++) {
            int x = points[i][0], y=points[i][1];
            int distance = x*x+y*y;
            pq.push({distance, i});
            while(pq.size() > k) {
                pq.pop();
            }
        }

        vector<vector<int>> ans;
        while(!pq.empty()) {
            auto [_, idx] = pq.top(); pq.pop();
            ans.push_back({points[idx][0], points[idx][1]});
        }
        return ans;


    }
};
// @lc code=end



/*
// @lcpr case=start
// [[1,3],[-2,2]]\n1\n
// @lcpr case=end

// @lcpr case=start
// [[3,3],[5,-1],[-2,4]]\n2\n
// @lcpr case=end

 */

