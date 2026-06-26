# 题解点评 - 312. Burst Balloons

## 基本信息

- 日期：2026-06-26
- 主题：动态规划 / 区间状态
- 难度：困难
- 本次结果：通过，区间“最后戳”建模正确
- 对应源码：`src/312.burst-balloons.cpp`
- 资料来源：LeetCode 官方题目页 `https://leetcode.cn/problems/burst-balloons/` 与本地源码
- 查询日期：2026-06-26

## 用户思路概述

1. 在数组两端补 1，方便处理边界气球。
2. `dfs(left, right)` 表示开区间 `(left, right)` 内所有气球被戳破后能获得的最大硬币。
3. 枚举区间内最后一个被戳破的气球 `i`。
4. 此时它的左右相邻气球固定为 `left` 和 `right`。
5. 递归求左右子区间，并用记忆化避免重复计算。

## 用户解法复杂度

- 时间复杂度：`O(n^3)`
- 空间复杂度：`O(n^2)`

## 用户代码注释版

```cpp
class Solution {
public:
    int maxCoins(vector<int>& nums) {
        int n=nums.size();
        vector<int> val(n+2, 0);
        vector<vector<int>> mem(n+2, vector<int>(n+2, -1));
        for(int i=1; i<=n; i++) val[i] = nums[i-1];
        val[0] = val[n+1] = 1;

        function<int(int, int)> dfs = [&](int left, int right) -> int {
            if(left >= right-1) return 0; // 开区间为空。
            if(mem[left][right] != -1) return mem[left][right];
            for(int i=left+1; i<right; i++) {
                int sum=val[left]*val[i]*val[right]; // i 是最后戳的气球。
                sum += dfs(left, i) + dfs(i, right);
                mem[left][right] = max(mem[left][right], sum);
            }
            return mem[left][right];
        };
        return dfs(0, n+1);
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 区间定义 | 开区间 `(left, right)` | 正确避开边界变化 | 这是本题核心 |
| 最后戳 | 枚举最后一个气球 | 正确固定左右邻居 | 比“第一个戳”更容易建模 |
| 记忆化 | `mem[left][right]` | 避免指数重复 | 正确 |
| 写法形态 | 自顶向下 DFS | 清晰 | 可再练自底向上 |

## 最优解法

自底向上写法和你的记忆化等价：按区间长度从短到长填表，枚举最后戳的气球。

- 最优时间复杂度：`O(n^3)`
- 最优空间复杂度：`O(n^2)`

### 最优解代码

```cpp
class Solution {
public:
    int maxCoins(vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        vector<int> values(n + 2, 1);
        for (int i = 1; i <= n; i++) values[i] = nums[i - 1];

        vector<vector<int>> dp(n + 2, vector<int>(n + 2, 0));
        for (int len = 2; len <= n + 1; len++) {
            for (int left = 0; left + len <= n + 1; left++) {
                int right = left + len;
                for (int last = left + 1; last < right; last++) {
                    // last 是开区间 (left, right) 中最后被戳破的气球。
                    dp[left][right] = max(dp[left][right],
                        dp[left][last] + dp[last][right] + values[left] * values[last] * values[right]);
                }
            }
        }
        return dp[0][n + 1];
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | 开区间记忆化 | 开区间二维表 | 本质相同 |
| 更新逻辑 | 枚举最后戳 | 枚举最后戳 | 正确 |
| 边界处理 | 两端补 1 | 相同 | 正确 |
| 复杂度 | `O(n^3)` / `O(n^2)` | `O(n^3)` / `O(n^2)` | 形态可互换 |

## 下一步建议

这题完成得很好。建议把“为什么枚举最后戳，而不是第一个戳”写进复盘，这是区间 DP 的关键迁移点。

## 后续练习

1. `1039. Minimum Score Triangulation of Polygon` - 同类区间切分。
2. `516. Longest Palindromic Subsequence` - 练习另一种区间状态。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/312.burst-balloons.cpp`
- 新函数名：`maxCoinsOpt`
- 保留用户原实现：是
