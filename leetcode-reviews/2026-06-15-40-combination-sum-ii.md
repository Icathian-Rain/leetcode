# 题解点评 - 40. Combination Sum II

## 基本信息

- 日期：2026-06-15
- 主题：回溯 / 重复元素与目标和去重
- 难度：中等
- 本次结果：待提交验证，源码逻辑检查通过
- 对应源码：`src/40.combination-sum-ii.cpp`
- 资料来源：LeetCode 官方题目页 `https://leetcode.cn/problems/combination-sum-ii/`
- 查询日期：2026-06-15

## 用户思路概述

1. 先排序，让重复候选值相邻。
2. 用 `path` 保存当前组合，用递归参数 `target` 表示剩余目标。
3. 当 `target == 0` 时收集当前路径；当 `target < 0` 时停止。
4. 每层从 `start` 往后选，递归传 `i + 1`，表示每个位置只能使用一次。
5. 使用 `i > start && candidates[i] == candidates[i - 1]` 做同层去重。

## 用户解法复杂度

- 时间复杂度：最坏 `O(n * 2^n)`
- 空间复杂度：`O(n)`，不计返回结果
- 复杂度来源：每个元素最多选或不选，答案复制最坏需要 `O(n)`；排序为 `O(n log n)`。

## 用户代码注释版

```cpp
class Solution {
    vector<vector<int>> ans;
    vector<int> path;

    void bt(vector<int>& candidates, int target, int start) {
        if (target <= 0) {
            if (target == 0) ans.push_back(path); // 剩余目标为 0，当前组合合法。
            return;
        }
        for (int i = start; i < candidates.size(); i++) {
            if (i > start && candidates[i] == candidates[i - 1]) {
                continue; // 同一层跳过重复值，避免重复组合。
            }
            path.push_back(candidates[i]);
            bt(candidates, target - candidates[i], i + 1); // 每个位置只能用一次。
            path.pop_back();
        }
    }

public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        bt(candidates, target, 0);
        return ans;
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 去重方式 | `i > start` 同层去重 | 能避免 `[1,7]` 被不同相同值位置重复生成 | 继续把 `start` 理解成本层边界 |
| 使用次数 | 递归传 `i + 1` | 正确表达每个位置最多使用一次 | 和 `39` 的传 `i` 对比记忆 |
| 剪枝效率 | 没有在候选值超过目标时 `break` | 正确性没问题，但会进入一些必然无解分支 | 排序后补 `if (candidates[i] > target) break` |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 核心回溯和同层去重正确 | 少了排序后的正数剪枝；成员变量复用风险 | 适合本题，效率可再稳一点 |
| 推荐最优解 | 使用 `remain` 更清楚，并在超过剩余目标时提前停止 | 需要注意先排序才可 `break` | 适合组合总和类题模板 |

## 最优解法

1. 排序候选数组。
2. 用 `remain` 表示剩余目标。
3. 同一层跳过重复候选。
4. 当候选值大于 `remain` 时直接结束本层循环。

- 最优时间复杂度：最坏 `O(n * 2^n)`
- 最优空间复杂度：`O(n)`，不计返回结果

### 最优解代码

```cpp
class Solution {
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());

        vector<vector<int>> result;
        vector<int> current;

        function<void(int, int)> dfs = [&](int start, int remain) {
            if (remain == 0) {
                result.push_back(current);
                return;
            }

            for (int i = start; i < static_cast<int>(candidates.size()); ++i) {
                if (i > start && candidates[i] == candidates[i - 1]) {
                    continue; // 同一层跳过重复候选，保证组合唯一。
                }
                if (candidates[i] > remain) {
                    break;
                }
                current.push_back(candidates[i]);
                dfs(i + 1, remain - candidates[i]);
                current.pop_back();
            }
        };

        dfs(0, target);
        return result;
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | `target` 作为剩余目标 | `remain` 语义更直接 | 命名可更贴近状态含义 |
| 更新逻辑 | 传 `i + 1` | 传 `i + 1` | 正确 |
| 边界处理 | 目标小于等于 0 停止 | 目标为 0 收集，超过由排序剪枝阻止 | 增加 `break` |
| 复杂度 | 最坏 `O(n*2^n)` | 最坏 `O(n*2^n)`，常数更好 | 通过剪枝减少无效分支 |

## 下一步建议

建议补测 `[2,5,2,1,2], target=5`，手推同一层为什么只能选择第一个 `2` 作为分支起点。

## 后续练习

1. `491. Non-decreasing Subsequences` - 不允许排序时如何做同层去重。
2. `39. Combination Sum` - 对比“可重复使用”和“每个位置只用一次”。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/40.combination-sum-ii.cpp`
- 新函数名：`combinationSum2Opt`
- 保留用户原实现：是
