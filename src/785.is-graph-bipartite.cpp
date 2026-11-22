/*
 * @lc app=leetcode.cn id=785 lang=cpp
 * @lcpr version=30204
 *
 * [785] 判断二分图
 */


// @lcpr-template-start
#include "../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    bool isBipartiteOpt(vector<vector<int>>& graph) {
        int n = static_cast<int>(graph.size());
        vector<int> color(n, 0); // 0 = 未染色，1/-1 = 两个集合
        for (int i = 0; i < n; i++) {
            if (color[i] != 0) continue; // 已属于某个处理过的分量
            queue<int> q;
            color[i] = 1; // 起点染哪色不影响判定（整分量翻转等价）
            q.push(i);
            while (!q.empty()) {
                int u = q.front(); q.pop();
                for (int v : graph[u]) {
                    if (color[v] == 0) {
                        color[v] = -color[u]; // 入队即染色（填值即标记）
                        q.push(v);
                    } else if (color[v] == color[u]) {
                        return false; // 相邻同色 = 出现奇环
                    }
                }
            }
        }
        return true;
    }

public:
    bool isBipartite(vector<vector<int>>& graph) {
        int n=graph.size();
        vector<int> color(n, 0);
        for(int i=0; i<n; i++) {
            if(color[i] != 0) continue;
            queue<int> q;
            color[i] = 1;
            q.push(i);

            while(!q.empty()) {
                auto u=q.front(); q.pop();
                for(auto v: graph[u]) {
                    if(color[v] == 0) {
                        color[v] = -color[u];
                        q.push(v);
                    } else if(color[v] == color[u]) {
                        return false;
                    }
                }
            }
        }
        return true;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [[1,2,3],[0,2],[0,1,3],[0,2]]\n
// @lcpr case=end

// @lcpr case=start
// [[1,3],[0,2],[1,3],[0,2]]\n
// @lcpr case=end

 */

