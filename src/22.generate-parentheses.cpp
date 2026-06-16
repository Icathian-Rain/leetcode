/*
 * @lc app=leetcode.cn id=22 lang=cpp
 * @lcpr version=30204
 *
 * [22] 括号生成
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    vector<string> generateParenthesisOpt(int n) {
        vector<string> result;
        string current;

        function<void(int, int)> dfs = [&](int left, int right) {
            if (left == n && right == n) {
                result.push_back(current);
                return;
            }

            if (left < n) {
                current.push_back('(');
                dfs(left + 1, right);
                current.pop_back();
            }
            if (right < left) {
                current.push_back(')');
                dfs(left, right + 1);
                current.pop_back();
            }
        };

        dfs(0, 0);
        return result;
    }

public:
    vector<string> ans;
    string path;

    void dfs(int left, int right, int n) {
        if(left == n && right == n) {
            ans.push_back(path);
            return ;
        }
        if(left > right) {
            path.push_back(')');
            dfs(left, right+1, n);
            path.pop_back();
        }
        if(left < n) {
            path.push_back('(');
            dfs(left+1, right, n);
            path.pop_back();
        }
    }

    vector<string> generateParenthesis(int n) {
        dfs(0, 0, n);
        return ans;
    }
};
// @lc code=end



/*
// @lcpr case=start
// 3\n
// @lcpr case=end

// @lcpr case=start
// 1\n
// @lcpr case=end

 */

