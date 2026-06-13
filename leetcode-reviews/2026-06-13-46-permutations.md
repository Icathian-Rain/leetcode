# 题解点评 - 46. Permutations

## 基本信息

- 日期：2026-06-13
- 主题：回溯 / 排列与使用状态
- 难度：中等
- 本次结果：待提交验证，源码逻辑检查通过
- 对应源码：`src/46.permutations.cpp`
- 资料来源：LeetCode 官方题目页 `https://leetcode.cn/problems/permutations/`
- 查询日期：2026-06-13

## 用户思路概述

1. 用 `path` 保存当前排列前缀，用 `ans` 保存完整排列。
2. 用 `used[i]` 标记 `nums[i]` 是否已经进入当前路径。
3. 每一层遍历所有下标，选择还没用过的元素，递归结束后撤销路径和使用状态。
4. 当 `path.size() == nums.size()` 时，当前路径就是一个完整排列，加入答案。

## 用户解法复杂度

- 时间复杂度：`O(n * n!)`
- 空间复杂度：`O(n)`，不计返回结果
- 复杂度来源：共有 `n!` 个排列，每个排列复制到答案需要 `O(n)`；递归深度和路径长度为 `n`。

## 用户代码注释版

```cpp
class Solution {
public:
    vector<vector<int>> ans;
    vector<int> path;
    vector<int> used;

    void backtrace(vector<int>& nums) {
        if (path.size() == nums.size()) {
            ans.push_back(path); // 路径长度等于数组长度，得到一个完整排列。
            return;
        }

        for (int i = 0; i < nums.size(); i++) {
            if (used[i] != true) { // 当前下标还没有进入路径，才可以选择。
                used[i] = true;
                path.push_back(nums[i]);
                backtrace(nums);
                path.pop_back();  // 撤销当前选择。
                used[i] = false;  // 恢复使用状态，给兄弟分支使用。
            }
        }
    }

    vector<vector<int>> permute(vector<int>& nums) {
        int n = nums.size();
        used.assign(n, false);
        backtrace(nums);
        return ans;
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 排列状态 | 用 `used` 表示每个位置是否已用 | 正确区分排列和组合：排列每层都可以重新扫描所有元素 | 继续保持“路径长度代表正在填第几个位置”的理解 |
| 撤销动作 | `path.pop_back()` 和 `used[i] = false` 成对出现 | 能避免兄弟分支被污染 | 之后遇到棋盘/网格题也按这个思路恢复现场 |
| 状态作用域 | `ans/path/used` 是成员变量 | 单次调用可过，多次调用同一对象时答案可能残留 | 推荐入口内使用局部变量，或进入入口先清空所有状态 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 回溯结构完整，`used` 状态清楚 | 成员变量复用风险；`vector<int>` 表示布尔状态略重 | 适合无重复元素的排列生成 |
| 推荐最优解 | 状态局部化，`vector<bool>` 表达更贴切 | lambda 写法需要熟悉捕获 | 适合 LeetCode 提交和迁移到排列类模板 |

## 最优解法

1. 在入口内定义 `result`、`current` 和 `used`，避免多次调用残留。
2. 每一层都遍历全部下标，跳过已经进入路径的位置。
3. 选择元素后递归填下一个位置，返回后同时撤销路径和使用状态。

- 最优时间复杂度：`O(n * n!)`
- 最优空间复杂度：`O(n)`，不计返回结果

### 最优解代码

```cpp
class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> result;
        vector<int> current;
        vector<bool> used(nums.size(), false);

        function<void()> dfs = [&]() {
            if (current.size() == nums.size()) {
                result.push_back(current);
                return;
            }

            for (int i = 0; i < static_cast<int>(nums.size()); ++i) {
                if (used[i]) {
                    continue;
                }
                used[i] = true;
                current.push_back(nums[i]);
                dfs();
                current.pop_back();
                used[i] = false; // 恢复使用状态，让同层其他分支可以选择该元素。
            }
        };

        dfs();
        return result;
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | 成员变量保存状态 | 入口局部变量保存状态 | 避免复用污染 |
| 更新逻辑 | 选择、递归、撤销完整 | 同样完整 | 当前主干可以保留 |
| 边界处理 | 长度满时收集 | 长度满时收集 | 正确 |
| 复杂度 | `O(n*n!)` | `O(n*n!)` | 排列生成的必要成本 |

## 下一步建议

进入 `47. Permutations II` 时，把注意力放在“同一层去重”：不是看到相同值就跳过，而是要判断前一个相同值在当前层是否已经作为代表使用。

## 后续练习

1. `47. Permutations II` - 在排列状态上加入重复值去重。
2. `51. N-Queens` - 用类似 `used` 的状态维护列和对角线占用。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/46.permutations.cpp`
- 新函数名：`permuteOpt`
- 保留用户原实现：是
