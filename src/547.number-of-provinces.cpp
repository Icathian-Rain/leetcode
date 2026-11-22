/*
 * @lc app=leetcode.cn id=547 lang=cpp
 * @lcpr version=30204
 *
 * [547] 省份数量
 */


// @lcpr-template-start
#include "../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    int findCircleNumOpt(vector<vector<int>>& isConnected) {
        int n = static_cast<int>(isConnected.size());
        vector<char> vis(n, 0); // 0 = 未访问
        int ans = 0;
        for (int i = 0; i < n; i++) { // 每发现一个未访问节点 = 新分量
            if (vis[i]) continue;
            ans++;
            queue<int> q;
            vis[i] = 1;
            q.push(i);
            while (!q.empty()) {
                int u = q.front(); q.pop();
                for (int v = 0; v < n; v++) {
                    // 直接扫矩阵一行取邻居，免建邻接表
                    if (isConnected[u][v] && !vis[v]) {
                        vis[v] = 1; // 入队即标记
                        q.push(v);
                    }
                }
            }
        }
        return ans;
    }

public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        int n=isConnected.size();
        vector<vector<int>> graph(n);
        for(int i=0; i<n; i++) {
            for(int j=0; j<n; j++) {
                if(isConnected[i][j]==1) {
                    graph[i].push_back(j);
                }
            }
        }
        vector<int> vis(n, -1);
        int ans=0;
        for(int i=0; i<n; i++) {
            if(vis[i] != -1) continue;
            ans++;
            queue<int> q;
            q.push(i);
            vis[i]=ans;
            while(!q.empty()) {
                auto u=q.front(); q.pop();
                for(auto v:graph[u]) {
                    if(vis[v] == -1) {
                        q.push(v);
                        vis[v]=ans;
                    }
                }
            }
        }
        return ans;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [[1,1,0],[1,1,0],[0,0,1]]\n
// @lcpr case=end

// @lcpr case=start
// [[1,0,0],[0,1,0],[0,0,1]]\n
// @lcpr case=end

 */

