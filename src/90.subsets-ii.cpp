/*
 * @lc app=leetcode.cn id=90 lang=cpp
 * @lcpr version=30204
 *
 * [90] 子集 II
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    vector<vector<int>> ans;
    vector<int> path;

    vector<vector<int>> subsetsWithDupOpt(vector<int>& nums) {
        sort(nums.begin(), nums.end());

        vector<vector<int>> result;
        vector<int> current;

        function<void(int)> dfs = [&](int start) {
            result.push_back(current);

            for (int i = start; i < static_cast<int>(nums.size()); ++i) {
                if (i > start && nums[i] == nums[i - 1]) {
                    continue; // 同一层跳过重复值，避免生成重复子集。
                }
                current.push_back(nums[i]);
                dfs(i + 1);
                current.pop_back();
            }
        };

        dfs(0);
        return result;
    }

    void backtrace(vector<int>& nums, int idx) {
        ans.push_back(path);
        for(int i=idx; i<nums.size(); i++) {
            if(i>idx && nums[i] == nums[i-1]) continue;
            path.push_back(nums[i]);
            backtrace(nums, i+1);
            path.pop_back();
        }
        return ;
    }
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        backtrace(nums, 0);
        return ans;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,2,2]\n
// @lcpr case=end

// @lcpr case=start
// [0]\n
// @lcpr case=end

 */

