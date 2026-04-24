/*
 * @lc app=leetcode.cn id=XXX lang=cpp
 * [XXX] 题目名称
 */
#include "../header.h"
int testcase = 0;
// @lc code=start
#ifdef LOCAL
    #define DEBUG(x) cout << #x << ": " << x << endl
#else
    #define DEBUG(x)
#endif

class Solution {
public:
    int solve(vector<int>& nums) {
        // 核心算法
        DEBUG(nums.size());
        return 0;
    }
};
// @lc code=end

// 使用模板支持不同类型的返回值和参数
template <typename T, typename U>
void test(T&& input, U expected) {
    cout << "============ Test Case " << ++testcase << " =================" << endl;
    print(input);

    Solution sol;
    // 拷贝一份数据用于测试，避免干扰计时
    auto data = input; 
    Timer timer;
    auto result = sol.solve(data);
    timer.show("Execution Time");

    // 格式化输出方便对齐
    cout << "Result: ";
    print(result);

    cout << "Expected: ";
    print(expected);
    // 建议在 EXPECT_EQ 失败时打印出具体输入，方便回溯
    if (result != expected) {
        cout << " [!] Test Case Failed!" << endl;
    } else {
        cout << " [✓] Test Case Passed!" << endl;
    }
    cout << endl;
}

int main() {
    // 针对大数据的输入测试
    test(vector<int>{1, 2, 3}, 0);
    test(vector<int>{4, 5, 6}, 1);

    return 0;
}