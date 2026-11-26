
#include "../header.h"

class UnionFind {
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
            x=find(x);
            y=find(y);
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
    bool validTreeOpt(int n, vector<vector<int>>& edges) {
        // 判据一：树必有恰 n-1 条边（少则不连通，多则必有环）——正确性必需非剪枝
        if (edges.size() != static_cast<size_t>(n) - 1) return false;
        // 判据二：n-1 条边全部"当时合并两个不同分量"地加入
        // => 无环 + 成功合并 n-1 次 => 分量数恰为 1（连通被推出，不用再查）
        vector<int> fa(n), sz(n, 1);
        iota(fa.begin(), fa.end(), 0);
        auto findIt = [&](int x) {
            while (fa[x] != x) {
                fa[x] = fa[fa[x]]; // 隔代压缩
                x = fa[x];
            }
            return x;
        };
        for (const auto& e : edges) {
            int rx = findIt(e[0]), ry = findIt(e[1]);
            if (rx == ry) return false;   // 成环：非树
            if (sz[rx] < sz[ry]) swap(rx, ry);
            fa[ry] = rx;
            sz[rx] += sz[ry];
        }
        return true;
    }

public:
    bool validTree(int n, vector<vector<int>>& edges) {
        UnionFind uf(n);
        if(edges.size() != n-1) {
            return false;
        }
        for(auto e: edges) {
            int x=e[0], y=e[1];
            if(uf.connected(x, y) == true) {
                return false;
            }
            uf.unite(x, y);
        }
        return true;

    }
};

int main() {
    struct TestCase {
        int n;
        vector<vector<int>> edges;
        bool expected;
    };

    vector<TestCase> tests = {
        {5, {{0,1},{0,2},{0,3},{1,4}}, true},
        {5, {{0,1},{1,2},{2,3},{1,3},{1,4}}, false},
        {4, {{0,1},{2,3}}, false},
        {1, {}, true},
        {2, {}, false},
        {2, {{0,1}}, true},
        {3, {{0,1},{1,2},{2,0}}, false},
        {4, {{0,1},{1,2},{2,0}}, false},
        {5, {{0,1},{1,2},{2,3},{3,4}}, true}
    };

    double totalTime = 0;
    cout << boolalpha;

    for (int i = 0; i < SZ(tests); i++) {
        auto [n, edges, expected] = tests[i];
        Solution sol;

        cout << "\n===== Test " << i + 1 << " =====" << endl;
        cout << "n = " << n << endl;
        cout << "edges = ";
        print(edges);

        Timer timer;
        bool result = sol.validTree(n, edges);
        double elapsed = timer.elapsed();
        totalTime += elapsed;

        EXPECT_EQ(result, expected);
        cout << "Time: " << fixed << setprecision(3)
             << elapsed << " ms" << endl;
    }

    cout << "\n===== Summary =====" << endl;
    cout << "Total cases: " << SZ(tests) << endl;
    cout << "Total time: " << totalTime << " ms" << endl;
    cout << "Average time: " << totalTime / SZ(tests) << " ms" << endl;
    return 0;
}
