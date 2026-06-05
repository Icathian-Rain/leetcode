# 题解点评 - 39. Combination Sum

## 基本信息

- 日期：2026-06-05
- 主题：回溯 / 可重复选择的组合边界
- 难度：中等
- 本次结果：有主要风险，核心递归方向正确
- 对应源码：`src/39.combination-sum.cpp`
- 资料来源：LeetCode 官方题目页 `https://leetcode.cn/problems/combination-sum/`
- 查询日期：2026-06-05

## 用户思路概述

1. 用 `path` 保存当前组合，用 `sum` 保存当前组合和。
2. `dfs(candidates, target, start)` 从 `start` 开始枚举候选数字，避免生成同一组合的不同排列。
3. 选择 `candidates[i]` 后递归调用 `dfs(..., i)`，表示当前数字可以继续被重复选择。
4. 当 `sum >= target` 时停止继续向下；如果刚好等于目标，就收集当前路径。

## 用户解法复杂度

- 时间复杂度：接近 `O(N^(target / min(candidates)))`，实际受目标值、候选数和剪枝影响
- 空间复杂度：`O(target / min(candidates))`，不计返回结果
- 复杂度来源：每层可以继续选择多个候选数，路径最长由最小候选数重复凑到 `target` 的次数决定。

## 用户代码注释版

```cpp
class Solution {
public:
    vector<vector<int>> ans;
    vector<int> path;
    int sum; // 风险点：没有初始化，第一次进入 dfs 时值不稳定。

    void dfs(vector<int>& candidates, int target, int start) {
        if (sum >= target) {
            if (sum == target) ans.push_back(path); // 当前组合正好达到目标。
            return;
        }

        for (int i = start; i < candidates.size(); i++) {
            path.push_back(candidates[i]);
            sum += candidates[i];
            dfs(candidates, target, i); // 继续从 i 开始，允许当前数字重复使用。
            sum -= candidates[i];
            path.pop_back();
        }
    }

    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        dfs(candidates, target, 0);
        return ans;
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 可重复选择 | 递归传 `i` 而不是 `i + 1` | 正确表达同一个数可以重复使用 | 这是本题和 216 的关键差异，值得记住 |
| 去重顺序 | 每层从 `start` 往后选 | 能避免 `[2,2,3]` 和 `[2,3,2]` 重复出现 | 组合总和类题继续保持非降序路径 |
| 当前和状态 | 使用成员变量 `sum` | 未初始化会导致错误答案或不稳定行为 | 改用 `remain` 参数更稳 |
| 剪枝效率 | 没有排序，无法在本层提前 `break` | 当候选较多时会尝试更多无效分支 | 先排序，再用 `candidate > remain` 停止 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 能抓住“可重复选”和“保持顺序去重” | `sum` 未初始化；未排序导致剪枝不充分 | 适合小规模，但稳定性要补 |
| 推荐最优解 | 剩余目标清楚，排序后可提前停止 | 会改变 `candidates` 顺序，但题目允许任意顺序返回 | 适合本题和一类组合总和题 |

## 最优解法

1. 先对 `candidates` 排序，使超过剩余目标的候选可以直接停止本层循环。
2. 递归参数使用 `start` 和 `remain`，分别表示当前可选起点和剩余目标。
3. 当 `remain == 0` 时收集答案。
4. 递归时仍传入 `i`，表示当前候选数字可以重复使用。

- 最优时间复杂度：输出敏感，常写作 `O(S)`，其中 `S` 为搜索树规模与答案复制成本
- 最优空间复杂度：`O(target / min(candidates))`，不计返回结果

### 最优解代码

```cpp
class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());

        vector<vector<int>> result;
        vector<int> path;

        function<void(int, int)> dfs = [&](int start, int remain) {
            if (remain == 0) {
                result.push_back(path);
                return;
            }

            for (int i = start; i < static_cast<int>(candidates.size()); ++i) {
                if (candidates[i] > remain) {
                    break;
                }
                path.push_back(candidates[i]);
                dfs(i, remain - candidates[i]); // 仍从 i 开始，表示当前数字可重复使用。
                path.pop_back();
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
| 状态定义 | `sum` 表示当前和 | `remain` 表示还差多少 | 终止条件更直接，避免成员变量初始化问题 |
| 更新逻辑 | 加当前值，返回后减当前值 | 递归传剩余目标，路径只负责答案内容 | 把数值状态交给参数 |
| 边界处理 | 达到或超过目标后返回 | 达到目标收集；超过目标由排序剪枝阻止 | 让无效分支更早停 |
| 复杂度 | 搜索树偏大 | 排序后减少无效分支 | 提升常数和可解释性 |

## 下一步建议

建议补边界测试：`candidates=[2], target=1`、`candidates=[2,3,5], target=8`、`candidates=[7,3,2], target=7`。这三组能同时检查空答案、重复使用和排序剪枝。

## 后续练习

1. `40. Combination Sum II` - 从“可重复选”切到“每个位置最多选一次”。
2. `90. Subsets II` - 专门练习重复输入下的结果唯一性。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/39.combination-sum.cpp`
- 新函数名：`combinationSumOpt`
- 保留用户原实现：是
