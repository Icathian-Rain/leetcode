/*
 * @lc app=leetcode.cn id=767 lang=cpp
 * @lcpr version=30204
 *
 * [767] 重构字符串
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
using pic = pair<int, char>;
class Solution {
    string reorganizeStringOpt(string s) {
        vector<int> freq(26, 0);
        for (char ch : s) {
            ++freq[ch - 'a'];
        }

        int maxFreq = 0;
        char maxChar = 'a';
        for (int i = 0; i < 26; ++i) {
            if (freq[i] > maxFreq) {
                maxFreq = freq[i];
                maxChar = static_cast<char>('a' + i);
            }
        }

        int n = static_cast<int>(s.size());
        if (maxFreq > (n + 1) / 2) {
            return "";
        }

        string ans(n, ' ');
        int index = 0;
        while (freq[maxChar - 'a'] > 0) {
            ans[index] = maxChar;
            index += 2;
            --freq[maxChar - 'a'];
        }

        for (int i = 0; i < 26; ++i) {
            while (freq[i] > 0) {
                if (index >= n) {
                    index = 1;
                }
                ans[index] = static_cast<char>('a' + i);
                index += 2;
                --freq[i];
            }
        }
        return ans;
    }

public:
    string s1(string s) {
        vector<int> cnt(26, 0);
        for(auto ch: s) {
            cnt[ch-'a']++;
        }
        int maxCnt = 0;
        for(auto count: cnt) {
            maxCnt = max(maxCnt, count);
        }

        int n=s.length();
        if(maxCnt > (n+1)/2) {
            return "";
        }
        priority_queue<pic> pq;
        for(int i=0; i<26; i++) {
            if(cnt[i] > 0)
            pq.push({cnt[i], 'a'+i});
        }
        string ans;
        while(pq.size() >= 2) {
            auto [cnt1, ch1] = pq.top(); pq.pop();
            auto [cnt2, ch2] = pq.top(); pq.pop();
            ans.push_back(ch1);
            ans.push_back(ch2);
            cnt1--;
            cnt2--;
            if(cnt1 > 0) {
                pq.push({cnt1, ch1});
            }
            if(cnt2 > 0) {
                pq.push({cnt2, ch2});
            }
        }
        if(!pq.empty()) {
            ans.push_back(pq.top().second);
        }
        return ans;
    }

    string s2(string s) {
        vector<int> cnt(26, 0);
        for(auto ch: s) {
            cnt[ch-'a']++;
        }
        int maxCnt = 0;
        char maxch = 'a';
        for(int i=0; i<26; i++) {
            if(cnt[i] > maxCnt) {
                maxCnt = cnt[i];
                maxch = 'a'+i;
            }
        }

        int n=s.length();
        if(maxCnt > (n+1)/2) {
            return "";
        }
        string ans(n, ' ');
        int idx = 0;
        while(cnt[maxch-'a'] > 0) {
            ans[idx] = maxch;
            idx+=2;
            cnt[maxch-'a']--;
        }
        for(int i=0; i<26; i++) {
            while(cnt[i] > 0) {
                if(idx >= n) {
                    idx = 1;
                }
                ans[idx] = char('a'+i);
                idx+=2;
                cnt[i]--;
            }
        }
        return ans;
    }

    string reorganizeString(string s) {
        // return s1(s);
        return s2(s);
    }
};
// @lc code=end



/*
// @lcpr case=start
// "aab"\n
// @lcpr case=end

// @lcpr case=start
// "aaab"\n
// @lcpr case=end

 */

