/*
 * @lc app=leetcode.cn id=139 lang=cpp
 * @lcpr version=30204
 *
 * [139] 单词拆分
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    bool wordBreakOpt(string s, vector<string>& wordDict) {
        unordered_set<string> words(wordDict.begin(), wordDict.end());
        int maxLen = 0;
        for (const string& word : wordDict) {
            maxLen = max(maxLen, static_cast<int>(word.size()));
        }

        int n = static_cast<int>(s.size());
        vector<bool> dp(n + 1, false);
        dp[0] = true;
        for (int end = 1; end <= n; end++) {
            for (int len = 1; len <= maxLen && len <= end; len++) {
                int start = end - len;
                // dp[start] 可达，且后缀片段在词典中，end 才可达。
                if (dp[start] && words.count(s.substr(start, len))) {
                    dp[end] = true;
                    break;
                }
            }
        }
        return dp[n];
    }

public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> st;
        for(auto word: wordDict) {
            st.insert(word);
        }
        int n=s.length();
        vector<bool> dp(n+1, 0);
        dp[0] = true;
        for(int i=1; i<=n; i++) {
            for(int j=0; j<i; j++) {
                if(dp[j] && st.find(s.substr(j, i-j)) != st.end()) {
                    dp[i] = true;
                    break;
                }
            }
        }
        return dp[n];
    }
};
// @lc code=end



/*
// @lcpr case=start
// "leetcode"\n["leet", "code"]\n
// @lcpr case=end

// @lcpr case=start
// "applepenapple"\n["apple", "pen"]\n
// @lcpr case=end

// @lcpr case=start
// "catsandog"\n["cats", "dog", "sand", "and", "cat"]\n
// @lcpr case=end

 */

