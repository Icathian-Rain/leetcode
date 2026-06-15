/*
 * @lc app=leetcode.cn id=40 lang=cpp
 * @lcpr version=30204
 *
 * [40] 组合总和 II
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    vector<vector<int>> ans;
    vector<int> path;

    vector<vector<int>> combinationSum2Opt(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());

        vector<vector<int>> result;
        vector<int> current;

        function<void(int, int)> dfs = [&](int start, int remain) {
            if (remain == 0) {
                result.push_back(current);
                return;
            }

            for (int i = start; i < static_cast<int>(candidates.size()); ++i) {
                if (i > start && candidates[i] == candidates[i - 1]) {
                    continue; // 同一层跳过重复候选，保证组合唯一。
                }
                if (candidates[i] > remain) {
                    break;
                }
                current.push_back(candidates[i]);
                dfs(i + 1, remain - candidates[i]);
                current.pop_back();
            }
        };

        dfs(0, target);
        return result;
    }

    void bt(vector<int>& candidates, int target, int start) {
        if(target <= 0) {
            if(target == 0) {
                ans.push_back(path);
            }
            return ;
        }
        for(int i=start; i<candidates.size(); i++) {
            if(i > start && candidates[i] == candidates[i-1]) {
                continue;
            }
            path.push_back(candidates[i]);
            bt(candidates, target-candidates[i], i+1);
            path.pop_back();
        }
    }

public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        bt(candidates, target, 0);
        return ans;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [10,1,2,7,6,1,5]\n8\n
// @lcpr case=end

// @lcpr case=start
// [2,5,2,1,2]\n5\n
// @lcpr case=end

 */

