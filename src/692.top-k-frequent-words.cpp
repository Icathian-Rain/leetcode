/*
 * @lc app=leetcode.cn id=692 lang=cpp
 * @lcpr version=30204
 *
 * [692] 前K个高频单词
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
using pis = pair<int, string>;
class Solution {
    vector<string> topKFrequentOpt(vector<string>& words, int k) {
        unordered_map<string, int> count;
        for (const string& word : words) {
            ++count[word];
        }

        auto worseFirst = [](const pis& a, const pis& b) {
            if (a.first != b.first) {
                return a.first > b.first;
            }
            // 同频时字典序更大的词更差，应更早被弹出。
            return a.second < b.second;
        };

        priority_queue<pis, vector<pis>, decltype(worseFirst)> heap(worseFirst);
        for (const auto& [word, freq] : count) {
            heap.push({freq, word});
            if (heap.size() > k) {
                heap.pop();
            }
        }

        vector<string> ans;
        while (!heap.empty()) {
            ans.push_back(heap.top().second);
            heap.pop();
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }

public:
    vector<string> topKFrequent(vector<string>& words, int k) {
        int n=words.size();
        unordered_map<string, int> cnt;
        for(int i=0; i<n; i++) {
            cnt[words[i]]++;
        }

        auto cmp = [](const pis& a, const pis& b)->bool {
            if (a.first != b.first) {
                return a.first > b.first; 
            }
            return a.second < b.second;
        };

        priority_queue<pis, vector<pis>, decltype(cmp)> pq;
        for(auto [str, count]: cnt) {
            pq.push({count, str});
            while(pq.size() > k) {
                pq.pop();
            }
        }
        vector<string> ans;
        while(!pq.empty()) {
            auto [_, str] = pq.top();pq.pop();
            ans.push_back(str);
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};
// @lc code=end



/*
// @lcpr case=start
// ["i", "love", "leetcode", "i", "love", "coding"]\n2\n
// @lcpr case=end

// @lcpr case=start
// 4\n
// @lcpr case=end

 */

