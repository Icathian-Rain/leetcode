/*
 * @lc app=leetcode.cn id=207 lang=cpp
 * @lcpr version=30204
 *
 * [207] 课程表
 */


// @lcpr-template-start
#include "../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    bool canFinishOpt(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> next(numCourses); // next[v]: 完成 v 后解锁的课
        vector<int> indeg(numCourses, 0);    // 剩余未满足的先修数
        for (const auto& p : prerequisites) {
            next[p[1]].push_back(p[0]);       // p[1] 是 p[0] 的先修
            indeg[p[0]]++;
        }
        queue<int> q;
        int done = 0; // 已确定可修的课程数
        for (int i = 0; i < numCourses; i++) {
            if (indeg[i] == 0) { // 无先修：立即可修
                q.push(i);
                done++;
            }
        }
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : next[u]) {
                if (--indeg[v] == 0) { // 先修全部满足：轮到 v
                    q.push(v);
                    done++;
                }
            }
        }
        return done == numCourses; // 环上课程入度永不清零 -> 计数不齐
    }

public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> graph(numCourses);
        vector<int> pre(numCourses, 0);
        for(auto prereq: prerequisites) {
            int u=prereq[0], v=prereq[1];
            graph[v].push_back(u);
            pre[u]++;
        }
        int ans=0;
        queue<int> q;
        for(int i=0; i<numCourses; i++) {
            if(pre[i] == 0) {
                q.push(i);
                ans++;
            }
        }
        while(!q.empty()) {
            auto u=q.front(); q.pop();
            for(auto v: graph[u]) {
                pre[v]--;
                if(pre[v]==0) {
                    q.push(v);
                    ans++;
                }
            }
        }
        return ans == numCourses;


    }
};
// @lc code=end



/*
// @lcpr case=start
// 2\n[[1,0]]\n
// @lcpr case=end

// @lcpr case=start
// 2\n[[1,0],[0,1]]\n
// @lcpr case=end

 */

