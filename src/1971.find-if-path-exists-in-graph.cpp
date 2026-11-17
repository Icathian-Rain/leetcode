/*
 * @lc app=leetcode.cn id=1971 lang=cpp
 * @lcpr version=30204
 *
 * [1971] 寻找图中是否存在路径
 */


// @lcpr-template-start
#include "../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    bool validPathOpt(int n, vector<vector<int>>& edges, int source, int destination) {
        vector<vector<int>> adj(n);
        for (const auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]); // 无向图双向存边
        }
        vector<bool> vis(n, false);
        queue<int> q;
        q.push(source);
        vis[source] = true; // 入队即标记，防止重复入队
        while (!q.empty()) {
            int x = q.front(); q.pop();
            if (x == destination) return true; // 扩展前先判终点
            for (int next : adj[x]) {
                if (!vis[next]) {
                    vis[next] = true;
                    q.push(next);
                }
            }
        }
        return false;
    }

    bool dfs(int x, int destination, vector<vector<int>>& adj, vector<bool>& vis) {
        if(x == destination) {
            return true;
        }
        vis[x] = true;
        for(auto next: adj[x]) {
            if(!vis[next] && dfs(next, destination, adj, vis)) {
                return true;
            }
        }
        return false;
    }
public:
    bool validPath(int n, vector<vector<int>>& edges, int source, int destination) {
        vector<vector<int>> adj(n);
        for(auto e: edges) {
            int u=e[0], v=e[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        vector<bool> vis(n, false);
        return dfs(source, destination, adj, vis);

    }
};
// @lc code=end



/*
// @lcpr case=start
// 3\n[[0,1],[1,2],[2,0]]\n0\n2\n
// @lcpr case=end

// @lcpr case=start
// 6\n[[0,1],[0,2],[3,5],[5,4],[4,3]]\n0\n5\n
// @lcpr case=end

 */

