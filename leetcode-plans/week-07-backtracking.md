# 第 07 周 - 回溯

## 本周目标

把第 6 周树题里的“函数返回什么”继续推进成“当前选择到哪里、路径里有什么、什么时候撤销”。到本周结束时，你应该能在枚举类题目中先画出决策过程，再写出稳定的递归入口、终止条件、选择推进和现场恢复；面对重复元素、字符串切分、棋盘约束和网格搜索时，也能说清楚哪些分支不需要继续探索。

资料校准：默认主题顺序与核心题池参考 `.codex/skills/leetcode-weekly-coach/references/topic-ladders.md`；题号、英文题名、难度和标签参考 LeetCode 官方题目页，校准日期为 2026-06-03。已校准代表题包括 `78. Subsets`、`17. Letter Combinations of a Phone Number`、`39. Combination Sum`、`46. Permutations`、`79. Word Search`、`131. Palindrome Partitioning`、`40. Combination Sum II`、`51. N-Queens` 等。

## 与第 6 周衔接

树题强调“子树返回给父节点什么”；回溯强调“当前层做了什么选择，返回上一层前要恢复什么”。第 6 周如果递归返回值说不清，会把局部信息和全局答案混在一起；第 7 周如果路径状态说不清，会把兄弟分支互相污染，或者重复枚举同一种结果。

## 前置知识

- 能写出基础递归函数，并明确参数含义
- 能维护一个当前路径，并在递归返回前恢复
- 能区分“当前位置”“可选范围”和“已经选择过的内容”
- 能判断什么时候收集答案，什么时候直接停止
- 能手推 3 个元素以内的小规模搜索过程
- 能接受指数级复杂度，并说明规模限制为什么允许枚举

## 每日计划

### 第 1 天 - 枚举入口与路径意识

1. `401. Binary Watch` (`简单`) - 先用小规模枚举热身，练习把多个位置的选择结果转成合法输出。
2. `78. Subsets` (`中等`) - 练习在每一层决定是否继续扩展当前结果，并确保所有结果都被收集。
3. `17. Letter Combinations of a Phone Number` (`中等`) - 练习处理每一位都有多个可选项的字符串生成问题。

### 第 2 天 - 固定长度与组合边界

1. `77. Combinations` (`中等`) - 练习从有序范围中选择固定数量元素，并控制递归深度。
2. `216. Combination Sum III` (`中等`) - 练习同时满足数量和数值目标的枚举，并提前停止无效分支。
3. `39. Combination Sum` (`中等`) - 练习在结果长度不固定时保持选择顺序稳定，避免产生重复结果。

### 第 3 天 - 排列与使用状态

1. `46. Permutations` (`中等`) - 练习每个位置选择一个未使用元素，并生成完整排列。
2. `47. Permutations II` (`中等`) - 练习在存在重复元素时避免生成重复排列。
3. `31. Next Permutation` (`中等`) - 作为排列主题的非递归迁移题，观察“下一个结果”如何由局部调整得到。

### 第 4 天 - 重复元素与结果去重

1. `90. Subsets II` (`中等`) - 练习在输入包含重复值时生成不重复结果。
2. `40. Combination Sum II` (`中等`) - 练习每个输入位置只能使用一次时，如何保持结果唯一。
3. `491. Non-decreasing Subsequences` (`中等`) - 练习在不改变原顺序的条件下处理重复和合法性限制。

### 第 5 天 - 字符串切分与格式约束

1. `131. Palindrome Partitioning` (`中等`) - 练习把字符串切成多段，并在每段满足条件时继续探索。
2. `93. Restore IP Addresses` (`中等`) - 练习固定段数、段长度和数值范围同时存在时的边界控制。
3. `22. Generate Parentheses` (`中等`) - 练习在生成过程中持续保持结果合法，而不是生成后再筛选。

### 第 6 天 - 网格搜索与棋盘约束

1. `79. Word Search` (`中等`) - 练习在二维空间中沿路径搜索，并防止同一路径重复使用位置。
2. `51. N-Queens` (`困难`) - 练习把多种位置限制合并进搜索过程，并输出完整布局。
3. `37. Sudoku Solver` (`困难`) - 练习在高约束场景中选择下一个待填位置，并持续维护合法性。

### 第 7 天 - 综合复盘与迁移

1. `784. Letter Case Permutation` (`中等`) - 回顾字符串生成中“可变位置”和“固定位置”的处理。
2. `698. Partition to K Equal Sum Subsets` (`中等`) - 练习把数字分配到多个目标组中，并控制搜索顺序。
3. `52. N-Queens II` (`困难`) - 回到棋盘约束题，只统计数量，复盘“收集答案”和“计数答案”的差异。

## 本周关注清单

- 每题动手前先写一句：递归函数的参数分别表示什么。
- 每次修改当前路径或棋盘状态后，都检查返回上一层前有没有恢复。
- 收集答案前确认：当前状态是完整答案，还是只是一段中间路径。
- 遇到重复元素时，先区分是“输入值重复”还是“选择位置重复”。
- 遇到字符串切分时，先确认切分边界是否为空、越界或违反格式。
- 遇到棋盘和网格题时，优先手推 2x2、3x3 的小例子，不直接上大图。
- 每天复盘至少说清一题的搜索树：每层代表什么，分支代表什么，什么时候停止。

## 本周节奏建议

- 第 1 天：不追求速度，先把“选择、递归、撤销”的动作写顺。
- 第 2 天：重点观察递归深度、可选范围和目标值如何一起变化。
- 第 3 天：从组合切到排列，训练“位置”和“元素是否已用”的区别。
- 第 4 天：集中处理重复元素，不要靠结果容器兜底去重。
- 第 5 天：进入字符串切分，重点检查空段、越界和格式非法的边界。
- 第 6 天：挑战网格和棋盘约束，允许慢一点，但每个限制都要能口头解释。
- 第 7 天：做综合迁移，把枚举、分配、计数三种输出形式放在一起复盘。

## 进度更新 - 2026-06-04

- 今日完成：`401. Binary Watch`、`78. Subsets`、`17. Letter Combinations of a Phone Number`
- 当前主题：第 1 天 - 枚举入口与路径意识

### 通用解题模板

- 适用条件：题目要求枚举所有可能结果，并且每一层都可以从当前可选项中做一个选择，进入下一层后再恢复现场。
- 核心骨架：维护一个 `path` 表示当前已选内容；递归参数记录处理到的位置或下一次选择起点；到达完整状态时收集答案；每次 `push` 之后递归，返回后 `pop`。
- 关键边界：空输入是否应该返回空答案要按题意判断；收集答案的时机可能是每个节点，也可能只在叶子；成员变量在多次调用时要清空或改成局部变量。
- 复杂度：时间通常与结果数量成正比，空间为递归深度和当前路径长度。

```cpp
class Solution {
public:
    vector<vector<int>> backtrackingTemplate(vector<int>& nums) {
        vector<vector<int>> ans;
        vector<int> path;

        function<void(int)> dfs = [&](int start) {
            ans.push_back(path); // 当前路径如果已经是合法结果，就在这里收集。
            for (int i = start; i < static_cast<int>(nums.size()); ++i) {
                path.push_back(nums[i]);
                dfs(i + 1);
                path.pop_back(); // 回到同层继续尝试下一个选择。
            }
        };

        dfs(0);
        return ans;
    }
};
```

### 逐题评价

| 题目 | 完成质量 | 亮点 | 风险或复盘重点 | 详细点评 |
| --- | --- | --- | --- | --- |
| `401. Binary Watch` | 待提交验证，源码逻辑检查通过 | 能把亮灯数量拆成小时和分钟两部分，并分别枚举合法值后组合。 | 当前写法函数较多；可用小范围直接枚举降低实现复杂度。 | [查看](../leetcode-reviews/2026-06-04-401-binary-watch.md) |
| `78. Subsets` | 待提交验证，源码逻辑检查通过 | “选当前元素 / 不选当前元素”的递归结构清楚，`push/pop` 位置正确。 | 成员变量多次调用会残留；也可以改成每层都收集当前路径的组合模板。 | [查看](../leetcode-reviews/2026-06-04-78-subsets.md) |
| `17. Letter Combinations of a Phone Number` | 有边界错误，递归主体正确 | 能按数字位置逐层选择字母，并正确撤销当前字符。 | 空字符串应返回空数组，当前实现会返回 `[""]`；成员变量也有复用风险。 | [查看](../leetcode-reviews/2026-06-04-17-letter-combinations-of-a-phone-number.md) |

- 暴露问题：今天的核心动作已经成型：选择、递归、撤销都写出来了。主要需要补强两个习惯：先判断空输入的题意返回值；尽量把 `ans/path` 放在入口局部变量里，避免 LeetCode 同一对象多次调用时残留。
- 下一步安排：进入第 2 天固定长度与组合边界。下一组题会把“随便枚举所有结果”推进到“选择数量、目标值和起点范围一起受限制”，重点观察递归参数如何同时表达深度和剩余约束。

## 进度更新 - 2026-06-05

- 今日完成：`77. Combinations`、`216. Combination Sum III`、`39. Combination Sum`
- 当前主题：第 2 天 - 固定长度与组合边界

### 通用解题模板

- 适用条件：题目要求生成组合结果，并且每一层都从一个有序可选范围中继续选择；结果不关心排列顺序，需要通过起点控制避免重复。
- 核心骨架：维护当前路径 `path`；递归参数至少包含下一次选择起点 `start`，并按题意增加剩余数量 `left` 或剩余目标 `remain`；选择后递归，返回前撤销。
- 关键边界：固定长度题要在长度满足时收集；目标和题推荐用 `remain` 表达剩余目标；`i + 1` 表示当前数字不能再用，`i` 表示当前数字可以重复使用；成员变量要初始化或改成局部变量。
- 复杂度：时间与搜索树规模和答案复制成本相关；固定长度组合为 `O(C(n,k)*k)`，目标和组合为输出敏感复杂度；空间为递归深度和当前路径长度。

```cpp
class Solution {
public:
    vector<vector<int>> combinationTemplate(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());

        vector<vector<int>> result;
        vector<int> path;

        function<void(int, int)> dfs = [&](int start, int remain) {
            if (remain == 0) {
                result.push_back(path);
                return;
            }

            for (int i = start; i < static_cast<int>(nums.size()); ++i) {
                if (nums[i] > remain) {
                    break;
                }
                path.push_back(nums[i]);
                dfs(i, remain - nums[i]); // 改成 i + 1 时，表示当前数字不能重复使用。
                path.pop_back();
            }
        };

        dfs(0, target);
        return result;
    }
};
```

### 逐题评价

| 题目 | 完成质量 | 亮点 | 风险或复盘重点 | 详细点评 |
| --- | --- | --- | --- | --- |
| `77. Combinations` | 待提交验证，源码逻辑检查通过 | 能用 `start` 控制组合顺序，并写出 `n - need + 1` 的数量剪枝。 | `ans/comb` 是成员变量，建议入口局部化，避免多次调用残留。 | [查看](../leetcode-reviews/2026-06-05-77-combinations.md) |
| `216. Combination Sum III` | 有主要风险，递归主体正确 | 能同时维护数量、起点和目标和，并用 `i + 1` 保证数字不重复。 | `sum` 成员变量未初始化；循环上界不应把目标和 `n` 当作数字范围。 | [查看](../leetcode-reviews/2026-06-05-216-combination-sum-iii.md) |
| `39. Combination Sum` | 有主要风险，核心方向正确 | 能抓住递归传 `i` 表示当前数字可重复使用，也能用 `start` 避免排列重复。 | `sum` 成员变量未初始化；建议排序后用 `remain` 剪枝。 | [查看](../leetcode-reviews/2026-06-05-39-combination-sum.md) |

- 暴露问题：今天已经把组合题最核心的起点推进写出来了，尤其是能区分 `i + 1` 和 `i` 的含义。主要风险集中在“把数值状态放成员变量但没有初始化”，以及“循环上界到底由数量范围决定，还是由目标和决定”这两点。
- 下一步安排：进入第 3 天排列与使用状态。下一组题会从“组合只向后选”切换到“每个位置都可能选择任意未使用元素”，重点观察递归参数从 `start` 变成使用状态后，重复结果是如何被控制的。

## 进度更新 - 2026-06-13

- 今日完成：`46. Permutations`、`47. Permutations II`、`31. Next Permutation`
- 当前主题：第 3 天 - 排列与使用状态

### 通用解题模板

- 适用条件：题目要求生成所有排列，或者每一层都要给当前位置选择一个尚未使用的元素；如果存在重复值，需要保证同一层不重复选择等价分支。
- 核心骨架：维护 `path` 表示当前排列前缀，维护 `used/visited` 表示哪些下标已经进入路径；每层遍历所有下标，选择未使用元素，递归后撤销路径和使用状态。
- 关键边界：路径长度达到 `nums.size()` 时收集答案；重复排列题先排序，再用 `i > 0 && nums[i] == nums[i - 1] && !used[i - 1]` 跳过同层重复；成员变量状态要清空或局部化。
- 复杂度：无重复排列时间 `O(n*n!)`，空间 `O(n)`；重复排列最坏仍为 `O(n*n!)`，但同层去重会减少实际分支数量。

```cpp
class Solution {
public:
    vector<vector<int>> permuteTemplate(vector<int>& nums) {
        sort(nums.begin(), nums.end());

        vector<vector<int>> result;
        vector<int> path;
        vector<bool> used(nums.size(), false);

        function<void()> dfs = [&]() {
            if (path.size() == nums.size()) {
                result.push_back(path);
                return;
            }

            for (int i = 0; i < static_cast<int>(nums.size()); ++i) {
                if (used[i]) {
                    continue;
                }
                if (i > 0 && nums[i] == nums[i - 1] && !used[i - 1]) {
                    continue; // 同一层跳过重复值代表，避免重复排列。
                }
                used[i] = true;
                path.push_back(nums[i]);
                dfs();
                path.pop_back();
                used[i] = false;
            }
        };

        dfs();
        return result;
    }
};
```

### 逐题评价

| 题目 | 完成质量 | 亮点 | 风险或复盘重点 | 详细点评 |
| --- | --- | --- | --- | --- |
| `46. Permutations` | 待提交验证，源码逻辑检查通过 | 能用 `used` 标记元素是否已进入路径，选择和撤销动作完整。 | 成员变量状态没有入口清空，建议局部化；`vector<int>` 可换成更贴切的布尔状态。 | [查看](../leetcode-reviews/2026-06-13-46-permutations.md) |
| `47. Permutations II` | 待提交验证，源码逻辑检查通过 | 正确使用排序和 `!used[i - 1]` 做同层去重。 | `backtrace(vector<int> nums)` 按值传参会重复复制数组，建议改为引用或局部 lambda。 | [查看](../leetcode-reviews/2026-06-13-47-permutations-ii.md) |
| `31. Next Permutation` | 待提交验证，源码逻辑检查通过 | 已写出标准的找主元、找后继、反转后缀流程。 | 重点复盘为什么主元右侧必然降序，以及为什么反转后缀能得到最小增量。 | [查看](../leetcode-reviews/2026-06-13-31-next-permutation.md) |

- 暴露问题：排列回溯的核心动作已经稳定，尤其是 `used` 的选择/撤销和重复排列的同层去重。主要改进点是把成员变量状态局部化、避免递归中按值复制大对象，并能用语言解释 `!used[i - 1]` 代表“同一层去重”。
- 下一步安排：进入第 4 天重复元素与结果去重。下一组题会把今天的同层去重迁移到子集、组合和序列题里，重点观察“排序后同层跳过”和“不改变原顺序时每层去重”的差异。

## 进度更新 - 2026-06-15

- 今日完成：`90. Subsets II`、`40. Combination Sum II`、`491. Non-decreasing Subsequences`
- 当前主题：第 4 天 - 重复元素与结果去重

### 通用解题模板

- 适用条件：输入中可能有重复值，题目要求结果不能重复；每层递归都要避免从等价候选开始生成相同结果。
- 核心骨架：如果题目允许重排输入，先排序，再用 `i > start && nums[i] == nums[i - 1]` 做同层去重；如果题目必须保留原顺序，则每层新建一个集合记录本层已经尝试过的数值。
- 关键边界：同层去重只跳过兄弟分支，不阻止下一层继续使用相同值；组合题的 `i + 1` 表示每个位置最多使用一次；子序列题不能排序，否则会破坏原顺序。
- 复杂度：时间通常为 `O(n*2^n)` 级别，空间为递归深度 `O(n)`，不计返回结果。

```cpp
class Solution {
public:
    vector<vector<int>> dedupTemplate(vector<int>& nums) {
        sort(nums.begin(), nums.end());

        vector<vector<int>> result;
        vector<int> path;

        function<void(int)> dfs = [&](int start) {
            result.push_back(path);

            for (int i = start; i < static_cast<int>(nums.size()); ++i) {
                if (i > start && nums[i] == nums[i - 1]) {
                    continue; // 只跳过同一层重复分支。
                }
                path.push_back(nums[i]);
                dfs(i + 1);
                path.pop_back();
            }
        };

        dfs(0);
        return result;
    }
};
```

### 逐题评价

| 题目 | 完成质量 | 亮点 | 风险或复盘重点 | 详细点评 |
| --- | --- | --- | --- | --- |
| `90. Subsets II` | 待提交验证，源码逻辑检查通过 | 能用排序和 `i > idx` 做同层去重，每个递归节点收集子集的时机正确。 | 成员变量复用有残留风险；重点复盘 `idx` 为什么代表当前层边界。 | [查看](../leetcode-reviews/2026-06-15-90-subsets-ii.md) |
| `40. Combination Sum II` | 待提交验证，源码逻辑检查通过 | 能把同层去重、目标递减和 `i + 1` 组合起来，表达每个位置只能使用一次。 | 排序后可以补 `candidates[i] > target` 的提前停止，减少无效分支。 | [查看](../leetcode-reviews/2026-06-15-40-combination-sum-ii.md) |
| `491. Non-decreasing Subsequences` | 待提交验证，源码逻辑检查通过 | 能意识到不能排序，并改用每层 `unordered_set` 做局部去重。 | 重点复盘“本层集合”和“全局集合”的区别，以及为什么集合不能跨层复用。 | [查看](../leetcode-reviews/2026-06-15-491-non-decreasing-subsequences.md) |

- 暴露问题：今天的同层去重已经比较成型，尤其是能区分“可排序后相邻去重”和“必须保留原顺序时用每层集合”。主要改进点仍是把成员变量状态局部化，并在目标和题中利用排序进一步剪枝。
- 下一步安排：进入第 5 天字符串切分与格式约束。下一组题会把“选择一个元素”切换成“选择一段字符串”，重点观察切分边界、段合法性和递归停止条件。

## 前四天模板分类复盘

这 12 道题可以按“递归状态到底在表达什么”重新分组。复盘时不要只按日期记题，而要先判断当前题更像哪一种模板。

### 1. 小规模枚举 / 位状态枚举

| 模板 | 题目 | 共同点 |
| --- | --- | --- |
| 固定范围枚举，统计合法状态 | `401. Binary Watch` | 搜索空间很小，可以直接枚举所有状态，再判断是否合法。 |

这题更像回溯热身，不一定要写标准 `path + dfs`。重点是把“枚举所有可能状态，再筛合法结果”这件事写清楚。

### 2. 子集模板：每个节点都收集答案

| 模板 | 题目 | 共同点 |
| --- | --- | --- |
| `dfs(start)`，进入递归节点就收集当前 `path` | `78. Subsets`、`90. Subsets II` | 当前路径本身就是一个合法子集，不需要等到叶子节点。 |

- `78`：无重复元素，直接从 `start` 往后选。
- `90`：有重复元素，先排序，同层用 `i > start && nums[i] == nums[i - 1]` 去重。

```cpp
void dfs(int start) {
    ans.push_back(path);

    for (int i = start; i < static_cast<int>(nums.size()); ++i) {
        if (i > start && nums[i] == nums[i - 1]) {
            continue; // 有重复元素时加这一句。
        }
        path.push_back(nums[i]);
        dfs(i + 1);
        path.pop_back();
    }
}
```

### 3. 组合模板：固定长度 / 从有序范围选若干个

| 模板 | 题目 | 共同点 |
| --- | --- | --- |
| `dfs(start)`，路径长度达到目标才收集 | `77. Combinations`、`216. Combination Sum III` | 组合只关心选择集合，不关心排列顺序，所以每次往后选。 |

- `77`：只限制选 `k` 个。
- `216`：同时限制选 `k` 个，并且和为 `n`。

```cpp
void dfs(int start) {
    if (static_cast<int>(path.size()) == k) {
        ans.push_back(path);
        return;
    }

    int need = k - static_cast<int>(path.size());
    for (int value = start; value <= upper - need + 1; ++value) {
        path.push_back(value);
        dfs(value + 1);
        path.pop_back();
    }
}
```

`216` 在这个基础上多维护剩余数量和剩余目标：

```cpp
dfs(value + 1, left - 1, remain - value);
```

### 4. 组合总和模板：目标和 + 起点控制

| 模板 | 题目 | 共同点 |
| --- | --- | --- |
| `dfs(start, remain)` | `39. Combination Sum`、`40. Combination Sum II` | 都是从候选数组里选数凑目标，用 `remain` 表示剩余目标。 |

| 题目 | 当前数字能否重复使用 | 递归下一层 |
| --- | --- | --- |
| `39. Combination Sum` | 可以重复使用 | `dfs(i, remain - candidates[i])` |
| `40. Combination Sum II` | 每个位置只能用一次 | `dfs(i + 1, remain - candidates[i])` |

`40` 还有重复元素，需要排序后同层去重：

```cpp
if (i > start && candidates[i] == candidates[i - 1]) {
    continue;
}
```

### 5. 排列模板：每个位置选择一个未使用元素

| 模板 | 题目 | 共同点 |
| --- | --- | --- |
| `used[i]` / `visited[i]` 标记位置是否已用 | `46. Permutations`、`47. Permutations II` | 每一层是在“填排列的下一个位置”，所以每层都从 `0` 扫到 `n - 1`。 |

- `46`：无重复元素，只需要 `used`。
- `47`：有重复元素，先排序，再同层去重。

```cpp
void dfs() {
    if (path.size() == nums.size()) {
        ans.push_back(path);
        return;
    }

    for (int i = 0; i < static_cast<int>(nums.size()); ++i) {
        if (used[i]) {
            continue;
        }
        if (i > 0 && nums[i] == nums[i - 1] && !used[i - 1]) {
            continue; // 排列题的同层去重。
        }

        used[i] = true;
        path.push_back(nums[i]);
        dfs();
        path.pop_back();
        used[i] = false;
    }
}
```

### 6. 保留原顺序的子序列模板

| 模板 | 题目 | 共同点 |
| --- | --- | --- |
| `dfs(start)` + 每层 `unordered_set` 去重 | `491. Non-decreasing Subsequences` | 不能排序，因为子序列必须保持原数组顺序。 |

可排序题通常使用相邻元素同层去重：

```cpp
sort(nums.begin(), nums.end());
if (i > start && nums[i] == nums[i - 1]) {
    continue;
}
```

不能排序时，每一层单独记录已经尝试过的数值：

```cpp
unordered_set<int> usedThisLevel;
for (int i = start; i < static_cast<int>(nums.size()); ++i) {
    if (usedThisLevel.count(nums[i])) {
        continue;
    }
    if (!path.empty() && nums[i] < path.back()) {
        continue;
    }

    usedThisLevel.insert(nums[i]);
    path.push_back(nums[i]);
    dfs(i + 1);
    path.pop_back();
}
```

### 7. 非回溯排列构造模板

| 模板 | 题目 | 共同点 |
| --- | --- | --- |
| 字典序局部调整 | `31. Next Permutation` | 不生成所有排列，只原地构造下一个排列。 |

固定步骤：

1. 从右往左找第一个 `nums[i] < nums[i + 1]` 的主元。
2. 从右往左找第一个大于主元的数。
3. 交换二者。
4. 反转主元右侧后缀。

### 总表

| 大类 | 题目 |
| --- | --- |
| 小规模枚举 | `401` |
| 子集：每个节点收集 | `78`、`90` |
| 固定长度组合 | `77`、`216` |
| 目标和组合 | `39`、`40` |
| 排列 + `used` | `46`、`47` |
| 保序子序列 + 每层集合 | `491` |
| 非回溯排列构造 | `31` |

最重要的迁移句：`start` 解决“组合 / 子集只往后选”，`used` 解决“排列中每个位置都能选任意未用元素”，`i > start` 解决“排序后的同层去重”，每层 `set` 解决“不能排序但仍要同层去重”。
