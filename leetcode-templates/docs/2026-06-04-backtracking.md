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

## 回溯的两种递归形态

### 写法一：`for` 循环填充下一个位置

- 递归含义：当前递归层负责“给路径的下一个位置选一个值”。
- 典型参数：`start` 表示这一层可以从哪里开始选；组合题用它避免重复顺序，排列题通常换成 `used` 标记。
- 适用题型：组合、排列、切分、棋盘放置、路径搜索，以及每一层有多个候选项的问题。
- 收集时机：固定长度组合和排列通常在 `path.size()` 达到目标时收集；子集也可以在每个递归节点先收集一次。
- 易错点：循环上界要保证剩余数量够用；递归参数传 `i + 1` 表示当前元素不能再用，传 `i` 表示当前元素可以重复使用。

```cpp
void dfs(int start) {
    if (path.size() == targetSize) {
        ans.push_back(path);
        return;
    }

    for (int i = start; i < static_cast<int>(nums.size()); ++i) {
        path.push_back(nums[i]);
        dfs(i + 1);      // 组合：下一层只能从后面继续选。
        path.pop_back(); // 撤销后，继续尝试同层下一个候选。
    }
}
```

### 写法二：选或者不选

- 递归含义：当前递归层只处理一个位置 `index`，决策是“选它”或“不选它”。
- 典型参数：`index` 表示正在考虑哪个元素；每次递归都推进到 `index + 1`。
- 适用题型：子集、01 选择、每个元素最多使用一次且选择分支天然是二叉的问题。
- 收集时机：通常在 `index == nums.size()` 时收集，因为这时每个元素都已经做完“选 / 不选”决策。
- 易错点：选的分支需要 `push_back` 后再 `pop_back`；不选分支不能修改路径；如果题目要求固定长度或目标和，可以在递归中加入剪枝。

```cpp
void dfs(int index) {
    if (index == static_cast<int>(nums.size())) {
        ans.push_back(path);
        return;
    }

    path.push_back(nums[index]); // 选当前元素。
    dfs(index + 1);
    path.pop_back();

    dfs(index + 1); // 不选当前元素。
}
```

### 怎么选择

- 如果题目问“下一步可以从一组候选里挑谁”，优先用 `for` 循环写法。
- 如果题目问“每个元素只有选或不选两种状态”，可以用选 / 不选写法。
- `for` 写法通常更容易加入 `start`、数量剪枝、目标和剪枝和同层去重；选 / 不选写法更贴近二叉决策树，适合理解子集和 01 选择。
- 两种写法搜索到的状态空间可能等价，但递归参数的含义不同。写题前先说清楚：当前层是在“填下一个位置”，还是在“处理当前元素”。

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

    void chooseOrSkipSubsetDfs(vector<int>& nums, int index) {
        if (index == static_cast<int>(nums.size())) {
            ans.push_back(path);
            return;
        }

        path.push_back(nums[index]); // 选当前元素。
        chooseOrSkipSubsetDfs(nums, index + 1);
        path.pop_back();

        chooseOrSkipSubsetDfs(nums, index + 1); // 不选当前元素。
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

    vector<vector<int>> subsetsChooseOrSkipTemplate(vector<int>& nums) {
        ans.clear();
        path.clear();
        chooseOrSkipSubsetDfs(nums, 0);
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

### 样例 1 补充

- 输入：`nums = [1,2,3]`
- 输出：`subsetsChooseOrSkipTemplate(nums)` 生成 8 个子集，例如 `[1,2,3] [1,2] [1,3] [1] [2,3] [2] [3] []`
- 说明：每个元素依次做“选 / 不选”决策，直到 `index == nums.size()` 时才收集完整决策结果。

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
