# 算法模板 - 回溯

## 基本信息

- 日期：2026-06-04
- 主题：回溯
- 目标：沉淀“路径、选择列表、终止条件、撤销动作”这一类状态空间搜索题的通用写法。
- 适用语言：C++20
- 文档路径：`leetcode-templates/docs/2026-06-04-backtracking.md`
- 测试代码路径：`leetcode-templates/code/2026-06-04-backtracking.cpp`

## 适用信号

- 题目要求返回所有方案、所有组合、所有排列、所有路径或所有合法布局。
- 每一步都有多个候选选择，选择后进入下一层，返回上一层后还要继续尝试同层其他选择。
- 结果数量通常是指数级，题目输入规模较小，允许枚举完整状态空间。
- 题目中出现“不能重复使用”“固定选择数量”“结果不能重复”“路径合法”等限制。

## 核心思路

1. 先定义递归函数参数：当前处理到哪里、下一次从哪里开始选、当前还剩多少目标或哪些元素已经用过。
2. 用 `path` 保存当前已经做出的选择，用 `ans` 保存所有完整或阶段性合法结果。
3. 在当前层枚举选择；每次先做选择，再递归进入下一层，返回后撤销选择，让同层下一个分支看到干净状态。
4. 根据题意决定收集答案的时机：子集类可以每个递归节点都收集，排列和固定长度组合通常在路径长度满足要求时收集。

## 关键边界

- 空输入不总是同一种返回：`Subsets` 应包含空集，`Letter Combinations` 的空字符串应返回空数组。
- `push_back` 和 `pop_back` 必须成对出现；如果还维护 `used`、棋盘标记或计数，也要成对恢复。
- 组合类通常使用 `start` 保证只向后选择；排列类通常使用 `used` 表示哪些位置已经进入路径。
- 有重复元素时，通常先排序，并在同一层跳过重复选择；不要只依赖最终结果容器去重。
- 剪枝条件必须不丢合法答案：常见剪枝包括剩余数量不足、当前和已经超过目标、当前位置越界。

## 复杂度

- 时间复杂度：通常和结果数量成正比；子集类常见为 `O(n * 2^n)`，排列类常见为 `O(n * n!)`。
- 空间复杂度：通常为递归深度和当前路径 `O(n)`；不计输出结果。

## 模板代码

```cpp
class Solution {
private:
    vector<vector<int>> ans;
    vector<int> path;

    void subsetDfs(vector<int>& nums, int start) {
        // 子集类：当前路径本身就是一个合法结果。
        ans.push_back(path);

        for (int i = start; i < static_cast<int>(nums.size()); ++i) {
            path.push_back(nums[i]);
            subsetDfs(nums, i + 1);
            path.pop_back(); // 撤销当前选择，继续尝试同层下一个元素。
        }
    }

    void combinationDfs(int n, int k, int start) {
        if (static_cast<int>(path.size()) == k) {
            ans.push_back(path);
            return;
        }

        int need = k - static_cast<int>(path.size());
        for (int value = start; value <= n - need + 1; ++value) {
            path.push_back(value);
            combinationDfs(n, k, value + 1);
            path.pop_back();
        }
    }

    void permutationDfs(vector<int>& nums, vector<bool>& used) {
        if (path.size() == nums.size()) {
            ans.push_back(path);
            return;
        }

        for (int i = 0; i < static_cast<int>(nums.size()); ++i) {
            if (used[i]) {
                continue;
            }

            used[i] = true;
            path.push_back(nums[i]);
            permutationDfs(nums, used);
            path.pop_back();
            used[i] = false; // 撤销使用标记，避免影响其他排列分支。
        }
    }

public:
    vector<vector<int>> subsetsTemplate(vector<int>& nums) {
        ans.clear();
        path.clear();
        subsetDfs(nums, 0);
        return ans;
    }

    vector<vector<int>> combinationsTemplate(int n, int k) {
        ans.clear();
        path.clear();
        combinationDfs(n, k, 1);
        return ans;
    }

    vector<vector<int>> permutationsTemplate(vector<int>& nums) {
        ans.clear();
        path.clear();
        vector<bool> used(nums.size(), false);
        permutationDfs(nums, used);
        return ans;
    }
};
```

## 运行样例

### 样例 1

- 输入：`nums = [1,2,3]`
- 输出：`subsetsTemplate(nums)` 生成 `[] [1] [1,2] [1,2,3] [1,3] [2] [2,3] [3]`
- 说明：每进入一个递归节点就收集当前路径，因此空路径和所有长度的路径都会成为答案。

### 样例 2

- 输入：`n = 4, k = 2`
- 输出：`combinationsTemplate(4, 2)` 生成 `[1,2] [1,3] [1,4] [2,3] [2,4] [3,4]`
- 说明：`start` 保证每个组合只按递增顺序生成一次；`need` 用来剪掉剩余数量不足的分支。

### 样例 3

- 输入：`nums = [1,2,3]`
- 输出：`permutationsTemplate(nums)` 生成 6 个排列。
- 说明：`used` 记录哪些位置已经进入当前路径，路径长度达到 `nums.size()` 时收集答案。

## 套用提醒

- 做题前先写一句：递归参数是什么，`path` 里保存的是什么。
- 组合、子集、切分问题通常看 `start/index`；排列、棋盘放置通常看 `used/visited`。
- 如果题目要求结果去重，优先在“同一层选择”处去重，而不是生成所有结果后再去重。
- 如果题目只要求数量，可以把 `ans.push_back(path)` 改成计数器累加，避免保存大量结果。
- 如果题目是网格路径，撤销动作通常是恢复 `visited[x][y]` 或恢复原字符。
