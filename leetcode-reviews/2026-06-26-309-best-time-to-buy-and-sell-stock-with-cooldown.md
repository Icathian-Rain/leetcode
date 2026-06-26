# 题解点评 - 309. Best Time to Buy and Sell Stock with Cooldown

## 基本信息

- 日期：2026-06-26
- 主题：动态规划 / 多行为状态
- 难度：中等
- 本次结果：通过，状态拆分完整
- 对应源码：`src/309.best-time-to-buy-and-sell-stock-with-cooldown.cpp`
- 资料来源：LeetCode 官方题目页 `https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-with-cooldown/` 与本地源码
- 查询日期：2026-06-26

## 用户思路概述

1. 用 4 个状态表达当天买入/持有、保持不持有、卖出、冷冻期。
2. `dp[i][0]` 表示第 `i` 天结束后持有股票的最大收益。
3. `dp[i][2]` 表示当天卖出后的收益。
4. `dp[i][3]` 表示由前一天卖出进入冷冻期。
5. 最后从不持有股票的状态里取最大值。

## 用户解法复杂度

- 时间复杂度：`O(n)`
- 空间复杂度：`O(n)`

## 用户代码注释版

```cpp
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n=prices.size();
        vector<vector<int>> dp(n, vector<int>(4, 0));
        // dp[i][0]: 持有股票
        // dp[i][1]: 不持有且可买入
        // dp[i][2]: 当天卖出
        // dp[i][3]: 冷冻期
        dp[0][0] = -prices[0];
        for(int i=1; i<n; i++) {
            dp[i][0] = max(dp[i-1][0], max(dp[i-1][3], dp[i-1][1]) - prices[i]);
            dp[i][1] = max({dp[i-1][1], dp[i-1][3]});
            dp[i][2] = dp[i-1][0]+prices[i];
            dp[i][3] = dp[i-1][2];
        }
        return max({dp[n-1][1], dp[n-1][2], dp[n-1][3]});
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 状态拆分 | 持有、休息、卖出、冷冻 | 能表达冷冻限制 | 状态设计正确 |
| 买入来源 | 从休息或冷冻后状态买入 | 逻辑可行 | 可合并成 3 状态，更简洁 |
| 空间优化 | 使用二维表 | 清楚但可压缩 | 只依赖前一天 |

## 最优解法

用 3 个滚动状态即可：`hold` 持有，`sold` 今天卖出，`rest` 不持有且不处于今天卖出。

- 最优时间复杂度：`O(n)`
- 最优空间复杂度：`O(1)`

### 最优解代码

```cpp
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int hold = -prices[0];
        int rest = 0;
        int sold = 0;
        for (int i = 1; i < static_cast<int>(prices.size()); i++) {
            int prevHold = hold;
            int prevRest = rest;
            int prevSold = sold;
            // 买入只能来自非冷冻的休息状态，卖出会进入当天卖出状态。
            hold = max(prevHold, prevRest - prices[i]);
            sold = prevHold + prices[i];
            rest = max(prevRest, prevSold);
        }
        return max(rest, sold);
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | 4 个显式状态 | 3 个滚动状态 | 可合并等价状态 |
| 更新逻辑 | 依赖前一天 | 相同 | 正确 |
| 边界处理 | `dp[0][0] = -prices[0]` | `hold = -prices[0]` | 相同 |
| 复杂度 | `O(n)` / `O(n)` | `O(n)` / `O(1)` | 空间可优化 |

## 下一步建议

复盘时把每个状态画成节点，箭头标出允许的行为。股票 DP 最怕的是状态名模糊。

## 后续练习

1. `714. Best Time to Buy and Sell Stock with Transaction Fee` - 对照带手续费状态。
2. `790. Domino and Tromino Tiling` - 回看多状态计数的状态命名。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/309.best-time-to-buy-and-sell-stock-with-cooldown.cpp`
- 新函数名：`maxProfitOpt`
- 保留用户原实现：是
