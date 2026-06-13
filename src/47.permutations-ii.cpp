/*
 * @lc app=leetcode.cn id=47 lang=cpp
 * @lcpr version=30204
 *
 * [47] 全排列 II
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    vector<vector<int>> ans;
    vector<int> path;
    vector<int> used;

    vector<vector<int>> permuteUniqueOpt(vector<int>& nums) {
        sort(nums.begin(), nums.end());

        vector<vector<int>> result;
        vector<int> current;
        vector<bool> visited(nums.size(), false);

        function<void()> dfs = [&]() {
            if (current.size() == nums.size()) {
                result.push_back(current);
                return;
            }

            for (int i = 0; i < static_cast<int>(nums.size()); ++i) {
                if (visited[i]) {
                    continue;
                }
                // 同一层只使用相同数字中的第一个未使用位置，避免重复排列。
                if (i > 0 && nums[i] == nums[i - 1] && !visited[i - 1]) {
                    continue;
                }
                visited[i] = true;
                current.push_back(nums[i]);
                dfs();
                current.pop_back();
                visited[i] = false;
            }
        };

        dfs();
        return result;
    }

    void backtrace(vector<int> nums) {
        if(path.size() == nums.size()) {
            ans.push_back(path);
            return;
        }
        for(int i=0; i<nums.size(); i++) {
            if((used[i] == true) || (i>0 && nums[i] == nums[i-1] && (used[i-1] == false))) {
                continue;
            }
            used[i] = true;
            path.push_back(nums[i]);
            backtrace(nums);
            path.pop_back();
            used[i] = false;
        }
    }

public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        int n=nums.size();
        used.assign(n, false);
        sort(nums.begin(), nums.end());
        backtrace(nums);
        return ans;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,1,2]\n
// @lcpr case=end

// @lcpr case=start
// [1,2,3]\n
// @lcpr case=end

 */

