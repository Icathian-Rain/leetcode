/*
 * @lc app=leetcode.cn id=77 lang=cpp
 * @lcpr version=30204
 *
 * [77] 组合
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    vector<vector<int>> combineOpt(int n, int k) {
        vector<vector<int>> result;
        vector<int> path;

        function<void(int)> dfs = [&](int start) {
            if (static_cast<int>(path.size()) == k) {
                result.push_back(path);
                return;
            }

            // 剩余位置不足时提前停止，避免进入必然无解的分支。
            int need = k - static_cast<int>(path.size());
            for (int value = start; value <= n - need + 1; ++value) {
                path.push_back(value);
                dfs(value + 1);
                path.pop_back();
            }
        };

        dfs(1);
        return result;
    }

public:
    vector<vector<int>> ans;
    vector<int> comb;
    void dfs(int n, int k, int idx) {
        if(comb.size() == k) {
            ans.push_back(comb);
            return ;
        }

        int need = k-comb.size();        
        for(int i=idx; i<=n-need+1; i++) {
            comb.push_back(i);
            dfs(n, k, i+1);
            comb.pop_back();
        }
    }


    vector<vector<int>> combine(int n, int k) {
        dfs(n, k, 1);
        return ans;
    }
};
// @lc code=end



/*
// @lcpr case=start
// 4\n2\n
// @lcpr case=end

// @lcpr case=start
// 1\n1\n
// @lcpr case=end

 */

