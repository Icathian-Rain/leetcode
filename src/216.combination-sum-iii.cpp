/*
 * @lc app=leetcode.cn id=216 lang=cpp
 * @lcpr version=30204
 *
 * [216] 组合总和 III
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    vector<vector<int>> combinationSum3Opt(int k, int n) {
        vector<vector<int>> result;
        vector<int> path;

        function<void(int, int, int)> dfs = [&](int start, int left, int remain) {
            if (left == 0) {
                if (remain == 0) {
                    result.push_back(path);
                }
                return;
            }

            // 还需要 left 个数时，起点不能超过 10 - left，否则数量不够。
            for (int value = start; value <= 10 - left; ++value) {
                if (value > remain) {
                    break;
                }
                path.push_back(value);
                dfs(value + 1, left - 1, remain - value);
                path.pop_back();
            }
        };

        dfs(1, k, n);
        return result;
    }

public:
    vector<vector<int>> ans;
    vector<int> path;
    int sum;
    void dfs(int k, int n, int start) {
        if(path.size() == k && sum == n) {
            ans.push_back(path);
        }
        if(path.size() == k || sum >= n) {
            return ;
        }

        int need = k-path.size();
        for(int i=start; i<=n-need+1 && i<=9; i++) {
            path.push_back(i);
            sum += i;
            dfs(k, n, i+1);
            path.pop_back();
            sum -= i;
        }
    }

    vector<vector<int>> combinationSum3(int k, int n) {
        if(k*(k+1)/2 > n) return ans;
        dfs(k, n, 1);
        return ans;



    }
};
// @lc code=end



/*
// @lcpr case=start
// 3\n7\n
// @lcpr case=end

// @lcpr case=start
// 3\n9\n
// @lcpr case=end

// @lcpr case=start
// 4\n1\n
// @lcpr case=end

// @lcpr case=start
2\n18
// @lcpr case=end
 */

