# 题解点评 - 64. Minimum Path Sum

## 基本信息

- 日期：2026-06-20
- 主题：动态规划 / 网格路径代价
- 难度：中等
- 本次结果：通过，哨兵边界使用合理
- 对应源码：`src/64.minimum-path-sum.cpp`
- 资料来源：LeetCode 官方题目页 `https://leetcode.cn/problems/minimum-path-sum/` 与本地源码
- 查询日期：2026-06-20

## 用户思路概述

1. 用 `dp[i][j]` 表示到达 `grid[i-1][j-1]` 的最小路径和。
2. 多开一行一列，并把默认值设置为较大数，避免非法来源被选中。
3. 初始化起点 `dp[1][1] = grid[0][0]`。
4. 当前格从上方或左方选择较小路径和，再加上当前格权重。
5. 返回右下角 `dp[m][n]`。

## 用户解法复杂度

- 时间复杂度：`O(m*n)`
- 空间复杂度：`O(m*n)`
- 复杂度来源：二维表中每个位置计算一次。

## 用户代码注释版

```cpp
class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m=grid.size(), n=grid[0].size();
        vector<vector<int>> dp(m+1, vector<int>(n+1, 0x3f3f3f3f)); // 非法边界用大数挡住。
        dp[1][1] = grid[0][0]; // 起点路径和就是自身。
        for(int i=1; i<=m; i++) {
            for(int j=1; j<=n; j++) {
                if(i==1 && j==1) continue;
                dp[i][j] = min(dp[i][j-1], dp[i-1][j]) + grid[i-1][j-1];
            }
        }
        return dp[m][n];
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 状态定义 | `dp` 坐标和 `grid` 坐标错一位 | 正确但需要复盘时讲清 | 写注释时明确 `dp[i][j]` 对应 `grid[i-1][j-1]` |
| 哨兵值 | 用大数处理非法来源 | 首行首列无需单独初始化 | 注意大数加当前值不能溢出 |
| 转移选择 | 从上/左取较小值 | 正确命中最小路径结构 | 和 62 的“累加来源”形成对照 |
| 空间优化 | 使用完整二维表 | 清晰但空间可降 | 当前行只依赖上一行和左侧 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 边界统一，代码短 | 空间为二维表，哨兵语义要说清 | 适合初次写网格最小代价 |
| 推荐最优解 | 一维滚动，空间更低 | 第一列更新需要单独处理 | 提交时更简洁 |

## 最优解法

1. 用 `dp[col]` 表示当前行到达第 `col` 列的最小路径和。
2. `dp[col]` 更新前表示上方来源，`dp[col - 1]` 表示左方来源。
3. 第一列只能从上方下来，所以直接累加。
4. 其他列从上方和左方中取较小值。

- 最优时间复杂度：`O(m*n)`
- 最优空间复杂度：`O(n)`

### 最优解代码

```cpp
class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int rows = static_cast<int>(grid.size());
        int cols = static_cast<int>(grid[0].size());
        vector<int> dp(cols, 0x3f3f3f3f);
        dp[0] = 0;
        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                // dp[col] 是上方代价，dp[col - 1] 是左方代价。
                if (col == 0) {
                    dp[col] += grid[row][col];
                } else {
                    dp[col] = min(dp[col], dp[col - 1]) + grid[row][col];
                }
            }
        }
        return dp[cols - 1];
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | 二维位置最小代价 | 当前行每列最小代价 | 压缩时保持“上方/左方”来源含义 |
| 更新逻辑 | `min(左, 上) + 当前值` | 相同 | 主干正确 |
| 边界处理 | 大数哨兵 + 起点特判 | 第一列直接累加 | 两种边界模型都要会 |
| 复杂度 | `O(m*n)` / `O(m*n)` | `O(m*n)` / `O(n)` | 空间可优化 |

## 下一步建议

建议补两个边界用例：单行网格和单列网格，确认哨兵边界没有误选非法来源。

## 后续练习

1. `120. Triangle` - 把矩形网格迁移到不规则层级结构。
2. `931. Minimum Falling Path Sum` - 练习多个上层来源的最小代价。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/64.minimum-path-sum.cpp`
- 新函数名：`minPathSumOpt`
- 保留用户原实现：是
