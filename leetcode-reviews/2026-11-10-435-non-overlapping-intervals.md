# 题解点评 - 435. Non-overlapping Intervals（无重叠区间）

## 基本信息

- 日期：2026-11-10
- 主题：第 10 周区间与贪心 - 区间选择与删除
- 难度：中等
- 本次结果：通过（用户确认已测试通过）
- 对应源码：[src/435.non-overlapping-intervals.cpp](../src/435.non-overlapping-intervals.cpp)
- 资料来源：[LeetCode 中国版官方题目页](https://leetcode.cn/problems/non-overlapping-intervals/)，2026-11-10 查询
- 约束要点：`1 <= intervals.length <= 10^5`，`-5*10^4 <= start < end <= 5*10^4`；端点接触不算重叠（`[1,2]` 与 `[2,3]` 互不重叠）

## 用户思路概述

用户在同一文件里写了两个等价实现，公开接口当前采用 `s2`：

1. `s1`：按左端点排序后扫描，维护当前已保留区间的右边界 `r`；遇到 `intervals[i][0] < r` 视为冲突，移除计数加一，并用 `min(r, intervals[i][1])` 保留结束更早的一方。
2. `s2`：按右端点排序后扫描，维护当前保留链的结束位置 `r`；`intervals[i][0] >= r` 时该区间可保留，保留计数 `cnt` 加一并推进 `r`。
3. 公开函数 `eraseOverlapIntervals` 返回 `s2` 的 `n - cnt`，即最少移除数。

## 用户解法复杂度

- 时间复杂度：`O(n log n)`（排序主导，扫描为 `O(n)`）
- 空间复杂度：`O(log n)`（排序栈，不计输入）
- 复杂度来源：两个实现各做一次完整排序；扫描本身只维护常数个变量，无额外存储。

## 用户代码注释版

> 只在点评文档中展示加注释版本；不把这些注释写回 `src/*.cpp` 的用户原代码。

```cpp
class Solution {
    int s1(vector<vector<int>>& intervals) {
        // 视角一：按左端点排序，冲突时"移除结束更晚的一方"
        int n=intervals.size();
        sort(intervals.begin(), intervals.end());
        int ans=0, r=intervals[0][1]; // r：当前保留链的右边界
        for(int i=1; i<n; i++) {
            if(intervals[i][0] < r) {
                ans ++;                          // 发生冲突，必移除一个
                r = min(r, intervals[i][1]);     // 关键：保留结束更早者，给后续留余地
            } else {
                r = intervals[i][1];             // 无冲突，直接采纳
            }
        }
        return ans;
    }

    int s2(vector<vector<int>>& intervals) {
        // 视角二：按右端点排序，直接数"最多能保留多少个互不重叠区间"
        int n=intervals.size();
        sort(intervals.begin(), intervals.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[1] < b[1];
        });
        int cnt=1, r=intervals[0][1];            // cnt：不重叠保留数，首区间必保留
        for(int i=1; i<n; i++) {
            if(intervals[i][0] >= r) {           // 端点相接不算重叠，用 >= 
                cnt++;
                r = intervals[i][1];
            }
        }
        return n-cnt;                           // 移除数 = 总数 - 保留数
    }

public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        // return s1(intervals);
        return s2(intervals);
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 两种排序视角的等价性 | `s1` 和 `s2` 都正确，且能同时写出 | 说明对"保留谁更安全"理解扎实，是亮点 | 复盘时练习口头证明：为什么右端点排序下"第一个区间必属于某个最优解" |
| `s1` 的 `min` 修正 | 冲突时用 `min(r, intervals[i][1])` 保留结束早者 | 这一步是左端点视角的正确性核心，漏掉会得到错误答案 | 写 `s1` 时先写一句注释提醒自己：移除的不是当前区间，而是两者中结束更晚的 |
| 端点接触语义 | `s2` 用 `>=` 判定可保留 | 与题意"只在一点接触不重叠"一致，正确 | 区间题先确认闭开语义再定比较符，这是本周易错点之一 |
| 空输入假设 | `s1`/`s2` 均直接取 `intervals[0]` | 本题约束 `n >= 1`，安全；但模板迁移到其他题时是隐患 | 通用模板里保留 `n == 0` 的显式判断或确认约束后再省略 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户 `s2`（右端点排序数保留数） | 一次排序一趟扫描；"保留链结束位置"单调推进，无需回退修正；与 452 推荐解同构，迁移性强 | 答案要绕一步 `n - cnt`，语义比直接数移除略间接 | 需要最大化互不重叠区间数的场景 |
| 用户 `s1`（左端点排序冲突修正） | 直接数移除数，语义直观；强化"冲突时保留谁"的判断 | 冲突时必须做 `min` 修正，多一个易错点 | 适合用来对照理解两种视角的差异 |

## 最优解法

1. 将区间按右端点升序排序；若右端点相同，顺序不影响正确性。
2. 维护当前保留链的结束位置 `endSoFar`，初始化为排序后首区间的右端点，保留数初始化为 1。
3. 扫描后续区间：起点 `>= endSoFar` 则可保留（端点接触不算重叠），推进 `endSoFar` 并累加保留数。
4. 返回 `n - 保留数`。

- 关键不变量：`endSoFar` 始终是当前保留链中最晚的结束位置；按右端点排序保证每个新冲突的区间只需与这一个值比较，且"结束最早的区间"必可保留在某个最优解中。
- 最优时间复杂度：`O(n log n)`
- 最优空间复杂度：`O(log n)`（排序栈）

### 最优解代码

```cpp
class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        // 按右端点升序：结束最早的区间一定可以保留在某个最优解中
        sort(intervals.begin(), intervals.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[1] < b[1];
        });
        int keep = 1;
        int endSoFar = intervals[0][1]; // 当前保留链的结束位置
        for (int i = 1; i < static_cast<int>(intervals.size()); i++) {
            // 端点接触不算重叠，起点 >= 结束位置即可直接保留
            if (intervals[i][0] >= endSoFar) {
                keep++;
                endSoFar = intervals[i][1];
            }
        }
        return static_cast<int>(intervals.size()) - keep;
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | `s2` 维护保留数 `cnt` 与结束位置 `r` | 相同结构（`keep`、`endSoFar`） | 已达标；命名上 `endSoFar` 比 `r` 更自解释 |
| 更新逻辑 | 无冲突时推进 `r`，冲突时跳过 | 相同 | 已达标 |
| 边界处理 | 依赖 `n >= 1`，本题成立 | 同样依赖 `n >= 1` | 迁移到无下界保证的题时补判断 |
| 复杂度 | 时间 `O(n log n)`、空间 `O(log n)` | 相同 | 已达最优 |

用户 `s2` 与推荐最优解在结构和复杂度上完全一致，本次同步的最优解函数主要价值是把命名和注释固定成可迁移的模板形态。

## 下一步建议

- 进入下一题：本题两种视角都已掌握，`s2` 已是标准最优形态。
- 复盘任务：对着 `s1` 写一句证明——"冲突时移除结束更晚的一方不会损失最优解"；这和第 10 周目标里的"局部选择证明"直接对应。

## 后续练习

1. `452. Minimum Number of Arrows to Burst Balloons` - 与本题同日题单，右端点视角的直接迁移，但闭区间语义相反（相切算重叠），适合对照比较符差异。
2. `253. Meeting Rooms II` - 同为区间冲突问题，但从"二选一保留"升级为"同时维护多条保留链"，检验本周第 6 天前的基础。

## 代码同步

- 已将最优解作为新的解题函数写入：[src/435.non-overlapping-intervals.cpp](../src/435.non-overlapping-intervals.cpp)
- 新函数名：`eraseOverlapIntervalsOpt`，位于原 `class Solution` 中 `public:` 之前的私有区域
- 保留用户原实现：是（`s1`、`s2` 与公开函数均未改动）
