/*
 * @lc app=leetcode.cn id=30 lang=cpp
 * @lcpr version=30204
 *
 * [30] 串联所有单词的子串
 */

// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        int len=s.length();
        int m=words.size(), n=words[0].size();

        vector<int> ans;
        for(int i=0; i<n && i+m*n<=len; i++) {
            unordered_map<string, int> cnt;
            for(auto word: words) {
                cnt[word]++;
            }
            // 滑动窗口
            for(int j=i; j+n<=len; j+=n) {
                string tmp = s.substr(j, n);
                cnt[tmp]--;
                if(cnt[tmp] == 0) cnt.erase(tmp);

                if(j-i<(m-1)*n) continue;
                if(cnt.size() == 0) ans.push_back(j-(m-1)*n);

                tmp = s.substr(j-(m-1)*n, n);
                cnt[tmp]++;
                if(cnt[tmp] == 0) cnt.erase(tmp);
            }
        }
        return ans;
    }
};
// @lc code=end

/*
// @lcpr case=start
// "barfoothefoobarman"\n["foo","bar"]\n
// @lcpr case=end

// @lcpr case=start
// "wordgoodgoodgoodbestword"\n["word","good","best","word"]\n
// @lcpr case=end

// @lcpr case=start
// "barfoofoobarthefoobarman"\n["bar","foo","the"]\n
// @lcpr case=end

 */
