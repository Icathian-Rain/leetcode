/*
 * @lc app=leetcode.cn id=316 lang=cpp
 * @lcpr version=30204
 *
 * [316] 去除重复字母
 */


// @lcpr-template-start
#include "../header.h"
// @lcpr-template-end
// @lc code=start
using pii = pair<int, int>;
class Solution {
    string removeDuplicateLettersOpt(string s) {
        vector<int> cnt(26, 0), inStack(26, 0);
        for (char ch : s) cnt[ch - 'a']++;
        string stk; // 栈内即当前最优前缀，结束时就是答案
        for (char ch : s) {
            int x = ch - 'a';
            cnt[x]--; // cnt[x] 从此表示 x 在当前位置之后还出现几次
            if (inStack[x]) continue; // 已保留过，保证每字母恰好一次
            // 弹出条件三要素：栈非空、栈顶更大、栈顶之后还有备份
            while (!stk.empty() && stk.back() > ch && cnt[stk.back() - 'a'] > 0) {
                inStack[stk.back() - 'a'] = 0;
                stk.pop_back();
            }
            stk.push_back(ch);
            inStack[x] = 1;
        }
        return stk;
    }

public:
    string removeDuplicateLetters(string s) {
        int n=s.size();
        vector<int> cnt(26, 0), vis(26, 0);
        for(auto ch: s) cnt[ch-'a']++;
        string ans;
        for(auto ch: s) {
            int x = ch - 'a';
            cnt[x]--;
            if(vis[x]) continue;
            while(!ans.empty() && ans.back() > ch && cnt[ans.back()-'a'] > 0) {
                vis[ans.back() - 'a'] = 0;
                ans.pop_back();
            }
            ans.push_back(ch);
            vis[x] = 1;
        }
        return ans;

    }
};
// @lc code=end



/*
// @lcpr case=start
// "bcabc"\n
// @lcpr case=end

// @lcpr case=start
// "cbacdcbc"\n
// @lcpr case=end

 */

