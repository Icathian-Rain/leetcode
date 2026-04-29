/*
 * @lc app=leetcode.cn id=1559 lang=cpp
 * @lcpr version=30204
 *
 * [1559] 二维网格图中探测环
 */


// @lcpr-template-start
#include"../header.h"
// @lcpr-template-end
// @lc code=start
struct DSU {
    vector<int> fa, sz;

    DSU(int n) {
        fa.resize(n);
        sz.assign(n, 1);
        iota(fa.begin(), fa.end(), 0);
    }

    int find(int x) {
        return fa[x] == x ? x : fa[x] = find(fa[x]);
    }

    bool unite(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return false;
        if (sz[x] < sz[y]) swap(x, y);
        fa[y] = x;
        sz[x] += sz[y];
        return true;
    }
};



class Solution {
public:
    bool containsCycle(vector<vector<char>>& grid) {
        int m=grid.size(), n=grid[0].size();
        DSU dsu(m*n);
        auto getid = [&](int i, int j) {
            return i*n+j;
        };
        for(int i=0; i<m; i++) {
            for(int j=0; j<n; j++) {
                int u=getid(i, j);
                if(i+1<m && grid[i][j] == grid[i+1][j]) {
                    int v=getid(i+1, j);
                    if(dsu.unite(u, v) == false) {
                        return true;
                    }
                }
                if(j+1<n && grid[i][j] == grid[i][j+1]) {
                    int v=getid(i, j+1);
                    if(dsu.unite(u, v) == false) {
                        return true;
                    }
                }
            }
        }
        return false;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [["a","a","a","a"],["a","b","b","a"],["a","b","b","a"],["a","a","a","a"]]\n
// @lcpr case=end

// @lcpr case=start
// [["c","c","c","a"],["c","d","c","c"],["c","c","e","c"],["f","c","c","c"]]\n
// @lcpr case=end

// @lcpr case=start
// [["a","b","b"],["b","z","b"],["b","b","a"]]\n
// @lcpr case=end

 */

