/*
 * @lc app=leetcode.cn id=46 lang=cpp
 * @lcpr version=30204
 *
 * [46] 全排列
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    vector<vector<int>> permuteOpt(vector<int>& nums) {
        vector<vector<int>> result;
        vector<int> current;
        vector<bool> used(nums.size(), false);

        function<void()> dfs = [&]() {
            if (current.size() == nums.size()) {
                result.push_back(current);
                return;
            }

            for (int i = 0; i < static_cast<int>(nums.size()); ++i) {
                if (used[i]) {
                    continue;
                }
                used[i] = true;
                current.push_back(nums[i]);
                dfs();
                current.pop_back();
                used[i] = false; // 恢复使用状态，让同层其他分支可以选择该元素。
            }
        };

        dfs();
        return result;
    }

public:
    vector<vector<int>> ans;
    vector<int> path;
    vector<int> used;
    void backtrace(vector<int>& nums) {
        if(path.size() == nums.size()) {
            ans.push_back(path);
            return;
        }

        for(int i=0; i<nums.size(); i++) {
            if(used[i] != true) {
                used[i] = true;
                path.push_back(nums[i]);
                backtrace(nums);
                path.pop_back();
                used[i] = false;
            }
        }
        return ;

    }


    vector<vector<int>> permute(vector<int>& nums) {
        int n=nums.size();
        used.assign(n, false);
        backtrace(nums);
        return ans;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,2,3]\n
// @lcpr case=end

// @lcpr case=start
// [0,1]\n
// @lcpr case=end

// @lcpr case=start
// [1]\n
// @lcpr case=end

 */

