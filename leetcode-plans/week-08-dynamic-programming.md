# 第 08 周 - 动态规划

## 本周目标

把前 7 周里“递归状态、路径状态、局部选择”的经验，推进成“一个位置或区间的答案如何由更小问题推出”。到本周结束时，你应该能在动手前先写清楚：当前记录的量代表什么、它依赖哪些已经处理过的结果、初始条件是什么、遍历顺序为什么不会用到未来信息。

资料依据：默认主题顺序与核心题池参考 `.codex/skills/leetcode-weekly-coach/references/topic-ladders.md`；题号、英文题名和难度按本地训练题池整理，记录日期为 2026-06-19。做题或生成点评时，再按单题继续核对官方信息。

## 与第 7 周衔接

回溯强调“当前层做选择，再把选择撤销”；动态规划强调“当前状态不再展开整棵搜索树，而是复用已经算过的子结果”。如果第 7 周能说清递归参数含义，本周就要进一步说清每个状态的含义；如果回溯里曾经重复搜索相同结构，本周就要观察如何把这些重复结构压缩成表格或滚动变量。

## 前置知识

- 能接受一个题目里存在多个候选状态定义，并比较哪一个更容易转移。
- 能写出数组下标含义，避免只凭样例推公式。
- 能区分“当前位置之前的答案”和“包含当前位置的答案”。
- 能处理空输入、首位、前两位这类初始化边界。
- 能判断一维表、二维表和滚动变量分别适合什么场景。
- 能从小样例手推表格，而不是直接写循环。

## 每日计划

### 第 1 天 - 递推入口与一维状态

1. `70. Climbing Stairs` (`简单`) - 从最小规模入手，练习把一个位置的答案和前面位置联系起来。
2. `746. Min Cost Climbing Stairs` (`简单`) - 练习在相邻选择里比较代价，并处理起点选择差异。
3. `198. House Robber` (`中等`) - 练习在相邻限制下决定当前位置是否参与结果。

### 第 2 天 - 路径累计与网格状态

1. `62. Unique Paths` (`中等`) - 练习把二维位置的结果由相邻来源累积出来。
2. `64. Minimum Path Sum` (`中等`) - 在路径累计中加入代价比较，检查首行首列边界。
3. `120. Triangle` (`中等`) - 练习不规则层级结构里的相邻来源选择。

### 第 3 天 - 选择约束与相邻状态

1. `213. House Robber II` (`中等`) - 在首尾互相影响时，练习拆分场景而不是硬套线性过程。
2. `740. Delete and Earn` (`中等`) - 练习把数值选择限制转成相邻限制后再求解。
3. `790. Domino and Tromino Tiling` (`中等`) - 练习在铺满结构里同时维护完整状态和缺口状态。

### 第 4 天 - 目标可达与容量边界

1. `322. Coin Change` (`中等`) - 练习从目标值角度记录最优结果，并处理不可达状态。
2. `416. Partition Equal Subset Sum` (`中等`) - 练习判断目标是否可达，并控制每个输入只能贡献一次。
3. `494. Target Sum` (`中等`) - 练习把符号选择转成目标计数问题，观察约束变形。

### 第 5 天 - 子序列与双序列关系

1. `300. Longest Increasing Subsequence` (`中等`) - 练习定义以当前位置结尾的结果，并比较所有可能来源。
2. `1143. Longest Common Subsequence` (`中等`) - 练习在两个字符串之间维护前缀关系。
3. `72. Edit Distance` (`困难`) - 练习把两个字符串的变化过程拆成多个操作来源。

### 第 6 天 - 字符串前缀与可拆分状态

1. `91. Decode Ways` (`中等`) - 练习在字符串前缀中处理单字符和双字符的合法性。
2. `139. Word Break` (`中等`) - 练习判断一个前缀能否由已有片段组成。
3. `115. Distinct Subsequences` (`困难`) - 练习统计一个字符串形成另一个字符串的方案数。

### 第 7 天 - 综合复盘与区间意识

1. `152. Maximum Product Subarray` (`中等`) - 回顾单序列状态中最大值和最小值同时变化的情况。
2. `309. Best Time to Buy and Sell Stock with Cooldown` (`中等`) - 练习用多个状态表达同一天的不同行为结果。
3. `312. Burst Balloons` (`困难`) - 进入区间型问题，观察一个区间的答案如何由内部切分得到。

## 本周关注清单

- 每题先写一句：`dp[i]` 或 `dp[i][j]` 代表什么，不写清楚不动手。
- 初始化要单独检查，不把边界塞进循环里赌样例通过。
- 每次写循环前确认遍历方向：当前状态依赖的结果是否已经算过。
- 如果状态里有“不可能”或“不可达”，要用明确的哨兵值表示，不和合法答案混淆。
- 遇到二维表时，先手画 `2x2` 或短字符串表格，确认横纵坐标含义。
- 遇到空间优化时，先写清完整表，再考虑滚动变量，不抢一步。
- 每天复盘至少说清一道题的“状态定义 -> 初始条件 -> 转移来源 -> 返回值”四件事。

## 本周节奏建议

- 第 1 天：不追求题量速度，重点练“状态到底表示什么”。
- 第 2 天：把一维推进到二维，重点看边界行列如何初始化。
- 第 3 天：处理相邻限制和拆分场景，不要把环形或数值限制硬塞进线性模板。
- 第 4 天：进入目标可达类问题，重点检查不可达状态和每个输入能否重复使用。
- 第 5 天：进入序列关系，要求每个格子的含义能口头解释。
- 第 6 天：集中处理字符串前缀，尤其是非法字符、空前缀和切分位置。
- 第 7 天：做综合迁移，允许慢一点，但必须能说出为什么当前状态足够表达答案。

## 进度更新 - 2026-06-19

- 今日完成：`70. Climbing Stairs`、`746. Min Cost Climbing Stairs`、`198. House Robber`
- 当前主题：动态规划 / 一维状态

### 通用解题模板

- 适用条件：题目要求按顺序处理位置、台阶、房屋或前缀，当前位置的答案只依赖前面固定数量的结果。
- 核心骨架：先明确 `dp[i]` 的含义，再写初始化；如果每次只依赖前一项或前两项，先用数组确认转移，再压缩成滚动变量。
- 关键边界：`dp[0]` 是否表示空前缀或起点；返回的是最后一个位置、楼顶位置，还是最后两个位置的最优值；付费或选择发生在“到达”还是“离开”。
- 复杂度：时间通常为 `O(n)`；完整表空间为 `O(n)`，滚动变量可降为 `O(1)`。

```cpp
class Solution {
public:
    int linearDpExample(vector<int>& nums) {
        int bestTwoBack = 0;
        int bestOneBack = 0;
        for (int value : nums) {
            // 根据题意决定当前位置是否接在前一项或前两项之后。
            int current = max(bestOneBack, bestTwoBack + value);
            bestTwoBack = bestOneBack;
            bestOneBack = current;
        }
        return bestOneBack;
    }
};
```

### 逐题评价

| 题目 | 完成质量 | 亮点 | 风险或复盘重点 | 详细点评 |
| --- | --- | --- | --- | --- |
| `70. Climbing Stairs` | 通过 | `dp[i]` 状态定义清楚，初始化能自然覆盖基础边界 | 可继续练习把只依赖前两项的状态压缩成滚动变量 | [查看](../leetcode-reviews/2026-06-19-70-climbing-stairs.md) |
| `746. Min Cost Climbing Stairs` | 通过 | 能处理起点选择和最后跨上楼顶的比较 | 当前 `dp` 下标和台阶编号错开一位，建议用“到达第 i 级”的定义重写 | [查看](../leetcode-reviews/2026-06-19-746-min-cost-climbing-stairs.md) |
| `198. House Robber` | 通过 | 同时写出一维最优值和二维选/不选状态，说明相邻限制理解扎实 | 提交时可以收敛到一版，并用滚动变量减少特判和空间 | [查看](../leetcode-reviews/2026-06-19-198-house-robber.md) |

- 暴露问题：整体已经能写出基本转移；下一步要把“状态到底表示哪个位置/前缀”说得更精确，尤其是 746 这种返回楼顶而不是某一级台阶的题。
- 下一步安排：继续进入第 2 天，把一维状态迁移到二维位置累计。

## 进度更新 - 2026-06-20

- 今日完成：`62. Unique Paths`、`64. Minimum Path Sum`、`120. Triangle`
- 当前主题：动态规划 / 网格与层级状态

### 通用解题模板

- 适用条件：题目在二维网格、三角形层级或相邻层之间移动，当前位置的结果由上方、左方、左上方或下一层相邻位置推出。
- 核心骨架：先确定 `dp[row][col]` 表示“到达当前位置”还是“从当前位置出发到终点”；再根据移动方向决定遍历顺序。
- 关键边界：首行、首列、三角形左右边界、起点和终点语义要单独检查；压缩成一维数组时，必须确认当前 `dp[col]` 代表上方结果还是已经更新过的当前行结果。
- 复杂度：矩形网格通常时间 `O(m*n)`；三角形通常时间 `O(n^2)`；空间可从完整二维表压缩到一行或一层。

```cpp
class Solution {
public:
    int gridDpExample(vector<vector<int>>& grid) {
        int rows = static_cast<int>(grid.size());
        int cols = static_cast<int>(grid[0].size());
        vector<int> dp(cols, 0);
        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                // 根据题意组合“上方 dp[col]”和“左方 dp[col - 1]”。
                // 首行首列要先决定是初始化、累加，还是视为不可达。
            }
        }
        return dp[cols - 1];
    }
};
```

### 逐题评价

| 题目 | 完成质量 | 亮点 | 风险或复盘重点 | 详细点评 |
| --- | --- | --- | --- | --- |
| `62. Unique Paths` | 通过 | 1-based padding 让上方和左方来源统一，起点处理清楚 | 可继续练习一维压缩，理解 `dp[col]` 同时承载上方和当前行结果 | [查看](../leetcode-reviews/2026-06-20-62-unique-paths.md) |
| `64. Minimum Path Sum` | 通过 | 用大数哨兵挡住非法来源，转移式简洁 | 注意 `dp[i][j]` 与 `grid[i-1][j-1]` 的坐标错位，复盘时要讲清 | [查看](../leetcode-reviews/2026-06-20-64-minimum-path-sum.md) |
| `120. Triangle` | 通过 | 同时写了二维表和一维滚动，左右边界处理完整 | 可以进一步比较自顶向下和自底向上的状态语义差异 | [查看](../leetcode-reviews/2026-06-20-120-triangle.md) |

- 暴露问题：整体二维状态已经比较稳；下一步重点是空间压缩时说清 `dp[col]` 更新前后的含义，避免在一维数组里混淆上一行和当前行。
- 下一步安排：继续进入第 3 天，处理带额外选择约束的状态拆分。

## 进度更新 - 2026-06-21

- 今日完成：`213. House Robber II`、`740. Delete and Earn`、`790. Domino and Tromino Tiling`
- 当前主题：动态规划 / 选择约束与相邻状态

### 通用解题模板

- 适用条件：题目在原始线性选择之外加入首尾相连、数值相邻冲突、缺口轮廓或多种行为状态，导致单个 `dp[i]` 不够直接表达所有限制。
- 核心骨架：先判断能否把复杂限制拆成若干个线性子问题；如果不能拆，就把“当前处于什么状态”显式加入状态维度。
- 关键边界：环形问题要处理 `n == 1`；数值冲突题要先聚合同值收益；多状态计数题要给每个状态命名，并确认初始状态代表空结构还是完整结构。
- 复杂度：拆分线性问题通常时间 `O(n)`、空间可 `O(1)`；按值域聚合通常时间 `O(n + M)`；固定数量多状态通常时间 `O(n)`、空间 `O(1)`。

```cpp
class Solution {
    int solveLinear(const vector<int>& nums, int left, int right) {
        int bestTwoBack = 0;
        int bestOneBack = 0;
        for (int i = left; i <= right; i++) {
            // 根据当前限制决定“选当前”和“不选当前”的来源。
            int current = max(bestOneBack, bestTwoBack + nums[i]);
            bestTwoBack = bestOneBack;
            bestOneBack = current;
        }
        return bestOneBack;
    }

public:
    int constrainedDpExample(vector<int>& nums) {
        if (nums.size() == 1) return nums[0];
        return max(solveLinear(nums, 0, static_cast<int>(nums.size()) - 2),
                   solveLinear(nums, 1, static_cast<int>(nums.size()) - 1));
    }
};
```

### 逐题评价

| 题目 | 完成质量 | 亮点 | 风险或复盘重点 | 详细点评 |
| --- | --- | --- | --- | --- |
| `213. House Robber II` | 通过 | 能把环形首尾限制拆成两个线性范围，复用了第 1 天的相邻选择模型 | 两段线性 DP 代码重复，可抽成区间函数并压缩空间 | [查看](../leetcode-reviews/2026-06-21-213-house-robber-ii.md) |
| `740. Delete and Earn` | 通过 | 成功把数值相邻冲突转成打家劫舍模型，并使用滚动变量 | `a/b/ans` 命名偏抽象，建议改成表达前两项和前一项的语义名 | [查看](../leetcode-reviews/2026-06-21-740-delete-and-earn.md) |
| `790. Domino and Tromino Tiling` | 通过 | 四状态转移正确，取模处理完整，已经做到常数空间 | `dp[0..3]` 的状态编号需要改成语义状态，方便复盘和防止转移写反 | [查看](../leetcode-reviews/2026-06-21-790-domino-and-tromino-tiling.md) |

- 暴露问题：今天的核心转移都写对了；主要改进点不是算法正确性，而是把“拆分后的线性范围”和“多状态编号”命名得更可解释。
- 下一步安排：继续进入第 4 天，开始处理目标可达、容量边界和不可达状态。

## 进度更新 - 2026-06-24

- 今日完成：`322. Coin Change`、`416. Partition Equal Subset Sum`、`494. Target Sum`
- 当前主题：动态规划 / 目标可达与容量边界

### 通用解题模板

- 适用条件：题目要求凑出某个目标值、判断目标是否可达、求最少数量或统计方案数，并且每个输入元素存在“可重复使用”或“只能使用一次”的限制。
- 核心骨架：先定义 `dp[target]` 表示最小代价、是否可达或方案数；再根据元素是否可重复决定容量遍历方向。
- 关键边界：`dp[0]` 的含义必须明确；不可达状态要用哨兵或 `false` 表示；计数题初始化通常是 `dp[0] = 1`；每个元素只能用一次时容量倒序，可重复使用时容量正序。
- 复杂度：常见时间为 `O(n * target)` 或 `O(target * n)`，空间可压缩为 `O(target)`。

```cpp
class Solution {
public:
    bool zeroOneReachable(vector<int>& nums, int target) {
        vector<bool> dp(target + 1, false);
        dp[0] = true;
        for (int num : nums) {
            // 每个 num 只能用一次，容量倒序。
            for (int value = target; value >= num; value--) {
                dp[value] = dp[value] || dp[value - num];
            }
        }
        return dp[target];
    }
};
```

### 逐题评价

| 题目 | 完成质量 | 亮点 | 风险或复盘重点 | 详细点评 |
| --- | --- | --- | --- | --- |
| `322. Coin Change` | 通过 | 能用 `amount + 1` 作为不可达哨兵，返回值处理清楚 | 继续区分“可重复使用”对应容量正序，和 416/494 的倒序形成对照 | [查看](../leetcode-reviews/2026-06-24-322-coin-change.md) |
| `416. Partition Equal Subset Sum` | 有实现风险 | 核心转换和倒序容量更新正确 | `maxNum` 未初始化会造成未定义行为，需初始化或删除该剪枝 | [查看](../leetcode-reviews/2026-06-24-416-partition-equal-subset-sum.md) |
| `494. Target Sum` | 通过 | 能把符号选择转换成目标和方案数，`dp[0] = 1` 初始化正确 | 复盘时注意它和 416 的区别：一个是布尔可达，一个是方案计数 | [查看](../leetcode-reviews/2026-06-24-494-target-sum.md) |

- 暴露问题：容量类题整体框架已经建立；最需要补强的是实现细节里的初始化纪律，尤其是局部变量必须有确定初值。
- 下一步安排：继续进入第 5 天，处理子序列与双序列关系。

## 进度更新 - 2026-06-25

- 今日完成：`300. Longest Increasing Subsequence`、`1143. Longest Common Subsequence`、`72. Edit Distance`、`91. Decode Ways`、`139. Word Break`、`115. Distinct Subsequences`
- 当前主题：动态规划 / 子序列、双序列与字符串前缀

### 通用解题模板

- 适用条件：题目涉及一个序列的子序列选择、两个字符串前缀之间的关系、字符串能否按合法片段拆分，或统计从一个字符串形成另一个字符串的方案数。
- 核心骨架：单序列题先判断状态是否表示“以当前位置结尾”；双序列题优先定义 `dp[i][j]` 为两个前缀或后缀之间的答案；字符串拆分题通常让 `dp[i]` 表示前 `i` 个字符是否合法或有多少方案。
- 关键边界：空前缀经常是合法基础状态；双序列题的首行首列要表达空串关系；计数题要分清 `0` 种和 `1` 种基础方案；一维压缩时要明确左上角旧值是否会被覆盖。
- 复杂度：双序列常见时间 `O(m*n)`；前缀切分常见时间 `O(n^2)` 或受最大词长限制；空间通常可从二维表压缩到一行。

```cpp
class Solution {
public:
    int twoSequenceDpExample(string a, string b) {
        int m = static_cast<int>(a.size());
        int n = static_cast<int>(b.size());
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (a[i - 1] == b[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                } else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        return dp[m][n];
    }
};
```

### 逐题评价

| 题目 | 完成质量 | 亮点 | 风险或复盘重点 | 详细点评 |
| --- | --- | --- | --- | --- |
| `300. Longest Increasing Subsequence` | 通过 | `dp[i]` 表示以当前位置结尾，严格递增条件处理正确 | 当前是 `O(n^2)`，建议补 `tails + lower_bound` 优化写法 | [查看](../leetcode-reviews/2026-06-25-300-longest-increasing-subsequence.md) |
| `1143. Longest Common Subsequence` | 通过 | 双前缀状态和相等/不等分支都很标准 | 可进一步练习一维压缩时如何保存左上角旧值 | [查看](../leetcode-reviews/2026-06-25-1143-longest-common-subsequence.md) |
| `72. Edit Distance` | 通过 | 首行首列初始化完整，三种操作来源表达准确 | 复盘时要能说清上、左、左上分别对应删除、插入、替换 | [查看](../leetcode-reviews/2026-06-25-72-edit-distance.md) |
| `91. Decode Ways` | 通过 | 单字符和双字符合法性分开判断，`0` 的处理清楚 | 可压缩空间，并补测 `"0"`、`"10"`、`"100"` | [查看](../leetcode-reviews/2026-06-25-91-decode-ways.md) |
| `139. Word Break` | 通过 | 前缀可拆状态明确，词典哈希使用正确 | `substr` 枚举有额外成本，可用最大词长减少无效尝试 | [查看](../leetcode-reviews/2026-06-25-139-word-break.md) |
| `115. Distinct Subsequences` | 通过 | 后缀状态和空目标串边界都很稳，计数语义正确 | 可练一维倒序写法，理解它和二维后缀状态的等价关系 | [查看](../leetcode-reviews/2026-06-25-115-distinct-subsequences.md) |

- 暴露问题：今天总体完成质量高；后续主要补强空间压缩时的“旧左上角”保存，以及区分布尔可达、最值和方案计数三类状态的初始化。
- 下一步安排：继续进入第 7 天综合复盘，把单序列、多状态、容量、双序列几类 DP 放在一起做迁移。

## 进度更新 - 2026-06-26

- 今日完成：`152. Maximum Product Subarray`、`309. Best Time to Buy and Sell Stock with Cooldown`、`312. Burst Balloons`
- 当前主题：动态规划 / 综合复盘与区间意识

### 通用解题模板

- 适用条件：题目中的答案不能只由一个简单前缀状态表达，需要额外记录最大/最小、持有/不持有、冷冻/卖出、区间边界或最后一个操作位置。
- 核心骨架：先问“当前状态是否足够表达未来转移”；如果不够，就增加状态维度；区间题优先考虑枚举最后一次操作，让左右边界固定。
- 关键边界：单序列滚动状态必须保存旧值；多状态题要给每个状态命名；区间题要明确开闭区间和空区间返回值；补虚拟边界时要确认返回的是原问题完整区间。
- 复杂度：单序列多状态通常 `O(n)`；固定行为状态可压缩到 `O(1)`；区间切分常见 `O(n^3)` 时间和 `O(n^2)` 空间。

```cpp
class Solution {
public:
    int intervalDpExample(vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        vector<vector<int>> dp(n, vector<int>(n, 0));
        for (int len = 2; len <= n; len++) {
            for (int left = 0; left + len - 1 < n; left++) {
                int right = left + len - 1;
                for (int mid = left; mid <= right; mid++) {
                    // 枚举区间里的关键切分点或最后一次操作位置。
                }
            }
        }
        return n == 0 ? 0 : dp[0][n - 1];
    }
};
```

### 逐题评价

| 题目 | 完成质量 | 亮点 | 风险或复盘重点 | 详细点评 |
| --- | --- | --- | --- | --- |
| `152. Maximum Product Subarray` | 通过 | 同时维护最大和最小结尾状态，正确处理负数翻转 | 复盘时要能解释为什么只维护最大值不够 | [查看](../leetcode-reviews/2026-06-26-152-maximum-product-subarray.md) |
| `309. Best Time to Buy and Sell Stock with Cooldown` | 通过 | 能用多个状态表达持有、卖出、冷冻等行为结果 | 状态命名可进一步语义化，并压缩到常数空间 | [查看](../leetcode-reviews/2026-06-26-309-best-time-to-buy-and-sell-stock-with-cooldown.md) |
| `312. Burst Balloons` | 通过 | 正确使用开区间和“最后戳”建模，记忆化避免重复计算 | 建议再写一遍自底向上的区间 DP，巩固区间长度遍历 | [查看](../leetcode-reviews/2026-06-26-312-burst-balloons.md) |

- 暴露问题：本周最后一天整体表现很好；现在主要不是“会不会写转移”，而是要把状态语义、遍历顺序和边界返回值讲得足够稳定。
- 下一步安排：第 8 周动态规划主线已完成。后续建议做一次总复盘，把题目按“一维最值 / 目标容量 / 双序列 / 多状态 / 区间”五类重新归档。
