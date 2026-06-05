/*
 * @lc app=leetcode.cn id=17 lang=cpp
 * @lcpr version=30204
 *
 * [17] 电话号码的字母组合
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    vector<string> letterCombinationsOpt(string digits) {
        if (digits.empty()) {
            return {};
        }

        const vector<string> mapping = {
            "", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"
        };
        vector<string> result;
        string path;

        function<void(int)> dfs = [&](int index) {
            if (index == static_cast<int>(digits.size())) {
                result.push_back(path);
                return;
            }

            // 当前数字决定本层选择列表，每次选择后进入下一位。
            for (char letter : mapping[digits[index] - '0']) {
                path.push_back(letter);
                dfs(index + 1);
                path.pop_back();
            }
        };

        dfs(0);
        return result;
    }

public:
    vector<string> ans;
    string str;
    vector<string> keyboard;

    void dfs(string digits, int idx) {
        if(idx == digits.size()) {
            ans.push_back(str);
            return;
        }
        int pos = digits[idx] - '0';
        for(int i=0; i<keyboard[pos].size(); i++) {
            str.push_back(keyboard[pos][i]);
            dfs(digits, idx+1);
            str.pop_back();
        }
    }

    vector<string> letterCombinations(string digits) {
        keyboard = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
        dfs(digits, 0);
        return ans;
    }
};
// @lc code=end



/*
// @lcpr case=start
// "23"\n
// @lcpr case=end

// @lcpr case=start
// "2"\n
// @lcpr case=end

 */

