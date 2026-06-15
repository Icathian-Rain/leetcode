/*
 * @lc app=leetcode.cn id=491 lang=cpp
 * @lcpr version=30204
 *
 * [491] 非递减子序列
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    vector<vector<int>> ans;
    vector<int> path;

    vector<vector<int>> findSubsequencesOpt(vector<int>& nums) {
        vector<vector<int>> result;
        vector<int> current;

        function<void(int)> dfs = [&](int start) {
            if (current.size() >= 2) {
                result.push_back(current);
            }

            unordered_set<int> usedThisLevel;
            for (int i = start; i < static_cast<int>(nums.size()); ++i) {
                if (usedThisLevel.count(nums[i])) {
                    continue; // 同一层相同数值只作为一次分支起点。
                }
                if (!current.empty() && nums[i] < current.back()) {
                    continue;
                }
                usedThisLevel.insert(nums[i]);
                current.push_back(nums[i]);
                dfs(i + 1);
                current.pop_back();
            }
        };

        dfs(0);
        return result;
    }

    void bt(vector<int>& nums, int start) {
        if(path.size() >= 2) {
            ans.push_back(path);
        }
        unordered_set<int> used;
        for(int i=start; i<nums.size(); i++) {
            if(used.count(nums[i])) continue;
            if(path.size() == 0 || nums[i] >= path.back()) {  
                used.insert(nums[i]);
                
                path.push_back(nums[i]);
                bt(nums, i+1);
                path.pop_back();
            }
        }
    }

public:
    vector<vector<int>> findSubsequences(vector<int>& nums) {
        bt(nums, 0);
        return ans;        
    }
};
// @lc code=end



/*
// @lcpr case=start
// [4,6,7,7]\n
// @lcpr case=end

// @lcpr case=start
// [4,4,3,2,1]\n
// @lcpr case=end

 */

