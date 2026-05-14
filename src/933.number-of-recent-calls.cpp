/*
 * @lc app=leetcode.cn id=933 lang=cpp
 * @lcpr version=30204
 *
 * [933] 最近的请求次数
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
class RecentCounter {
public:
    queue<int> q;
    queue<int> qOpt;
    RecentCounter() {
        
    }

    int pingOpt(int t) {
        qOpt.push(t);
        while(!qOpt.empty() && qOpt.front() < t - 3000) {
            // 队首永远是最早请求，过期请求只会从队首删除。
            qOpt.pop();
        }
        return qOpt.size();
    }
    
    int ping(int t) {
        q.push(t);
        while(!q.empty() && q.front() < t-3000) {
            q.pop();
        }
        return q.size();
    }
};

/**
 * Your RecentCounter object will be instantiated and called as such:
 * RecentCounter* obj = new RecentCounter();
 * int param_1 = obj->ping(t);
 */
// @lc code=end



/*
// @lcpr case=start
// ["RecentCounter", "ping", "ping", "ping", "ping"][[], [1], [100], [3001], [3002]]\n
// @lcpr case=end

 */

