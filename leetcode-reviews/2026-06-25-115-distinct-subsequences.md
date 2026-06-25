# 题解点评 - 115. Distinct Subsequences

## 基本信息

- 日期：2026-06-25
- 主题：动态规划 / 双序列方案计数
- 难度：困难
- 本次结果：通过，后缀状态写法正确
- 对应源码：`src/115.distinct-subsequences.cpp`
- 资料来源：LeetCode 官方题目页 `https://leetcode.cn/problems/distinct-subsequences/` 与本地源码
- 查询日期：2026-06-25

## 用户思路概述

1. `dp[i][j]` 表示 `s[i..]` 形成 `t[j..]` 的方案数。
2. 当 `j == n` 时，目标串已经匹配完，任意 `s[i..]` 都有一种方案。
3. 从后往前填表。
4. 如果 `s[i] == t[j]`，可以选择匹配当前字符，也可以跳过当前字符。
5. 如果不相等，只能跳过 `s[i]`。

## 用户解法复杂度

- 时间复杂度：`O(m*n)`
- 空间复杂度：`O(m*n)`

## 用户代码注释版

```cpp
using ull = unsigned long long;
class Solution {
public:
    int numDistinct(string s, string t) {
        int m=s.length(), n=t.length();
        vector<vector<ull>> dp(m+1, vector<ull>(n+1, 0));
        for(int i=0; i<=m; i++) {
            dp[i][n] = 1; // 空目标串有一种匹配方式。
        }
        for(int i=m-1; i>=0; i--) {
            for(int j=n-1; j>=0; j--) {
                if(s[i] == t[j]) {
                    dp[i][j] = dp[i+1][j+1] + dp[i+1][j];
                } else {
                    dp[i][j] = dp[i+1][j];
                }
            }
        }
        return dp[0][0];
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 后缀状态 | `s[i..]` 到 `t[j..]` | 正确且自然 | 很适合本题 |
| 空目标串 | `dp[i][n] = 1` | 正确 | 计数边界抓得稳 |
| 数值类型 | 使用 `unsigned long long` | 避免中间计数过大 | 返回前转 `int` 即可 |
| 空间优化 | 二维表 | 清晰但可压缩 | 可练一维倒序 |

## 最优解法

一维写法中，`dp[j]` 表示已处理 `s` 前缀形成 `t` 前 `j` 个字符的方案数；内层倒序，避免同一个 `s[i]` 被重复使用。

- 最优时间复杂度：`O(m*n)`
- 最优空间复杂度：`O(n)`

### 最优解代码

```cpp
class Solution {
public:
    int numDistinct(string s, string t) {
        vector<unsigned long long> dp(t.size() + 1, 0);
        dp[0] = 1;
        for (int i = 1; i <= static_cast<int>(s.size()); i++) {
            for (int j = static_cast<int>(t.size()); j >= 1; j--) {
                // 倒序避免同一个 s[i - 1] 在本轮被重复使用。
                if (s[i - 1] == t[j - 1]) dp[j] += dp[j - 1];
            }
        }
        return static_cast<int>(dp[t.size()]);
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | 后缀二维计数 | 前缀一维计数 | 两种都成立 |
| 更新逻辑 | 匹配或跳过 | 倒序累加 | 空间压缩 |
| 边界处理 | 空目标串为 1 | `dp[0] = 1` | 语义对应 |
| 复杂度 | `O(mn)` / `O(mn)` | `O(mn)` / `O(n)` | 空间可优化 |

## 下一步建议

这题完成得很稳。建议把“后缀二维”和“前缀一维”都手推一遍 `rabbbit -> rabbit` 的前两层，确认两个状态方向等价。

## 后续练习

1. `1143. Longest Common Subsequence` - 对照双序列最大长度。
2. `392. Is Subsequence` - 回到判断型子序列基础题。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/115.distinct-subsequences.cpp`
- 新函数名：`numDistinctOpt`
- 保留用户原实现：是
