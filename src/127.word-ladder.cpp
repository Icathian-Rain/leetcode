/*
 * @lc app=leetcode.cn id=127 lang=cpp
 * @lcpr version=30204
 *
 * [127] 单词接龙
 */


// @lcpr-template-start
#include "../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    int ladderLengthOpt(string beginWord, string endWord, vector<string>& wordList) {
        // 哈希集合：O(1) 查存在，删除即"已访问"（免独立 visited）
        unordered_set<string> dict(wordList.begin(), wordList.end());
        if (!dict.count(endWord)) return 0;
        dict.erase(beginWord); // beginWord 不占位（若在表中）
        queue<pair<string, int>> q; // (当前词, 已用单词数)
        q.push({beginWord, 1});
        while (!q.empty()) {
            auto [word, steps] = q.front(); q.pop();
            // 逐位替换 26 个字母生成邻居：与当前词恰好差一个字母全体
            for (int i = 0; i < static_cast<int>(word.size()); i++) {
                char origin = word[i];
                for (char c = 'a'; c <= 'z'; c++) {
                    word[i] = c;
                    if (word == endWord) return steps + 1; // 首达即最短，单词数口径
                    if (dict.count(word)) {
                        dict.erase(word); // 删除即标记，防止重入
                        q.push({word, steps + 1});
                    }
                }
                word[i] = origin; // 恢复被替换位
            }
        }
        return 0;
    }

public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        int n=wordList.size();
        vector<vector<int>> adj(n);
        auto cmp = [](const string& a, const string& b) -> bool {
            int len=a.size();
            int diff=0;
            for(int i=0; i<len; i++) {
                if(a[i] != b[i]) {
                    diff++;
                    if(diff > 1) {
                        return false;
                    }
                }
            }
            return true;
        };
        int start = -1;
        for(int i=0; i<n; i++) {
            if(wordList[i]==endWord) {
                start = i;
            }
            for(int j=i+1; j<n; j++) {
                if(cmp(wordList[i], wordList[j])) {
                    adj[i].push_back(j);
                    adj[j].push_back(i);
                }
            }
            if(cmp(wordList[i], beginWord)) {
                adj[i].push_back(n);
            }
        }
        if(start == -1) return 0;
        vector<int> dist(n, -1);
        queue<int> q;
        q.push(start);
        dist[start] = 1;
        while(!q.empty()) {
            auto p=q.front(); q.pop();
            for(int j=0; j<adj[p].size(); j++) {
                if(adj[p][j] == n) return dist[p]+1;
                if(dist[adj[p][j]] == -1) {
                    q.push(adj[p][j]);
                    dist[adj[p][j]] = dist[p]+1;
                }
            }
        }
        return 0;
    }
};
// @lc code=end



/*
// @lcpr case=start
// "hit"\n"cog"\n["hot","dot","dog","lot","log","cog"]\n
// @lcpr case=end

// @lcpr case=start
// "hit"\n"cog"\n["hot","dot","dog","lot","log"]\n
// @lcpr case=end

 */

