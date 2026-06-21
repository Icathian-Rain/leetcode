# 题解点评 - 790. Domino and Tromino Tiling

## 基本信息

- 日期：2026-06-21
- 主题：动态规划 / 轮廓状态
- 难度：中等
- 本次结果：通过，状态转移正确但命名可读性偏弱
- 对应源码：`src/790.domino-and-tromino-tiling.cpp`
- 资料来源：LeetCode 官方题目页 `https://leetcode.cn/problems/domino-and-tromino-tiling/` 与本地源码
- 查询日期：2026-06-21

## 用户思路概述

1. 用 4 个状态表示当前列的铺砖轮廓。
2. 初始时认为第 0 列之前是完整状态。
3. 每推进一列，重新计算四种轮廓状态。
4. 每个状态都对 `1e9 + 7` 取模。
5. 最后返回铺满状态。

## 用户解法复杂度

- 时间复杂度：`O(n)`
- 空间复杂度：`O(1)`
- 复杂度来源：每列只更新 4 个状态。

## 用户代码注释版

```cpp
const int MOD=1e9+7;
using ll = long long;
class Solution {
public:
    int numTilings(int n) {
        vector<ll> dp(4, 0);
        dp[0]=0;
        dp[1]=0;
        dp[2]=0;
        dp[3]=1; // 初始完整轮廓。
        for(int i=1; i<=n; i++) {
            vector<ll> tmp(4, 0);
            tmp[0] = dp[3];
            tmp[1] = (dp[0] + dp[2]) % MOD;
            tmp[2] = (dp[0] + dp[1]) % MOD;
            tmp[3] = (dp[0] + dp[1] + dp[2] + dp[3]) % MOD;
            dp.swap(tmp);
        }
        return dp[3]; // 铺满状态。
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 多状态建模 | 维护 4 种轮廓状态 | 正确覆盖多米诺和托米诺带来的缺口 | 这是本题核心能力 |
| 取模处理 | 每次转移都取模 | 避免数值溢出 | 保持 `long long` 中间值 |
| 状态命名 | 使用 `dp[0..3]` | 代码短，但复盘时难解释 | 给 4 个状态起语义名 |
| 初始化 | `dp[3] = 1` | 正确表示空板已铺满 | 需要能口头说明这个“完整状态” |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 转移正确，空间已经是常数 | 状态编号不直观 | 能提交，但复盘成本高 |
| 推荐最优解 | 用语义变量解释四种轮廓 | 代码略长 | 更适合学习状态拆分 |

## 最优解法

1. 把每一列的轮廓拆成 4 种：空、上缺、下缺、完整。
2. 每次推进一列，根据上一列轮廓计算下一列轮廓。
3. 只保存当前列 4 个状态。
4. 返回完整铺满状态。

- 最优时间复杂度：`O(n)`
- 最优空间复杂度：`O(1)`

### 最优解代码

```cpp
class Solution {
public:
    int numTilings(int n) {
        const int MOD = 1'000'000'007;
        long long empty = 1;
        long long topMissing = 0;
        long long bottomMissing = 0;
        long long full = 0;
        for (int col = 1; col <= n; col++) {
            // 四个状态分别表示当前列轮廓：空、上缺、下缺、已铺满。
            long long nextEmpty = full;
            long long nextTopMissing = (empty + bottomMissing) % MOD;
            long long nextBottomMissing = (empty + topMissing) % MOD;
            long long nextFull = (empty + topMissing + bottomMissing + full) % MOD;
            empty = nextEmpty;
            topMissing = nextTopMissing;
            bottomMissing = nextBottomMissing;
            full = nextFull;
        }
        return static_cast<int>(full);
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | `dp[0..3]` | 四个语义变量 | 优先让状态可解释 |
| 更新逻辑 | 4 个编号状态一起转移 | 4 个命名状态一起转移 | 转移本质相同 |
| 边界处理 | `dp[3] = 1` | `empty = 1` | 说清空板初始状态 |
| 复杂度 | `O(n)` / `O(1)` | `O(n)` / `O(1)` | 已经最优 |

## 下一步建议

建议重画 `n = 1`、`n = 2` 的四状态流转图。代码是对的，下一步是让每个状态编号都能被你自然解释。

## 后续练习

1. `552. Student Attendance Record II` - 继续练习多个状态维度的计数。
2. `309. Best Time to Buy and Sell Stock with Cooldown` - 练习用多个状态表达同一天的不同行为。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/790.domino-and-tromino-tiling.cpp`
- 新函数名：`numTilingsOpt`
- 保留用户原实现：是
