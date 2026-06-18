/*
 * @lc app=leetcode.cn id=784 lang=cpp
 * @lcpr version=30204
 *
 * [784] 字母大小写全排列
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    vector<string> letterCasePermutationOpt(string s) {
        vector<string> result;
        string current = s;

        function<void(int)> dfs = [&](int index) {
            if (index == static_cast<int>(current.size())) {
                result.push_back(current);
                return;
            }

            if (isdigit(current[index])) {
                dfs(index + 1);
                return;
            }

            current[index] = static_cast<char>(tolower(current[index]));
            dfs(index + 1);
            current[index] = static_cast<char>(toupper(current[index]));
            dfs(index + 1);
            current[index] = s[index]; // 恢复当前字符，避免影响上层对状态的理解。
        };

        dfs(0);
        return result;
    }

public:
    vector<string> letterCasePermutation(string s) {
        vector<string> ans;
        string path = s;

        function<void(int)> dfs = [&](int idx) -> void {
            if(idx == path.length()) {
                ans.push_back(path);
                return ;
            }

            if(isdigit(path[idx])) {
                dfs(idx+1);
            } else if(isalpha(path[idx])) {
                path[idx] = tolower(path[idx]);
                dfs(idx+1);
                path[idx] = toupper(path[idx]);
                dfs(idx+1);
            }
        };

        dfs(0);
        return ans;

    }
};
// @lc code=end



/*
// @lcpr case=start
// "a1b2"\n
// @lcpr case=end

// @lcpr case=start
// "3z4"\n
// @lcpr case=end

 */

