/*
 * @lc app=leetcode.cn id=39 lang=cpp
 * @lcpr version=30204
 *
 * [39] 组合总和
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    vector<vector<int>> combinationSumOpt(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());

        vector<vector<int>> result;
        vector<int> path;

        function<void(int, int)> dfs = [&](int start, int remain) {
            if (remain == 0) {
                result.push_back(path);
                return;
            }

            for (int i = start; i < static_cast<int>(candidates.size()); ++i) {
                if (candidates[i] > remain) {
                    break;
                }
                path.push_back(candidates[i]);
                dfs(i, remain - candidates[i]); // 仍从 i 开始，表示当前数字可重复使用。
                path.pop_back();
            }
        };

        dfs(0, target);
        return result;
    }

public:
    vector<vector<int>> ans;
    vector<int> path;
    int sum;

    void dfs(vector<int>& candidates, int target, int start) {
        if(sum >= target) {
            if(sum == target) ans.push_back(path);
            return ;
        }

        for(int i=start; i<candidates.size(); i++) {
            path.push_back(candidates[i]);
            sum += candidates[i];
            dfs(candidates, target, i);
            sum -= candidates[i];
            path.pop_back();
        }
    }

    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        dfs(candidates, target, 0);
        return ans;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [2,3,6,7]\n7\n
// @lcpr case=end

// @lcpr case=start
// [2,3,5]\n8\n
// @lcpr case=end

// @lcpr case=start
// [2]\n1\n
// @lcpr case=end

 */

