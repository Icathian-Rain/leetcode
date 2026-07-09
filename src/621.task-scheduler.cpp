/*
 * @lc app=leetcode.cn id=621 lang=cpp
 * @lcpr version=30204
 *
 * [621] 任务调度器
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    int leastIntervalOpt(vector<char>& tasks, int n) {
        vector<int> freq(26, 0);
        for (char task : tasks) {
            ++freq[task - 'A'];
        }

        int maxFreq = 0;
        for (int count : freq) {
            maxFreq = max(maxFreq, count);
        }

        int maxKinds = 0;
        for (int count : freq) {
            if (count == maxFreq) {
                ++maxKinds;
            }
        }

        // 最高频任务决定最少框架长度；任务足够多时，答案就是任务总数。
        int frame = (maxFreq - 1) * (n + 1) + maxKinds;
        return max(static_cast<int>(tasks.size()), frame);
    }

public:
    int leastInterval(vector<char>& tasks, int n) {
        vector<int> cnt(26, 0);
        for (char ch : tasks) {
            cnt[ch - 'A']++;
        }

        int maxCnt = 0;
        for (int x : cnt) {
            maxCnt = max(maxCnt, x);
        }

        int maxKinds = 0;
        for (int x : cnt) {
            if (x == maxCnt) {
                maxKinds++;
            }
        }

        int frame = (maxCnt - 1) * (n + 1) + maxKinds;
        return max((int)tasks.size(), frame);
    }
};
// @lc code=end



/*

// A -> B -> idle -> A -> B -> idle -> A -> B 
// @lcpr case=start
// ["A","A","A","B","B","B"]\n2\n
// @lcpr case=end

// A -> B -> C-> A -> B -> D
// @lcpr case=start
// ["A","C","A","B","D","B"]\n1\n
// @lcpr case=end

// @lcpr case=start
// ["A","A","A","B","B","B"]\n3\n
// @lcpr case=end

 */

