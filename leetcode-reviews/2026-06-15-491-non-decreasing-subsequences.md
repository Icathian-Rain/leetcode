# 题解点评 - 491. Non-decreasing Subsequences

## 基本信息

- 日期：2026-06-15
- 主题：回溯 / 不排序条件下的同层去重
- 难度：中等
- 本次结果：待提交验证，源码逻辑检查通过
- 对应源码：`src/491.non-decreasing-subsequences.cpp`
- 资料来源：LeetCode 官方题目页 `https://leetcode.cn/problems/non-decreasing-subsequences/`
- 查询日期：2026-06-15

## 用户思路概述

1. 用 `path` 保存当前子序列。
2. 当 `path.size() >= 2` 时收集答案。
3. 每层从 `start` 向后选择元素，保证子序列保持原数组顺序。
4. 用当前层的 `unordered_set<int> used` 记录本层已经尝试过的数值，避免重复分支。
5. 只有当 `path` 为空或 `nums[i] >= path.back()` 时，才允许继续扩展。

## 用户解法复杂度

- 时间复杂度：最坏 `O(n * 2^n)`
- 空间复杂度：`O(n)`，不计返回结果
- 复杂度来源：最坏情况下枚举大量子序列，每个结果复制路径；递归深度为 `n`，每层有一个局部去重集合。

## 用户代码注释版

```cpp
class Solution {
    vector<vector<int>> ans;
    vector<int> path;

    void bt(vector<int>& nums, int start) {
        if (path.size() >= 2) {
            ans.push_back(path); // 长度至少为 2 的非递减路径是合法答案。
        }

        unordered_set<int> used; // 只记录当前层已经作为分支起点的数值。
        for (int i = start; i < nums.size(); i++) {
            if (used.count(nums[i])) continue;
            if (path.size() == 0 || nums[i] >= path.back()) {
                used.insert(nums[i]);
                path.push_back(nums[i]);
                bt(nums, i + 1);
                path.pop_back();
            }
        }
    }

public:
    vector<vector<int>> findSubsequences(vector<int>& nums) {
        bt(nums, 0);
        return ans;
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 原顺序约束 | 没有排序，递归传 `i + 1` | 正确保留子序列的原数组顺序 | 这题不能像 `90/40` 一样先排序 |
| 合法性约束 | 检查 `nums[i] >= path.back()` | 正确保住非递减条件 | 可以先判断合法性，再插入本层集合 |
| 同层去重 | 每层新建 `unordered_set` | 正确避免同一层重复选择相同值 | 重点记住集合是“本层”的，不是全局的 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 正确区分不能排序的场景，局部去重写得稳 | 成员变量复用风险；插入集合的位置可更集中 | 适合本题 |
| 推荐最优解 | 状态局部化，并把重复与合法性判断拆开 | 仍然是指数枚举，无法避免输出规模 | 适合不排序的子序列去重题 |

## 最优解法

1. 不排序，保持原数组顺序。
2. 每层用一个局部集合记录已经尝试过的数值。
3. 跳过本层重复值；再跳过会破坏非递减关系的值。
4. 长度达到 2 后即可收集当前路径。

- 最优时间复杂度：最坏 `O(n * 2^n)`
- 最优空间复杂度：`O(n)`，不计返回结果

### 最优解代码

```cpp
class Solution {
public:
    vector<vector<int>> findSubsequences(vector<int>& nums) {
        vector<vector<int>> result;
        vector<int> current;

        function<void(int)> dfs = [&](int start) {
            if (current.size() >= 2) {
                result.push_back(current);
            }

            unordered_set<int> usedThisLevel;
            for (int i = start; i < static_cast<int>(nums.size()); ++i) {
                if (usedThisLevel.count(nums[i])) {
                    continue; // 同一层相同数值只作为一次分支起点。
                }
                if (!current.empty() && nums[i] < current.back()) {
                    continue;
                }
                usedThisLevel.insert(nums[i]);
                current.push_back(nums[i]);
                dfs(i + 1);
                current.pop_back();
            }
        };

        dfs(0);
        return result;
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | 成员变量 | 局部变量 | 减少调用残留 |
| 更新逻辑 | 选择、递归、撤销完整 | 相同 | 主干正确 |
| 边界处理 | 本层集合去重，保留原顺序 | 相同 | 继续巩固不能排序的原因 |
| 复杂度 | 最坏 `O(n*2^n)` | 最坏 `O(n*2^n)` | 输出规模决定 |

## 下一步建议

建议把 `90/40/491` 放在一起复盘：前两题可以排序后用相邻元素去重，`491` 不能排序，所以要用“每层集合”去重。

## 后续练习

1. `40. Combination Sum II` - 对比可排序去重。
2. `47. Permutations II` - 对比排列题的 `used` 去重。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/491.non-decreasing-subsequences.cpp`
- 新函数名：`findSubsequencesOpt`
- 保留用户原实现：是
