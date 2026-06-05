/*
 * @lc app=leetcode.cn id=78 lang=cpp
 * @lcpr version=30204
 *
 * [78] 子集
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    vector<vector<int>> subsetsOpt(vector<int>& nums) {
        vector<vector<int>> result;
        vector<int> path;

        function<void(int)> dfs = [&](int start) {
            // 当前路径本身就是一个合法子集。
            result.push_back(path);
            for (int i = start; i < static_cast<int>(nums.size()); ++i) {
                path.push_back(nums[i]);
                dfs(i + 1);
                path.pop_back(); // 撤销当前选择，继续尝试同层下一个元素。
            }
        };

        dfs(0);
        return result;
    }

public:
    vector<vector<int>> ans;
    vector<int> comp;

    void backtrace(vector<int>& nums, int idx) {
        if(idx == nums.size()) {
            ans.push_back(comp);
            return ;
        }
        comp.push_back(nums[idx]);
        backtrace(nums, idx+1);
        comp.pop_back();
        backtrace(nums, idx+1);
    }


    vector<vector<int>> subsets(vector<int>& nums) {
        backtrace(nums, 0);
        return ans;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,2,3]\n
// @lcpr case=end

// @lcpr case=start
// [0]\n
// @lcpr case=end

 */

