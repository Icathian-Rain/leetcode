/*
 * @lc app=leetcode.cn id=XXX lang=cpp
 * @lcpr version=30204
 *
 * [XXX] 题目名称
 */

// @lcpr-template-start
#include "../header.h"
// @lcpr-template-end

// @lc code=start
class Solution {
public:
    // 官方函数签名，函数体留空自行实现
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {

    }
};
// @lc code=end

#ifdef LOCAL
int main() {
    struct TestCase {
        vector<vector<int>> edges;
        vector<int> expected;
    };

    vector<TestCase> tests = {
        {{{1,2},{1,3},{2,3}}, {2,3}},
        {{{1,2},{2,3},{3,4},{1,4},{1,5}}, {1,4}},
        {{{1,2},{2,3},{3,4},{1,4}}, {1,4}},
        {{{1,2},{1,3},{2,3},{3,4}}, {2,3}},
        {{{1,2},{1,3},{1,4},{2,4}}, {2,4}},
        {{{1,2},{2,3},{1,3},{3,4},{4,5}}, {1,3}}
    };

    int passed = 0, failed = 0;
    double totalTime = 0, maxTime = 0;
    vector<int> failedCases;

    for(int i=0; i<SZ(tests); i++) {
        auto [edges, expected] = tests[i];
        Solution sol;

        cout << "\n===== Test " << i+1 << " =====" << endl;
        cout << "Input: ";
        print(edges);

        Timer timer;
        auto result = sol.findRedundantConnection(edges);
        double elapsed = timer.elapsed();

        totalTime += elapsed;
        maxTime = max(maxTime, elapsed);

        // 先比较得到 bool，再断言（容器不能直接进 EXPECT_EQ）
        bool ok = vectorEqual(result, expected);
        EXPECT_EQ(ok, true);

        if(ok) {
            passed++;
        } else {
            failed++;
            failedCases.pb(i+1);
            cout << "Expected: ";
            print(expected);
            cout << "Got:      ";
            print(result);
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
    cout << "Result: "
         << (failed == 0 ? "ACCEPTED" : "WRONG ANSWER") << endl;
    return 0;
}
#endif

/*
// @lcpr case=start
// [[1,2],[1,3],[2,3]]\n
// @lcpr case=end

// @lcpr case=start
// [[1,2],[2,3],[3,4],[1,4],[1,5]]\n
// @lcpr case=end

// @lcpr case=start
// [[1,2],[2,3],[3,4],[1,4]]\n
// @lcpr case=end

// @lcpr case=start
// [[1,2],[1,3],[2,3],[3,4]]\n
// @lcpr case=end

// @lcpr case=start
// [[1,2],[1,3],[1,4],[2,4]]\n
// @lcpr case=end

// @lcpr case=start
// [[1,2],[2,3],[1,3],[3,4],[4,5]]\n
// @lcpr case=end
*/
