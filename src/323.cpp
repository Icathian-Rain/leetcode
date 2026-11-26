
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
    int countComponentsOpt(int n, vector<vector<int>>& edges) {
        vector<int> fa(n), sz(n, 1);
        iota(fa.begin(), fa.end(), 0);
        int cnt = n;                     // 初始每人自成一类
        auto findIt = [&](int x) {
            while (fa[x] != x) {
                fa[x] = fa[fa[x]];      // 隔代压缩跳两层
                x = fa[x];
            }
            return x;
        };
        for (const auto& e : edges) {
            int rx = findIt(e[0]), ry = findIt(e[1]);
            if (rx == ry) continue;      // 同根：忽略
            if (sz[rx] < sz[ry]) swap(rx, ry);
            fa[ry] = rx;
            sz[rx] += sz[ry];
            cnt--;                       // 成功合并：分量数减一
        }
        return cnt;
    }

public:
    int countComponents(int n, vector<vector<int>>& edges) {
        UnionFind uf(n);
        for(auto e: edges) {
            int x=e[0], y=e[1];
            uf.unite(x, y);
        }
        return uf.count();
    }
};

int main() {
    struct TestCase {
        int n;
        vector<vector<int>> edges;
        int expected;
    };

    vector<TestCase> tests = {
        {5, {{0,1},{1,2},{3,4}}, 2},
        {5, {{0,1},{1,2},{2,3},{3,4}}, 1},
        {1, {}, 1},
        {5, {}, 5},
        {2, {{0,1}}, 1},
        {3, {{0,1},{1,2},{0,2}}, 1},
        {4, {{0,1},{1,2},{0,2}}, 2},
        {6, {{0,1},{2,3},{4,5}}, 3},
        {6, {{0,1},{0,2},{1,2},{3,4},{3,5},{4,5}}, 2},
        {5, {{0,1},{0,2}}, 3}
    };

    int passed = 0, failed = 0;
    double totalTime = 0, maxTime = 0;
    vector<int> failedCases;

    for(int i=0; i<SZ(tests); i++) {
        auto [n, edges, expected] = tests[i];
        Solution sol;

        cout << "\n===== Test " << i+1 << " =====" << endl;
        cout << "n = ";
        print(n);
        cout << "edges = ";
        print(edges);

        Timer timer;
        int result = sol.countComponents(n, edges);
        double elapsed = timer.elapsed();

        totalTime += elapsed;
        maxTime = max(maxTime, elapsed);

        EXPECT_EQ(result, expected);
        if(result == expected) {
            passed++;
        } else {
            failed++;
            failedCases.pb(i+1);
        }

        cout << "Time: " << fixed << setprecision(3)
             << elapsed << " ms" << endl;
    }

    cout << "\n========== Summary ==========" << endl;
    cout << "Total cases:  " << SZ(tests) << endl;
    cout << "Passed:       " << passed << endl;
    cout << "Failed:       " << failed << endl;
    cout << "Pass rate:    " << fixed << setprecision(2)
         << 100.0*passed/SZ(tests) << "%" << endl;

    if(failed > 0) {
        cout << "Failed cases: ";
        print(failedCases);
    }

    cout << fixed << setprecision(3);
    cout << "Total time:   " << totalTime << " ms" << endl;
    cout << "Average time: " << totalTime/SZ(tests) << " ms" << endl;
    cout << "Maximum time: " << maxTime << " ms" << endl;
    cout << "Result: " << (failed == 0 ? "ACCEPTED" : "WRONG ANSWER") << endl;
    return 0;
}
