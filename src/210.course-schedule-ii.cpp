/*
 * @lc app=leetcode.cn id=210 lang=cpp
 * @lcpr version=30204
 *
 * [210] 课程表 II
 */


// @lcpr-template-start
#include "../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    vector<int> findOrderOpt(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> next(numCourses); // next[v]: 完成 v 后解锁的课
        vector<int> indeg(numCourses, 0);
        for (const auto& p : prerequisites) {
            next[p[1]].push_back(p[0]); // p[1] 是 p[0] 的先修
            indeg[p[0]]++;
        }
        vector<int> order;
        queue<int> q;
        for (int i = 0; i < numCourses; i++) {
            if (indeg[i] == 0) {
                q.push(i);
                order.push_back(i); // 入队即写入：入队顺序 = 拓扑序
            }
        }
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : next[u]) {
                if (--indeg[v] == 0) { // 先修全部就位
                    q.push(v);
                    order.push_back(v);
                }
            }
        }
        // 长度不齐 = 有环：环上课程永不入队
        return static_cast<int>(order.size()) == numCourses ? order : vector<int>{};
    }

public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> graph(numCourses);
        vector<int> pre(numCourses, 0);
        vector<int> ans;
        for(auto prereq: prerequisites) {
            int u=prereq[0], v=prereq[1];
            graph[v].push_back(u);
            pre[u]++;
        }
        queue<int> q;
        for(int i=0; i<numCourses; i++) {
            if(pre[i] == 0) {
                q.push(i);
                ans.push_back(i);
            }
        }
        while(!q.empty()) {
            auto u=q.front(); q.pop();
            for(auto v: graph[u]) {
                pre[v]--;
                if(pre[v]==0) {
                    q.push(v);
                    ans.push_back(v);
                }
            }
        }
        if(ans.size() == numCourses) {
            return ans;
        }
        return {};
    }
};
// @lc code=end



/*
// @lcpr case=start
// 2\n[[1,0]]\n
// @lcpr case=end

// @lcpr case=start
// 4\n[[1,0],[2,0],[3,1],[3,2]]\n
// @lcpr case=end

// @lcpr case=start
// 1\n[]\n
// @lcpr case=end

 */

