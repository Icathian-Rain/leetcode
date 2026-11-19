/*
 * @lc app=leetcode.cn id=399 lang=cpp
 * @lcpr version=30204
 *
 * [399] 除法求值
 */


// @lcpr-template-start
#include "../header.h"
// @lcpr-template-end
// @lc code=start
class Solution {
    unordered_map<string, vector<pair<string, double>>> g;
    unordered_set<string> vis;

    double dfs(string u, string target) {
        if(u == target) return 1.0;
        vis.insert(u);
        for(auto [v, w]: g[u]) {
            if(vis.count(v)) continue;
            double res = dfs(v, target);
            if(res != -1.0) return w*res;
        }
        return -1.0;
    }
    vector<double> calcEquationOpt(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        // 带权无向图：u/v = w 正反向各存一条
        unordered_map<string, vector<pair<string, double>>> g;
        for (int i = 0; i < static_cast<int>(equations.size()); i++) {
            const string& u = equations[i][0];
            const string& v = equations[i][1];
            double w = values[i];
            g[u].push_back({v, w});      // 正向
            g[v].push_back({u, 1.0 / w}); // 反向取倒数（values > 0）
        }
        vector<double> ans;
        for (const auto& q : queries) {
            const string& u = q[0];
            const string& v = q[1];
            // 未知变量：不搜索直接 -1
            if (!g.count(u) || !g.count(v)) {
                ans.push_back(-1.0);
                continue;
            }
            // BFS 携带累计积；u == v 时起点即为答案 1.0
            unordered_set<string> vis{u};
            queue<pair<string, double>> bfs;
            bfs.push({u, 1.0});
            double result = -1.0;
            while (!bfs.empty()) {
                auto [cur, prod] = bfs.front(); bfs.pop();
                if (cur == v) { result = prod; break; }
                for (auto [nb, w] : g[cur]) {
                    if (vis.insert(nb).second) { // insert 返回 false 说明已访问
                        bfs.push({nb, prod * w});
                    }
                }
            }
            ans.push_back(result);
        }
        return ans;
    }

public:
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        int n=equations.size();
        for(int i=0; i<n; i++) {
            vector<string> eq = equations[i];
            double w = values[i];
            string u=eq[0], v=eq[1];
            g[u].push_back({v, w});
            g[v].push_back({u, 1.0/w});
        }
        vector<double> ans;
        for(auto q: queries) {
            string u=q[0], v=q[1];
            if(g.count(u) == 0 || g.count(v) == 0) {
                ans.push_back(-1.0);
                continue;
            }
            vis.clear();
            ans.push_back(dfs(u, v));
        }
        return ans;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [["a","b"],["b","c"]]\n[2.0,3.0]\n[["a","c"],["b","a"],["a","e"],["a","a"],["x","x"]]\n
// @lcpr case=end

// @lcpr case=start
// [["a","b"],["b","c"],["bc","cd"]]\n[1.5,2.5,5.0]\n[["a","c"],["c","b"],["bc","cd"],["cd","bc"]]\n
// @lcpr case=end

// @lcpr case=start
// [["a","b"]]\n[0.5]\n[["a","b"],["b","a"],["a","c"],["x","y"]]\n
// @lcpr case=end

 */

