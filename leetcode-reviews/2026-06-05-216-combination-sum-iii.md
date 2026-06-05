# 题解点评 - 216. Combination Sum III

## 基本信息

- 日期：2026-06-05
- 主题：回溯 / 固定长度与目标和
- 难度：中等
- 本次结果：有主要风险，递归主体思路正确
- 对应源码：`src/216.combination-sum-iii.cpp`
- 资料来源：LeetCode 官方题目页 `https://leetcode.cn/problems/combination-sum-iii/`
- 查询日期：2026-06-05

## 用户思路概述

1. 用 `path` 保存当前选择的数字，用 `sum` 记录当前路径和。
2. `dfs(k, n, start)` 每层从 `start` 到 9 继续选择，递归时传入 `i + 1`，保证每个数字最多使用一次。
3. 当 `path.size() == k && sum == n` 时收集答案。
4. 当长度已经达到 `k` 或当前和已经不小于目标时停止继续搜索。
5. 入口处用最小可能和 `k * (k + 1) / 2` 做了一个提前返回。

## 用户解法复杂度

- 时间复杂度：`O(C(9, k) * k)`
- 空间复杂度：`O(k)`，不计返回结果
- 复杂度来源：最多枚举从 1 到 9 中选择 `k` 个数的所有组合，复制答案时需要路径长度。

## 用户代码注释版

```cpp
class Solution {
public:
    vector<vector<int>> ans;
    vector<int> path;
    int sum; // 风险点：成员变量没有显式初始化，进入 dfs 前值不稳定。

    void dfs(int k, int n, int start) {
        if (path.size() == k && sum == n) {
            ans.push_back(path); // 数量和目标和同时满足，收集答案。
        }
        if (path.size() == k || sum >= n) {
            return; // 数量满了，或当前和已经不可能继续变小。
        }

        int need = k - path.size();
        for (int i = start; i <= n - need + 1 && i <= 9; i++) {
            path.push_back(i);
            sum += i;
            dfs(k, n, i + 1); // 下一层只能选择更大的数，保证不重复使用。
            path.pop_back();
            sum -= i;
        }
    }

    vector<vector<int>> combinationSum3(int k, int n) {
        if (k * (k + 1) / 2 > n) return ans;
        dfs(k, n, 1);
        return ans;
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 数字使用限制 | 递归传 `i + 1` | 正确保证每个数字最多使用一次 | 继续保持“组合向后选”的模型 |
| 当前和状态 | 用成员变量 `sum` 累加和撤销 | 思路对，但未初始化会造成不确定行为 | 用递归参数 `remain` 代替成员 `sum` |
| 循环上界 | 写成 `i <= n - need + 1 && i <= 9` | `n` 是目标和，不是可选范围上界，剪枝语义不够准 | 对本题数量剪枝应围绕 1 到 9 的剩余个数 |
| 剪枝完整性 | 只检查最小可能和 | 对极大目标可继续做无效搜索 | 可补最大可能和或用 `remain` 提前停止 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 主干回溯动作完整，能同时检查数量和目标 | `sum` 未初始化；循环上界把目标和和数值范围混在一起 | 思路适合本题，但实现需要修稳 |
| 推荐最优解 | 用 `remain` 表示剩余目标，状态局部化，边界更清楚 | 需要习惯把“当前和”反过来写成“剩余和” | 适合固定数量、固定范围、目标和组合题 |

## 最优解法

1. 递归参数使用 `start`、`left`、`remain`，分别表示下一次起点、还要选几个数、还差多少和。
2. 当 `left == 0` 时，只在 `remain == 0` 时收集答案。
3. 循环上界写成 `10 - left`，确保后面还有足够数字可选。
4. 因为数字递增且全为正数，当当前数字已经大于 `remain` 时直接停止本层循环。

- 最优时间复杂度：`O(C(9, k) * k)`
- 最优空间复杂度：`O(k)`，不计返回结果

### 最优解代码

```cpp
class Solution {
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<vector<int>> result;
        vector<int> path;

        function<void(int, int, int)> dfs = [&](int start, int left, int remain) {
            if (left == 0) {
                if (remain == 0) {
                    result.push_back(path);
                }
                return;
            }

            // 还需要 left 个数时，起点不能超过 10 - left，否则数量不够。
            for (int value = start; value <= 10 - left; ++value) {
                if (value > remain) {
                    break;
                }
                path.push_back(value);
                dfs(value + 1, left - 1, remain - value);
                path.pop_back();
            }
        };

        dfs(1, k, n);
        return result;
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | `sum` 记录当前路径和 | `remain` 记录剩余目标 | 避免未初始化成员变量 |
| 更新逻辑 | 选择后加，撤销时减 | 递归传 `remain - value` | 让终止条件更直接 |
| 边界处理 | 长度满或和超出时停止 | 数量为 0 时统一判断目标；循环保证剩余数量足够 | 区分“数字范围”和“目标和” |
| 复杂度 | `O(C(9,k)*k)` | `O(C(9,k)*k)` | 数量级相同，稳定性更好 |

## 下一步建议

建议重写当前题一次，把 `sum` 改成 `remain` 参数。你现在已经掌握了选择和撤销，下一步要练的是“多个约束分别由哪个参数负责”。

## 后续练习

1. `39. Combination Sum` - 观察“允许重复选择”时递归起点如何变化。
2. `40. Combination Sum II` - 继续练习目标和组合，同时处理重复输入。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/216.combination-sum-iii.cpp`
- 新函数名：`combinationSum3Opt`
- 保留用户原实现：是
