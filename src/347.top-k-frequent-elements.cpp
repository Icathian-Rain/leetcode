/*
 * @lc app=leetcode.cn id=347 lang=cpp
 * @lcpr version=30204
 *
 * [347] 前 K 个高频元素
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
using pii=pair<int, int>;
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> cnt;
        for(auto num: nums) {
            cnt[num]++;
        }

        vector<pii> vec;
        for(auto [num, c]: cnt) {
            vec.push_back({c, num});
        }

        sort(vec.begin(), vec.end(), greater<pii>());

        vector<int> ans;
        for(int i=0; i<k; i++) {
            ans.push_back(vec[i].second);
        }
        return ans;


    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,1,1,2,2,3]\n2\n
// @lcpr case=end

// @lcpr case=start
// [1]\n1\n
// @lcpr case=end

// @lcpr case=start
// [1,2,1,2,1,2,3,1,3,2]\n2\n
// @lcpr case=end

 */

