# 题解点评 - 1326. Minimum Number of Taps to Open to Water a Garden（灌溉花园的最少水龙头数目）

## 基本信息

- 日期：2026-11-11
- 主题：第 10 周区间与贪心 - 可达性与跳跃
- 难度：困难
- 本次结果：通过（用户确认已测试通过）
- 对应源码：[src/1326.minimum-number-of-taps-to-open-to-water-a-garden.cpp](../src/1326.minimum-number-of-taps-to-open-to-water-a-garden.cpp)
- 资料来源：[LeetCode 中国版官方题目页](https://leetcode.cn/problems/minimum-number-of-taps-to-open-to-water-a-garden/)，2026-11-11 查询
- 约束要点：`1 <= n <= 10^4`，`ranges.length == n + 1`，`0 <= ranges[i] <= 100`；花园与浇灌区域均为闭区间 `[0, n]`；无法覆盖全花园时返回 `-1`

## 用户思路概述

1. 预处理：把每个水龙头 `i` 转成闭区间 `[i - ranges[i], i + ranges[i]]`，截断到 `[0, n]` 后，记录 `rightMost[left] = max(rightMost[left], right)`——即"从每个左端点出发，能覆盖到的最远右端点"。
2. `rightMost` 初始化为 `iota`（`rightMost[i] = i`），自然表达"半径为 0 的水龙头只能覆盖点自身"。
3. 扫描阶段完全复用 45 的分层骨架：维护 `r`（当前层能覆盖到的最远右端）、`pre`（当前层边界）、`ans`。每轮 `r = max(r, rightMost[l])`；若 `l == r` 说明出现覆盖不到的空隙，返回 `-1`；若 `l == pre` 则结算一次（`ans++`，`pre = r`）。
4. 扫描覆盖 `0` 到 `n-1` 各位置后返回 `ans`。

## 用户解法复杂度

- 时间复杂度：`O(n)`（预处理和扫描各一趟）
- 空间复杂度：`O(n)`（`rightMost` 数组）
- 复杂度来源：预处理把每个水龙头写入一次 `rightMost`；扫描对每个位置 `0..n-1` 各访问一次。

## 用户代码注释版

> 只在点评文档中展示加注释版本；不把这些注释写回 `src/*.cpp` 的用户原代码。

```cpp
class Solution {
public:
    int minTaps(int n, vector<int>& ranges) {
        // rightMost[i]：所有左端点恰为 i 的水龙头中，能覆盖到的最远右端点
        vector<int> rightMost(n+1);
        iota(rightMost.begin(), rightMost.end(), 0); // 默认只能覆盖点自身
        for(int i=0; i<=n; i++) {
            int left = max(0, i-ranges[i]);   // 区间截断到 [0, n]
            int right = min(n, i+ranges[i]);
            rightMost[left] = max(rightMost[left], right); // 同左端点取覆盖更远者
        }
        int l=0, r=0, ans=0, pre=0;
        // pre：当前已选水龙头恰好连续覆盖到的边界；r：本层候选能延伸的最远右端
        for(l=0; l<n; l++) {
            r = max(r, rightMost[l]);
            if(l == r) return -1;   // 位置 l 之后无法继续覆盖，出现空隙
            if(l == pre) {          // 当前层结算：必须再开一个水龙头
                ans++;
                pre = r;
            }
        }
        return ans;
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 区间到跳跃模型的转换 | `rightMost[left] = max(right)` 把"开哪些水龙头"转成"从每个位置最远覆盖到哪" | 这是本题最难的一步，转换正确说明 45 的模式真正迁移成功，是今日最大亮点 | 复盘时能独立复述"为什么同一左端点只需保留覆盖最远的一个" |
| `iota` 初始化 | 未开任何水龙头时 `rightMost[i] = i` | 正确处理 `ranges[i] = 0` 的水龙头（只覆盖点自身，不延伸），边界干净 | 已达标 |
| 空隙判定 | `l == r` 时返回 `-1` | 正确：`r` 是所有左端点 `<= l` 的区间能延伸的最远右端，`r == l` 意味着 `l+1` 起无法覆盖 | 想清"为什么不用担心左端点在 `l` 之后的区间"——它们不覆盖位置 `l`，不影响判定 |
| 结算时机 | `l == pre` 时 `ans++` | 与 45 的层边界一致；覆盖恰好推进到 `pre` 时必须引入新水龙头 | 已达标 |
| 命名 | `pre` 表示层边界 | 次要级问题：`pre` 不如 `boundary` 直观，且 `l`/`r` 沿用区间命名 | 统一用 `i`/`farthest`/`boundary` 命名可减少跨题迁移成本 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法（区间转跳跃 + 分层计数） | `O(n)`/`O(n)`，线性最优；完整复用 45 骨架，迁移性最强；空隙判定自然 | 需要一步建模转换，若不熟悉跳跃模型较难想到 | 区间覆盖整条线段的最少数量问题 |
| 动态规划解 | 思路直接（`dp[i]` = 覆盖到 `i` 的最少数量），不需要建模转换 | `O(n × 100)` 时间，常数更大；与本周"边界推进"主题脱节，不利于迁移 | 对贪心证明没把握时的保底方案，本次不展开 |

## 最优解法

1. 预处理：对每个水龙头 `i`，取 `left = max(0, i - ranges[i])`、`right = min(n, i + ranges[i])`，令 `rightMost[left] = max(rightMost[left], right)`；`rightMost` 初始化为下标自身。
2. 扫描位置 `0..n-1`：维护 `far`（所有左端点不超过当前位置的区间能延伸的最远右端）与 `boundary`（已选水龙头恰好连续覆盖到的边界）。
3. 若某位置 `far == i`，说明 `i+1` 无法被覆盖，返回 `-1`；当 `i == boundary` 时结算一次（答案加一，`boundary = far`）。
4. 扫描结束返回答案。
- 关键不变量：`boundary` 是"已选 `ans` 个水龙头恰好连续覆盖的最远位置"；`far` 单调不减，等价于跳跃游戏中的最远可达。
- 最优时间复杂度：`O(n)`
- 最优空间复杂度：`O(n)`

### 最优解代码

```cpp
class Solution {
public:
    int minTaps(int n, vector<int>& ranges) {
        // rightMost[i]：左端点为 i 的水龙头能覆盖到的最远右端点
        vector<int> rightMost(n + 1);
        iota(rightMost.begin(), rightMost.end(), 0);
        for (int i = 0; i <= n; i++) {
            int left = max(0, i - ranges[i]);   // 浇灌区间截断到 [0, n]
            int right = min(n, i + ranges[i]);
            rightMost[left] = max(rightMost[left], right);
        }
        int ans = 0;
        int far = 0;      // 本层候选能延伸的最远右端
        int boundary = 0; // 已选水龙头恰好连续覆盖到的边界
        for (int i = 0; i < n; i++) {
            far = max(far, rightMost[i]);
            if (far == i) return -1; // 出现覆盖不到的空隙
            if (i == boundary) {     // 当前层结算：需要新开一个水龙头
                ans++;
                boundary = far;
            }
        }
        return ans;
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | `l`/`r`/`pre` | `i`/`far`/`boundary` | 命名与 55、45 统一后，三题骨架完全同形 |
| 更新逻辑 | `max` 扩张 + 层结算 | 相同 | 已达标 |
| 边界处理 | 区间截断、`ranges[i]=0`、空隙 `-1` 均正确 | 相同 | 已达标 |
| 复杂度 | 时间 `O(n)`、空间 `O(n)` | 相同 | 已达最优 |

用户解法与推荐最优解在结构和复杂度上完全一致，本题是今日三题中完成质量最高的一题：困难题上独立完成了"区间覆盖 → 边界推进"的建模转换。

## 下一步建议

- 进入下一题单：第 3 天三题全部通过，其中 1326 是困难题且一次通过，本周节奏良好。
- 复盘任务：不看题解，向别人讲清 1326 的两步——"为什么每个左端点只保留覆盖最远的水龙头"和"为什么空隙判定只需比较 `far` 和当前位置"。

## 后续练习

1. `763. Partition Labels` - 第 4 天题单，"推进到一个边界才结算"的字符串版本，直接检验分层思想迁移。
2. `1024. Video Stitching` - 同为区间覆盖整条线段的最少数量问题，与 1326 互为变体，适合作为周末回顾加练。

## 代码同步

- 已将最优解作为新的解题函数写入：[src/1326.minimum-number-of-taps-to-open-to-water-a-garden.cpp](../src/1326.minimum-number-of-taps-to-open-to-water-a-garden.cpp)
- 新函数名：`minTapsOpt`，位于原 `class Solution` 中 `public:` 之前的私有区域
- 保留用户原实现：是
