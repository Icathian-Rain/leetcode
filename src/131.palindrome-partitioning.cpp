/*
 * @lc app=leetcode.cn id=131 lang=cpp
 * @lcpr version=30204
 *
 * [131] 分割回文串
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    vector<vector<int>> f;
    vector<vector<string>> ans;
    vector<string> path;

    vector<vector<string>> partitionOpt(string s) {
        int n = static_cast<int>(s.size());
        vector<vector<bool>> isPalindrome(n, vector<bool>(n, true));
        for (int left = n - 1; left >= 0; --left) {
            for (int right = left + 1; right < n; ++right) {
                isPalindrome[left][right] =
                    (s[left] == s[right]) && isPalindrome[left + 1][right - 1];
            }
        }

        vector<vector<string>> result;
        vector<string> current;
        function<void(int)> dfs = [&](int start) {
            if (start == n) {
                result.push_back(current);
                return;
            }

            for (int end = start; end < n; ++end) {
                if (!isPalindrome[start][end]) {
                    continue;
                }
                current.push_back(s.substr(start, end - start + 1));
                dfs(end + 1);
                current.pop_back();
            }
        };

        dfs(0);
        return result;
    }

public:
    void dfs(string s, int start) {
        if(start == s.length()) {
            ans.push_back(path);
            return;
        }
        for(int i=start; i<s.length(); i++) {
            if(f[start][i]) {
                path.push_back(s.substr(start, i-start+1));
                dfs(s, i+1);
                path.pop_back();
            }
        }
    }


    vector<vector<string>> partition(string s) {
        int n=s.length();
        f.assign(n, vector<int>(n, true));
        for(int i=n-1; i>=0; i--) {
            for(int j=i+1; j<n; j++) {
                f[i][j] = (s[i] == s[j]) && (f[i+1][j-1]);
            }
        }
        dfs(s, 0);
        return ans;


    }
};
// @lc code=end



/*
// @lcpr case=start
// "aab"\n
// @lcpr case=end

// @lcpr case=start
// "a"\n
// @lcpr case=end

 */

