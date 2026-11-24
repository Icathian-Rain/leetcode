/*
 * @lc app=leetcode.cn id=802 lang=cpp
 * @lcpr version=30204
 *
 * [802] 找到最终的安全状态
 */


// @lcpr-template-start
#include "../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    vector<int> eventualSafeNodesOpt(vector<vector<int>>& graph) {
        int n = static_cast<int>(graph.size());
        vector<vector<int>> rg(n);         // 反图: rg[v] = 指向 v 的节点列表
        vector<int> out(n, 0);              // 剩余出度（未确定的后继数）
        for (int u = 0; u < n; u++) {
            for (int v : graph[u]) rg[v].push_back(u);
            out[u] = static_cast<int>(graph[u].size());
        }
        queue<int> q;
        for (int i = 0; i < n; i++) {
            if (out[i] == 0) q.push(i);     // 终端节点先入队
        }
        vector<int> ans;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            ans.push_back(u);               // 出队即确定为安全节点
            for (int v : rg[u]) {           // 反图所有前驱出度减一
                if (--out[v] == 0) q.push(v); // 后继全部安全 -> v 也安全
            }
        }
        sort(ans.begin(), ans.end());       // 出队序即字典升序答案，sort 兜底
        return ans;
    }

public:
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        int n=graph.size();
        vector<vector<int>> rg(n);
        vector<int> inDeg(n);
        for(int u=0; u<n; u++) {
            for(auto v: graph[u]) {
                rg[v].push_back(u);
            }
            inDeg[u] = graph[u].size();
        }
        queue<int> q;
        for(int i=0; i<n; i++) {
            if(inDeg[i] == 0) {
                q.push(i);
            }
        }
        while(!q.empty()) {
            int y=q.front();q.pop();
            for(int x: rg[y]) {
                inDeg[x]--;
                if(inDeg[x] == 0) {
                    q.push(x);
                }
            }
        }
        vector<int> ans;
        for(int i=0; i<n; i++) {
            if(inDeg[i] == 0) {
                ans.push_back(i);
            }
        }
        return ans;


    }
};
// @lc code=end



/*
// @lcpr case=start
// [[1,2],[2,3],[5],[0],[5],[],[]]\n
// @lcpr case=end

// @lcpr case=start
// [[1,2,3,4],[1,2],[3,4],[0,4],[]]\n
// @lcpr case=end

 */

