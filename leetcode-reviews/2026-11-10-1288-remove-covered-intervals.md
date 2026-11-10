# 题解点评 - 1288. Remove Covered Intervals（删除被覆盖区间）

## 基本信息

- 日期：2026-11-10
- 主题：第 10 周区间与贪心 - 区间选择与删除
- 难度：中等
- 本次结果：通过（用户确认已测试通过）
- 对应源码：[src/1288.remove-covered-intervals.cpp](../src/1288.remove-covered-intervals.cpp)
- 资料来源：[LeetCode 中国版官方题目页](https://leetcode.cn/problems/remove-covered-intervals/)，2026-11-10 查询
- 约束要点：`1 <= intervals.length <= 1000`，`0 <= start < end <= 10^5`，所有区间两两不同

## 用户思路概述

1. 自定义排序：左端点升序；左端点相同时右端点降序，保证同起点的区间里更长的先出现。
2. 用第一个区间初始化"当前保留段" `[l, r]`，答案 `ans`（保留数）初始化为 1。
3. 扫描后续区间：若 `intervals[i][1] <= r`，说明该区间被已保留的区间覆盖，跳过；否则它不被覆盖，`ans` 加一，并把 `[l, r]` 更新为该区间。
4. 返回 `ans`，即剩余未被覆盖的区间数。

## 用户解法复杂度

- 时间复杂度：`O(n log n)`（排序主导，扫描为 `O(n)`）
- 空间复杂度：`O(log n)`（排序栈，不计输入）
- 复杂度来源：一次自定义排序；扫描只维护常数个变量。本题 `n <= 1000`，即使平方做法也能通过，但用户解法已是最优级别。

## 用户代码注释版

> 只在点评文档中展示加注释版本；不把这些注释写回 `src/*.cpp` 的用户原代码。

```cpp
class Solution {
public:
    int removeCoveredIntervals(vector<vector<int>>& intervals) {
        int n=intervals.size();
        // 左端点升序、同起点右端点降序：保证同起点的短区间一定排在长区间之后
        sort(intervals.begin(), intervals.end(), [](const vector<int>& a, const vector<int>& b){
            if(a[0] == b[0]) return a[1] > b[1];
            return a[0] < b[0];
        });
        int l=intervals[0][0], r=intervals[0][1]; // [l, r]：最近一个未被覆盖的区间
        int ans = 1;                              // 首区间必不被覆盖
        for(int i=1; i<n; i++) {
            if(intervals[i][1] <= r) {
                continue;        // 排序保证当前左端点 >= 已见左端点，右端点又 <= r，必被覆盖
            } else {
                ans ++;          // 出现新的"最远延伸"，即一个新的未被覆盖区间
                l = intervals[i][0], r = intervals[i][1];
            }
        }
        return ans;
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 排序中"右端点降序"的作用 | 正确写出同起点时右端点降序 | 这是本题最核心的一步：保证同起点的短区间先被长区间"挡住"，不会误判为未覆盖 | 复盘时练习：如果同起点也升序，举一个会出错的输入（如 `[[1,4],[1,6]]`，升序会先见 `[1,4]` 再见 `[1,6]`，`[1,4]` 被漏判为未覆盖） |
| 覆盖判定只需比较右端点 | 用 `intervals[i][1] <= r` 单条件判定 | 排序已保证左端点不小于已见区间，单条件正确且简洁 | 能说出"排序承担了左端点的比较"这句理由 |
| 变量 `l` 未被读取 | 声明并更新 `l`，但从未参与判定 | 次要级问题：死变量增加复盘噪音 | 删掉 `l`，或意识到 `r` 实际是"历史最大右端点" |
| `r` 的真实语义 | `r` 单调不减，等价于已处理区间的最大右端点 | 理解这一点后，解法可简化为"维护 maxRight，统计被覆盖数" | 与推荐最优解对照 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法（维护当前保留段） | 排序依据正确；单条件覆盖判定简洁；`ans` 直接就是答案 | 维护的 `[l, r]` 名义上是"当前段"，实际判定只依赖历史最大右端点，`l` 是死变量 | 判定"被覆盖"类问题 |
| 推荐最优解（维护历史最大右端点） | 状态语义最诚实：一个变量 `maxRight`；返回 `n - covered` 与"删除"题意直接对应 | 与用户解法复杂度完全相同，只是表述更精简 | 同上，且更容易迁移到"只关心右端点最值"的变体 |

## 最优解法

1. 排序：左端点升序，相同时右端点降序。
2. 维护已处理区间的最大右端点 `maxRight`，初始化为排序后首区间的右端点；被覆盖计数初始化为 0。
3. 扫描后续区间：右端点 `<= maxRight` 则被覆盖，计数加一；否则更新 `maxRight` 为该右端点。
4. 返回 `n - 被覆盖数`。

- 关键不变量：`maxRight` 是目前为止见过的最大右端点；排序保证当前区间左端点不小于任何已见区间左端点，因此"右端点不超过 `maxRight`"当且仅当"被某个已见区间覆盖"。
- 最优时间复杂度：`O(n log n)`
- 最优空间复杂度：`O(log n)`（排序栈）

### 最优解代码

```cpp
class Solution {
public:
    int removeCoveredIntervals(vector<vector<int>>& intervals) {
        // 左端点升序、同起点右端点降序：长区间先出现，同起点的短区间必被覆盖
        sort(intervals.begin(), intervals.end(), [](const vector<int>& a, const vector<int>& b) {
            if (a[0] != b[0]) return a[0] < b[0];
            return a[1] > b[1];
        });
        int covered = 0;
        int maxRight = intervals[0][1]; // 已处理区间的最大右端点
        for (int i = 1; i < static_cast<int>(intervals.size()); i++) {
            // 排序已保证左端点条件成立，只需比较右端点
            if (intervals[i][1] <= maxRight) {
                covered++;
            } else {
                maxRight = intervals[i][1];
            }
        }
        return static_cast<int>(intervals.size()) - covered;
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | `[l, r]`"当前保留段"（`l` 未被使用） | 单变量 `maxRight` | 让状态名与真实使用方式一致，减少复盘时的误读 |
| 更新逻辑 | 未覆盖时重置 `l`、`r` | 只在延伸时更新 `maxRight` | 意识到 `r` 从不回退，等价于前缀最大值 |
| 边界处理 | 首区间计入 `ans=1`，依赖 `n >= 1` | 同样依赖 `n >= 1` | 本题约束保证成立；迁移时先确认 |
| 复杂度 | 时间 `O(n log n)`、空间 `O(log n)` | 相同 | 已达最优 |

用户解法与推荐最优解在复杂度和正确性上完全一致，差异只在状态表述；本次同步的最优解主要价值是展示"历史最大右端点"这一更可迁移的表述。

## 下一步建议

- 进入下一题单：本题已通过，判定逻辑正确，第 2 天三题全部完成。
- 复盘任务：口头回答"为什么排序里右端点要降序"和"`r` 为什么可以理解为历史最大右端点"，这两点想清楚，本题模式就完全内化了。

## 后续练习

1. `56. Merge Intervals` - 已完成，可回头对照：合并题维护的是"当前段右边界"，本题维护的是"历史最大右边界"，两者何时等价、何时不同。
2. `1326. Minimum Number of Taps to Open to Water a Garden` - 第 3 天题单，把"区间之间的包含/相交关系"升级为"区间对整条数轴的覆盖"，是本周覆盖类思想的收口。

## 代码同步

- 已将最优解作为新的解题函数写入：[src/1288.remove-covered-intervals.cpp](../src/1288.remove-covered-intervals.cpp)
- 新函数名：`removeCoveredIntervalsOpt`，位于原 `class Solution` 中 `public:` 之前的私有区域
- 保留用户原实现：是
