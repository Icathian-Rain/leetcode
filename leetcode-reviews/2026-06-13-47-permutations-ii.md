# 题解点评 - 47. Permutations II

## 基本信息

- 日期：2026-06-13
- 主题：回溯 / 排列去重
- 难度：中等
- 本次结果：待提交验证，源码逻辑检查通过
- 对应源码：`src/47.permutations-ii.cpp`
- 资料来源：LeetCode 官方题目页 `https://leetcode.cn/problems/permutations-ii/`
- 查询日期：2026-06-13

## 用户思路概述

1. 先对 `nums` 排序，让相同数字相邻，便于在同一层判断重复选择。
2. 用 `used` 标记下标是否已经进入当前路径。
3. 每层遍历所有下标，跳过已经使用过的下标。
4. 当 `nums[i] == nums[i - 1]` 且前一个相同值没有被使用时，跳过当前选择，避免同一层重复生成相同排列。

## 用户解法复杂度

- 时间复杂度：最坏 `O(n * n!)`
- 空间复杂度：`O(n)`，不计返回结果
- 复杂度来源：最坏情况下没有重复元素，需要生成全部排列；排序额外 `O(n log n)`，被排列枚举成本覆盖。

## 用户代码注释版

```cpp
class Solution {
    vector<vector<int>> ans;
    vector<int> path;
    vector<int> used;

    void backtrace(vector<int> nums) {
        if (path.size() == nums.size()) {
            ans.push_back(path);
            return;
        }

        for (int i = 0; i < nums.size(); i++) {
            if ((used[i] == true) ||
                (i > 0 && nums[i] == nums[i - 1] && (used[i - 1] == false))) {
                continue; // 已用位置跳过；同层重复值只让第一个未使用位置作为代表。
            }
            used[i] = true;
            path.push_back(nums[i]);
            backtrace(nums);
            path.pop_back();
            used[i] = false;
        }
    }

public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        int n = nums.size();
        used.assign(n, false);
        sort(nums.begin(), nums.end());
        backtrace(nums);
        return ans;
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 去重前提 | 先排序 | 相同数字相邻后才能可靠判断同层重复 | 这是重复元素回溯题的第一步 |
| 同层去重 | 使用 `!used[i - 1]` 判断 | 正确避免相同数字在同一位置重复作为分支开头 | 重点记住这是“同一层去重”，不是“整条路径不能有重复值” |
| 参数传递 | `backtrace(vector<int> nums)` 按值传递 | 每层递归都会复制数组，增加不必要开销 | 改成 `vector<int>& nums` 或局部 lambda 捕获 |
| 状态作用域 | 成员变量保存答案和路径 | 单次调用可过，多次调用有残留风险 | 入口局部化更稳 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 去重条件方向正确，主干回溯完整 | 按值传参有额外复制；成员状态复用风险 | 适合本题，但可优化实现细节 |
| 推荐最优解 | 状态局部化，按引用处理数组，去重条件集中清楚 | 需要准确理解 `!visited[i - 1]` | 适合重复排列和后续重复元素回溯题 |

## 最优解法

1. 排序，让相同数字相邻。
2. 用 `visited` 标记每个下标是否已经进入当前排列。
3. 每层跳过已使用元素；如果当前值等于前一个值且前一个相同值未使用，说明当前层会产生重复分支，也跳过。
4. 路径长度达到 `n` 时收集答案。

- 最优时间复杂度：最坏 `O(n * n!)`
- 最优空间复杂度：`O(n)`，不计返回结果

### 最优解代码

```cpp
class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        sort(nums.begin(), nums.end());

        vector<vector<int>> result;
        vector<int> current;
        vector<bool> visited(nums.size(), false);

        function<void()> dfs = [&]() {
            if (current.size() == nums.size()) {
                result.push_back(current);
                return;
            }

            for (int i = 0; i < static_cast<int>(nums.size()); ++i) {
                if (visited[i]) {
                    continue;
                }
                // 同一层只使用相同数字中的第一个未使用位置，避免重复排列。
                if (i > 0 && nums[i] == nums[i - 1] && !visited[i - 1]) {
                    continue;
                }
                visited[i] = true;
                current.push_back(nums[i]);
                dfs();
                current.pop_back();
                visited[i] = false;
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
| 状态定义 | 成员变量 | 局部变量 | 避免多次调用残留 |
| 更新逻辑 | 选择、递归、撤销完整 | 同样完整 | 主干正确 |
| 边界处理 | 同层去重条件正确 | 同层去重条件正确 | 继续巩固 `!used[i-1]` 的含义 |
| 复杂度 | 最坏 `O(n*n!)`，但递归复制数组 | 最坏 `O(n*n!)`，无数组复制 | 改按引用传参 |

## 下一步建议

建议补边界测试：`[1,1,2]`、`[1,1,1]`、`[1,2,2]`。如果这三组都能手推清楚，重复排列的同层去重就算扎实了。

## 后续练习

1. `90. Subsets II` - 把同层去重迁移到子集生成。
2. `40. Combination Sum II` - 把同层去重迁移到目标和组合。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/47.permutations-ii.cpp`
- 新函数名：`permuteUniqueOpt`
- 保留用户原实现：是
