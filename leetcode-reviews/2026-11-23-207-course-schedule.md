# 题解点评 - 207. Course Schedule（课程表）

## 基本信息

- 日期：2026-11-23
- 主题：第 12 周拓扑排序与并查集 - 入度与依赖入口（第 1 天）
- 难度：中等
- 本次结果：通过（用户确认已通过测试）
- 对应源码：[src/207.course-schedule.cpp](../src/207.course-schedule.cpp)
- 资料来源：[LeetCode 中国版官方题目页](https://leetcode.cn/problems/course-schedule/)，2026-11-23 查询
- 约束要点：`1 <= numCourses <= 2000`；`0 <= prerequisites.length <= 5000`，课程对互不相同（无重边）

## 用户思路概述

1. 邻接表 `graph[v] → u`：先修 `v` 完成后可以解锁 `u`；`pre[u]` 即 u 的剩余入度（未满足的先修数）。
2. 初始扫描把所有 `pre[i] == 0` 的课入队并计数。
3. 出队时遍历其解锁列表，把后继入度减 1；减到 0 则入队再计数。
4. `ans == numCourses` 即全部课程可排完（无环），否则说明有环上课程入度永不清零。

## 用户解法复杂度

- 时间复杂度：`O(V + E)`（每点入队出队一次、每条边引发一次入度递减）
- 空间复杂度：`O(V + E)`（邻接表 + 度数数组 + 队列）
- 复杂度来源：Kahn 算法标准形态；本题只问可行性，用计数 `ans` 免去了结果数组。

## 用户代码注释版

> 只在点评文档中展示加注释版本；不把这些注释写回 `src/*.cpp` 的用户原代码。

```cpp
class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> graph(numCourses);
        vector<int> pre(numCourses, 0);
        for(auto prereq: prerequisites) {
            int u=prereq[0], v=prereq[1];
            graph[v].push_back(u);   // 先修 v 解锁 u：从 v 到 u 的"开后继"边
            pre[u]++;               // u 的剩余入度：还差多少先修
        }
        int ans=0;
        queue<int> q;
        for(int i=0; i<numCourses; i++) {
            if(pre[i] == 0) {        // 入度 0：无先修，立即可修
                q.push(i);
                ans++;
            }
        }
        while(!q.empty()) {
            auto u=q.front(); q.pop();
            for(auto v: graph[u]) {  // u 修完解锁的后继课程
                pre[v]--;           // 满足一个先修
                if(pre[v]==0) {     // 全部先修满足：轮到它了
                    q.push(v);
                    ans++;
                }
            }
        }
        return ans == numCourses;   // 有环时环上课程入度永不清零，计数不齐


    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 边方向建模 | `graph[v]→u`（完成后解锁方向） | 正确选择"完成→解锁"方向的边——这样入队即"此课已可修"，语义自然 | 想清反方向（先修指向后继）能不能做：能（DFS 三色判环），但 Kahn 队列在本方向下语义最顺 |
| 入度语义 | `pre[u]` = 未满足先修数 | "入度清零即条件齐备"是拓扑排序的核心不变量，命名 `pre` 语义贴切 | 与 997 衔接：入度从"静态性质"升级为"动态清零的进度" |
| 判环方式（隐式） | `ans == numCourses` | 不需要显式找环——出队总数不足即存在环，这是 Kahn 判环的间接形态 | 复述"环上的点为什么永远不入场"：每条环内边都不会被处理，入度无法归零 |
| 计数代替序列 | 本题只问可行性，`ans` 免结果数组 | 比 210 的序列版少一个数组，恰当的最简 | 已达标 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法（Kahn 入度清零） | `O(V+E)` 最优；迭代无爆栈风险；判环间接完成 | 无 | 依赖调度的标准解 |
| DFS 三色标记（0/1/2 染色判环） | 同 `O(V+E)`；对"找具体环"更方便 | 递归深度 V=2000 本题安全，更大规模需迭代化 | 与 Kahn 等价的第二脉络 |
| 拓扑排序后逐边验证 | 概念直白 | 多余的一步 | 不必要 |

## 最优解法

1. 邻接表（完成→解锁方向）+ 入度数组。
2. 入度 0 者全部入队；出队 u 后对其每个后继入度减 1，减为 0 则入队。
3. 出队计数 == 节点总数 ⟺ 无环 ⟺ 可修完。
- 关键不变量：**入队恰在"所有先修已出队"的时刻发生**；环上任何点的入队条件永远无法达成。
- 最优时间复杂度：`O(V + E)`
- 最优空间复杂度：`O(V + E)`

### 最优解代码

```cpp
class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> next(numCourses); // next[v]: 完成 v 后解锁的课
        vector<int> indeg(numCourses, 0);    // 剩余未满足的先修数
        for (const auto& p : prerequisites) {
            next[p[1]].push_back(p[0]);       // p[1] 是 p[0] 的先修
            indeg[p[0]]++;
        }
        queue<int> q;
        int done = 0; // 已确定可修的课程数
        for (int i = 0; i < numCourses; i++) {
            if (indeg[i] == 0) { // 无先修：立即可修
                q.push(i);
                done++;
            }
        }
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : next[u]) {
                if (--indeg[v] == 0) { // 先修全部满足：轮到 v
                    q.push(v);
                    done++;
                }
            }
        }
        return done == numCourses; // 环上课程入度永不清零 → 计数不齐
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 图结构 | 邻接表（解锁方向） | 相同 | 已配套 |
| 更新逻辑 | 入度清零入队 + 计数 | 相同 | 已达标 |
| 边界处理 | 空先修表（全部可修）、自环（ai==bi 会构成永不清零的入度 → false）均自动正确 | 相同 | 自环情形想一遍：本题约束未排除 ai==bi（207 允许），自环课永远不可修 |
| 复杂度 | `O(V+E)` / `O(V+E)` | 相同 | 已达最优 |

用户解法与推荐最优解逐行同构，本题完成质量高。

## 下一步建议

- 复盘任务：写出 207 与 210 的五分钟互相改写清单——"计数换序列"只涉及 3 处改动，确认两题本质是同一个算法。
- 衔接任务：第 2 天的 802 会把"终端即入度 0"的视角反转（终端改为出度 0），提前想一遍出度/入度两个方向的对称性。

## 后续练习

1. `210. Course Schedule II` - 同日题单，从可行性升级为输出顺序。
2. `802. Find Eventual Safe States` - 第 2 天题单，"终端"定义翻转后反向建图的对称练习。

## 代码同步

- 已将最优解作为新的解题函数写入：[src/207.course-schedule.cpp](../src/207.course-schedule.cpp)
- 新函数名：`canFinishOpt`，位于原 `class Solution` 中 `public:` 之前的私有区域
- 保留用户原实现：是
