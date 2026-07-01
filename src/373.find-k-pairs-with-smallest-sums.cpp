/*
 * @lc app=leetcode.cn id=373 lang=cpp
 * @lcpr version=30204
 *
 * [373] 查找和最小的 K 对数字
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
using pii = pair<int, int>;
class Solution {
    vector<vector<int>> kSmallestPairsOpt(vector<int>& nums1, vector<int>& nums2, int k) {
        if (nums1.empty() || nums2.empty() || k == 0) {
            return {};
        }

        auto cmp = [&](const pii& a, const pii& b) {
            return nums1[a.first] + nums2[a.second] > nums1[b.first] + nums2[b.second];
        };

        priority_queue<pii, vector<pii>, decltype(cmp)> heap(cmp);
        for (int i = 0; i < min<int>(k, nums1.size()); ++i) {
            heap.push({i, 0});
        }

        vector<vector<int>> ans;
        while (k-- > 0 && !heap.empty()) {
            auto [i, j] = heap.top();
            heap.pop();
            ans.push_back({nums1[i], nums2[j]});
            // 固定 nums1[i] 后，只推进 nums2 的下一个位置，避免一次展开所有组合。
            if (j + 1 < nums2.size()) {
                heap.push({i, j + 1});
            }
        }
        return ans;
    }

public:
    vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        int m=nums1.size(), n=nums2.size();
        auto cmp = [&](const pii& a, const pii& b) {
            return nums1[a.first] + nums2[a.second] > nums1[b.first] + nums2[b.second];
        };
        priority_queue<pii, vector<pii>, decltype(cmp)> pq(cmp);
        vector<vector<int>> ans;
        for(int i=0; i<min(k, m); i++) {
            pq.push({i, 0});
        }
        while(k-->0 && !pq.empty()) {
            auto [x, y] = pq.top(); pq.pop();
            ans.push_back({nums1[x], nums2[y]});
            if(y+1 < n) {
                pq.push({x, y+1});
            }
        }
        return ans;




    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,7,11]\n[2,4,6]\n3\n
// @lcpr case=end

// @lcpr case=start
// [1,1,2]\n[1,2,3]\n2\n
// @lcpr case=end

 */

