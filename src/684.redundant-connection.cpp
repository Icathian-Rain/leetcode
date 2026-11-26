/*
 * @lc app=leetcode.cn id=684 lang=cpp
 * @lcpr version=30204
 *
 * [684] 冗余连接
 */


// @lcpr-template-start
#include "../header.h"
// @lcpr-template-end
// @lc code=start
class UnionFind {
    private:
        vector<int> fa, sz;
        int cnt;
    public:
        UnionFind(int n): fa(n), sz(n, 1), cnt(n) {
            iota(fa.begin(), fa.end(), 0);
        }
        int find(int x) {
            return fa[x] == x ? x : fa[x] = find(fa[x]);
        }
        bool unite(int x, int y) {
            x = find(x);
            y = find(y);
            if(x == y) return false;
            if(sz[x] < sz[y]) swap(x, y);
            fa[y] = x;
            sz[x] += sz[y];
            cnt --;
            return true;
        }
        bool connected(int x, int y) {
            return find(x) == find(y);
        }
        int size(int x) {
            return sz[find(x)];
        }
        int count() {
            return cnt;
        }
};
class Solution {
    vector<int> findRedundantConnectionOpt(vector<vector<int>>& edges) {
        int n = static_cast<int>(edges.size());
        vector<int> fa(n + 1, 0);          // 1 基题目直接开 n+1，免偏移换算
        vector<int> sz(n + 1, 1);
        for (int i = 0; i <= n; i++) fa[i] = i;
        // 迭代隔代压缩查根，免递归
        auto findIt = [&](int x) {
            while (fa[x] != x) {
                fa[x] = fa[fa[x]];        // 祖父一步跳两层
                x = fa[x];
            }
            return x;
        };
        for (const auto& e : edges) {
            int rx = findIt(e[0]), ry = findIt(e[1]);
            if (rx == ry) return e;        // 两端已同根：此边成环，即答案
            if (sz[rx] < sz[ry]) swap(rx, ry); // 小挂大
            fa[ry] = rx;
            sz[rx] += sz[ry];
        }
        return {};
    }

public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        int n=edges.size();
        UnionFind uf(n);
        for(auto edge: edges) {
            int x=edge[0], y=edge[1];
            if(uf.connected(x-1, y-1)) {
                return {x, y};
            }
            uf.unite(x-1, y-1);
        }
        return {};
    }
};
// @lc code=end



/*
// @lcpr case=start
// [[1,2], [1,3], [2,3]]\n
// @lcpr case=end

// @lcpr case=start
// [[1,2], [2,3], [3,4], [1,4], [1,5]]\n
// @lcpr case=end

 */

