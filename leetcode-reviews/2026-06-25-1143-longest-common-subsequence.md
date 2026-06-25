# 题解点评 - 1143. Longest Common Subsequence

## 基本信息

- 日期：2026-06-25
- 主题：动态规划 / 双序列前缀
- 难度：中等
- 本次结果：通过，二维前缀状态标准
- 对应源码：`src/1143.longest-common-subsequence.cpp`
- 资料来源：LeetCode 官方题目页 `https://leetcode.cn/problems/longest-common-subsequence/` 与本地源码
- 查询日期：2026-06-25

## 用户思路概述

1. `dp[i][j]` 表示 `text1` 前 `i` 个字符和 `text2` 前 `j` 个字符的最长公共子序列长度。
2. 如果当前两个字符相同，从左上角转移并加 1。
3. 如果不同，则从去掉其中一个末尾字符的两个状态中取最大值。
4. 返回 `dp[m][n]`。

## 用户解法复杂度

- 时间复杂度：`O(m*n)`
- 空间复杂度：`O(m*n)`

## 用户代码注释版

```cpp
class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int m=text1.length(), n=text2.length();
        vector<vector<int>> dp(m+1, vector<int>(n+1, 0));
        for(int i=1; i<=m; i++) {
            for(int j=1; j<=n; j++) {
                if(text1[i-1] == text2[j-1]) {
                    dp[i][j] = dp[i-1][j-1]+1;
                } else {
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
                }
            }
        }
        return dp[m][n];
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 前缀状态 | `dp[i][j]` 含义准确 | 主干正确 | 这是双序列题的基础 |
| 相等分支 | 左上角加 1 | 正确使用当前字符 | 注意是子序列，不要求连续 |
| 空间优化 | 使用完整二维表 | 清楚但可压缩 | 可练一维滚动保存左上角 |

## 最优解法

推荐在掌握二维表后练一维压缩：`dp[j]` 表示当前行第 `j` 列结果，用 `diagonal` 保存上一行左上角。

- 最优时间复杂度：`O(m*n)`
- 最优空间复杂度：`O(n)`

### 最优解代码

```cpp
class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        vector<int> dp(text2.size() + 1, 0);
        for (int i = 1; i <= static_cast<int>(text1.size()); i++) {
            int diagonal = 0;
            for (int j = 1; j <= static_cast<int>(text2.size()); j++) {
                int up = dp[j];
                if (text1[i - 1] == text2[j - 1]) dp[j] = diagonal + 1;
                else dp[j] = max(dp[j], dp[j - 1]);
                diagonal = up;
            }
        }
        return dp[text2.size()];
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | 二维前缀 | 一维滚动前缀 | 本质相同 |
| 更新逻辑 | 上、左、左上 | 同样来源 | 压缩时保存左上角 |
| 复杂度 | `O(mn)` / `O(mn)` | `O(mn)` / `O(n)` | 空间可优化 |

## 下一步建议

可以进入编辑距离；那道题只是把“不相等”的来源从两个扩展到三个。

## 后续练习

1. `72. Edit Distance` - 在双序列前缀上加入操作代价。
2. `1035. Uncrossed Lines` - 练习同构的 LCS 模型。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/1143.longest-common-subsequence.cpp`
- 新函数名：`longestCommonSubsequenceOpt`
- 保留用户原实现：是
