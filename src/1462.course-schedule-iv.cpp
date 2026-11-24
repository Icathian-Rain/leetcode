/*
 * @lc app=leetcode.cn id=1462 lang=cpp
 * @lcpr version=30204
 *
 * [1462] 课程表 IV
 */


// @lcpr-template-start
#include "../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    vector<bool> checkIfPrerequisiteOpt(int numCourses, vector<vector<int>>& prerequisites, vector<vector<int>>& queries) {
        // 方法一: 拓扑排序 + 传递闭包（与用户解法同构；方法二见下）
        vector<vector<int>> graph(numCourses);
        vector<int> indeg(numCourses, 0);
        vector<vector<bool>> reach(numCourses, vector<bool>(numCourses, false));
        for (const auto& p : prerequisites) {
            graph[p[0]].push_back(p[1]);
            indeg[p[1]]++;
        }
        queue<int> q;
        for (int i = 0; i < numCourses; i++) {
            if (indeg[i] == 0) q.push(i);
        }
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : graph[u]) {
                reach[u][v] = true;             // 直达边
                for (int i = 0; i < numCourses; i++) {
                    // u 的前驱也全是 v 的前驱: 传递合并
                    reach[i][v] = reach[i][v] || reach[i][u];
                }
                if (--indeg[v] == 0) q.push(v);
            }
        }
        vector<bool> ans;
        ans.reserve(queries.size());
        for (const auto& qr : queries) ans.push_back(reach[qr[0]][qr[1]]);
        return ans;
        // 方法二注释（不带闭包的替代）: 30 条边 BFS 每查询 -- O(QV)
    }

public:
    vector<bool> checkIfPrerequisite(int numCourses, vector<vector<int>>& prerequisites, vector<vector<int>>& queries) {
        vector<vector<int>> graph(numCourses);
        vector<int> pre(numCourses, 0);
        vector<vector<bool>> isPre(numCourses, vector<bool>(numCourses, false));
        for(auto prereq: prerequisites) {
            int u=prereq[0], v=prereq[1];
            graph[u].push_back(v);
            pre[v]++;
        }
        queue<int> q;
        for(int i=0; i<numCourses; i++) {
            if(pre[i] == 0) {
                q.push(i);
            }
        }
        while(!q.empty()) {
            auto u=q.front(); q.pop();
            for(auto v: graph[u]) {
                isPre[u][v] = true;
                for(int i=0; i<numCourses; i++) {
                    isPre[i][v] = isPre[i][v] | isPre[i][u];
                }
                pre[v]--;
                if(pre[v]==0) {
                    q.push(v);
                }
            }
        }
        vector<bool> ans;
        for(auto q: queries) {
            ans.push_back(isPre[q[0]][q[1]]);
        }
        return ans;
    }
};
// @lc code=end



/*
// @lcpr case=start
// 2\n[[1,0]]\n[[0,1],[1,0]]\n
// @lcpr case=end

// @lcpr case=start
// 2\n[]\n[[1,0],[0,1]]\n
// @lcpr case=end

// @lcpr case=start
// 3\n[[1,2],[1,0],[2,0]]\n[[1,0],[1,2]]\n
// @lcpr case=end

 */

