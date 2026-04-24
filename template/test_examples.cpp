/*
 * 测试用例示例文件 - 展示所有 header.h 工具的使用方法
 * 参考本文件编写你的测试用例
 */
#include "../header.h"

class Solution {
public:
    int solve(vector<int>& nums) {
        return nums.size();
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Solution sol;
    Timer timer; // 性能计时器

    // ========== 测试用例 1: 数组处理 ==========
    {
        vector<int> nums = {1, 2, 3, 4, 5};
        auto result = sol.solve(nums);

        cout << "Test 1 - Input: "; print(nums);
        cout << "Output: "; print(result);
        EXPECT_EQ(result, 5); // 断言验证
        cout << endl;
    }

    // ========== 测试用例 2: 链表操作 ==========
    {
        ListNode* head = buildList({1, 2, 3, 4});
        print(head);
        // auto result = sol.solveList(head);
        cout << endl;
    }

    // ========== 测试用例 3: 二叉树操作 ==========
    {
        // 方式1: 使用字符串数组（支持 "null"）
        TreeNode* root1 = buildTree({"1", "null", "2", "3"});
        printTree(root1); // 层序打印

        // 方式2: 使用整数数组（-1 表示 null）
        TreeNode* root2 = buildTree({1, 2, 3, -1, 4, -1, 5});
        cout << "\nTree Structure:\n";
        printTreeStructure(root2); // 可视化打印
        cout << endl;
    }

    // ========== 测试用例 4: 二维数组/矩阵 ==========
    {
        vector<vector<int>> matrix = {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9}
        };
        cout << "Matrix: "; print(matrix);
        cout << endl;
    }

    // ========== 测试用例 5: 图的邻接表 ==========
    {
        int n = 5;
        vector<vector<int>> edges = {{0,1}, {0,2}, {1,3}, {2,4}};
        auto graph = buildGraph(n, edges);

        cout << "Graph (n=" << n << "):\n";
        for (int i = 0; i < n; ++i) {
            cout << i << ": "; print(graph[i]);
        }
        cout << endl;
    }

    // ========== 测试用例 6: 其他数据结构 ==========
    {
        // Map 测试
        map<string, int> dict = {{"apple", 1}, {"banana", 2}};
        cout << "Map: "; print(dict);

        // Set 测试
        set<int> s = {3, 1, 4, 1, 5, 9};
        cout << "Set: "; print(s);

        // Pair/Vector<Pair> 测试
        vector<pair<int, int>> pairs = {{1,2}, {3,4}};
        cout << "Pairs: "; print(pairs);
        cout << endl;
    }

    // ========== 测试用例 7: 字符串数组 ==========
    {
        vector<string> strs = {"hello", "world", "leetcode"};
        cout << "Strings: "; print(strs);
        cout << endl;
    }

    // ========== 性能测试示例 ==========
    {
        cout << "Performance Test:\n";
        timer.reset();

        // 你的算法代码
        vector<int> largeArray = randomArray(1000000);
        sort(ALL(largeArray));

        timer.show("Sorting 1M elements");
        cout << endl;
    }

    // ========== 批量测试模板 ==========
    {
        vector<pair<vector<int>, int>> testCases = {
            {{1,2,3}, 3},
            {{4,5,6,7}, 4},
            {{}, 0}
        };

        cout << "Batch Testing:\n";
        for (int i = 0; i < SZ(testCases); ++i) {
            auto [input, expected] = testCases[i];
            auto result = sol.solve(input);
            cout << "Case " << i+1 << ": ";
            EXPECT_EQ(result, expected);
        }
    }

    return 0;
}
