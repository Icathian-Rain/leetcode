# 题解点评 - 72. Edit Distance

## 基本信息

- 日期：2026-06-25
- 主题：动态规划 / 双序列操作代价
- 难度：困难
- 本次结果：通过，初始化和三来源转移完整
- 对应源码：`src/72.edit-distance.cpp`
- 资料来源：LeetCode 官方题目页 `https://leetcode.cn/problems/edit-distance/` 与本地源码
- 查询日期：2026-06-25

## 用户思路概述

1. `dp[i][j]` 表示 `word1` 前 `i` 个字符变成 `word2` 前 `j` 个字符的最少操作数。
2. 空串到前缀需要连续插入或删除，所以初始化首行首列。
3. 当前字符相同则沿用左上角。
4. 当前字符不同，则从删除、插入、替换三种来源中取最小值再加 1。

## 用户解法复杂度

- 时间复杂度：`O(m*n)`
- 空间复杂度：`O(m*n)`

## 用户代码注释版

```cpp
class Solution {
public:
    int minDistance(string word1, string word2) {
        int m=word1.size(), n=word2.size();
        vector<vector<int>> dp(m+1, vector<int>(n+1, 0));
        for(int i=0; i<=m; i++) dp[i][0] = i;
        for(int j=0; j<=n; j++) dp[0][j] = j;
        for(int i=1; i<=m; i++) {
            for(int j=1; j<=n; j++) {
                if(word1[i-1] == word2[j-1]) dp[i][j] = dp[i-1][j-1];
                else dp[i][j] = min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]})+1;
            }
        }
        return dp[m][n];
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 空前缀初始化 | 首行首列完整 | 正确覆盖空串边界 | 这是编辑距离的关键边界 |
| 操作来源 | 删除、插入、替换三来源 | 正确 | 复盘时把每个来源对应的操作说清 |
| 空间优化 | 完整二维表 | 易懂但空间可降 | 可练一维滚动 |

## 最优解法

二维写法已经是标准解；空间优化时用一维数组保存当前行，并用 `diagonal` 记录左上角。

- 最优时间复杂度：`O(m*n)`
- 最优空间复杂度：`O(n)`

### 最优解代码

```cpp
class Solution {
public:
    int minDistance(string word1, string word2) {
        int m = static_cast<int>(word1.size());
        int n = static_cast<int>(word2.size());
        vector<int> dp(n + 1);
        for (int j = 0; j <= n; j++) dp[j] = j;
        for (int i = 1; i <= m; i++) {
            int diagonal = dp[0];
            dp[0] = i;
            for (int j = 1; j <= n; j++) {
                int up = dp[j];
                if (word1[i - 1] == word2[j - 1]) dp[j] = diagonal;
                else dp[j] = min({up, dp[j - 1], diagonal}) + 1;
                diagonal = up;
            }
        }
        return dp[n];
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | 二维前缀最少操作 | 一维滚动前缀 | 来源不变 |
| 更新逻辑 | 三来源取最小 | 三来源取最小 | 压缩时保存上、左、左上 |
| 复杂度 | `O(mn)` / `O(mn)` | `O(mn)` / `O(n)` | 空间可优化 |

## 下一步建议

当前题完成得稳。建议复盘时画一个 `horse -> ros` 的小表，确认三种操作来源和坐标方向。

## 后续练习

1. `1143. Longest Common Subsequence` - 对照双序列前缀的无代价版本。
2. `583. Delete Operation for Two Strings` - 练习编辑距离的变体。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/72.edit-distance.cpp`
- 新函数名：`minDistanceOpt`
- 保留用户原实现：是
