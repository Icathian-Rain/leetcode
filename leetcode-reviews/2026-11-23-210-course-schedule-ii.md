# 题解点评 - 210. Course Schedule II（课程表 II）

## 基本信息

- 日期：2026-11-23
- 主题：第 12 周拓扑排序与并查集 - 入度与依赖入口（第 1 天）
- 难度：中等
- 本次结果：通过（用户确认已通过测试）
- 对应源码：[src/210.course-schedule-ii.cpp](../src/210.course-schedule-ii.cpp)
- 资料来源：[LeetCode 中国版官方题目页](https://leetcode.cn/problems/course-schedule-ii/)，2026-11-23 查询
- 约束要点：`1 <= numCourses <= 2000`；`0 <= prerequisites.length <= numCourses*(numCourses-1)`；`ai != bi` 且无重边；无法完成返回**空数组**

## 用户思路概述

1. 与 207 完全同构：邻接表（完成→解锁）+ 入度数组 `pre`。
2. 初始入度 0 者入队并**按序写入结果 `ans`**；出队 u 后把后继入度减 1，清零者入队并追加。
3. 入队顺序即拓扑序（BFS 按层推进保证先修先出）。
4. `ans.size() == numCourses` 返回 `ans`，否则返回 `{}`。

## 用户解法复杂度

- 时间复杂度：`O(V + E)`
- 空间复杂度：`O(V + E)`（不计输出数组则为 `O(V+E)` 建图结构 + 队列）
- 复杂度来源：Kahn 算法序列版；每个课程恰好追加一次，追加顺序即一个合法拓扑序。

## 用户代码注释版

> 只在点评文档中展示加注释版本；不把这些注释写回 `src/*.cpp` 的用户原代码。

```cpp
class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> graph(numCourses);
        vector<int> pre(numCourses, 0);
        vector<int> ans;                 // 出队顺序即拓扑序（入队时写入，顺序等价）
        for(auto prereq: prerequisites) {
            int u=prereq[0], v=prereq[1];
            graph[v].push_back(u);       // 完成 v 解锁 u
            pre[u]++;
        }
        queue<int> q;
        for(int i=0; i<numCourses; i++) {
            if(pre[i] == 0) {
                q.push(i);
                ans.push_back(i);        // 入队时即写入结果：入队顺序 = 输出顺序
            }
        }
        while(!q.empty()) {
            auto u=q.front(); q.pop();
            for(auto v: graph[u]) {
                pre[v]--;
                if(pre[v]==0) {
                    q.push(v);
                    ans.push_back(v);   // 后继清零：先修已全部排前
                }
            }
        }
        if(ans.size() == numCourses) {
            return ans;                  // 全部排完：合法拓扑序
        }
        return {};                      // 有环：环上课程未入列，数量不齐
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 结果写入时点 | 入队时追加而非出队时 | 正确——同一队列里入队顺序与出队顺序一致，两写法等价；"入队即写入"省一次队头查询 | 意识到这层等价是"知道自己在写什么"而非"碰巧能过"；出队写入版在 DFS 拓扑里会反转，两脉络要分开记 |
| 顺序合法性论证 | 隐式（靠 Kahn 结构保证） | 正确：v 追加进 ans 的前提是 pre[v] 清零 = 全部先修已在此前追加 | 复盘时把这句话完整说一遍——它是"输出确实是拓扑序"的证明 |
| 失败返回 | `{}` 空数组 | 与 207 的 `false` 对位；`return {}` 即 `vector<int>{}` | 已达标 |
| 唯一性理解 | 题目允许多解，返回任意一个 | 邻接表顺序决定同层内的次序，均合法 | 知道为何合法即可，不必追求特定顺序（除非有字典序要求） |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法（Kahn + 入队写入） | `O(V+E)` 最优；结果即出队顺序；与 207 零成本互通 | 无 | 输出拓扑序的标准解 |
| DFS 后序反转 | 同 `O(V+E)`；递归风味 | 结果要反转（后序逆序才是拓扑序）；递归深度风险 | Kahn 的等价替代 |
| 字典序最小拓扑序 | 若题面追加"最小字典序"则改用**最小堆替代队列** | 本题不要求，用了反而增加复杂度 | 明确要求时才上 |

## 最优解法

1. 207 的骨架 + 结果数组：入度 0 者入队并写入结果。
2. 出队遍历后继，入度清零者入队并写入。
3. 结果长度 == 节点数返回；否则返回空数组。
- 关键不变量：**写入结果的时刻恰好是其所有先修已在结果中的时刻**；因此结果数组天然满足拓扑序定义。
- 最优时间复杂度：`O(V + E)`
- 最优空间复杂度：`O(V + E)`

### 最优解代码

```cpp
class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> next(numCourses); // next[v]: 完成 v 后解锁的课
        vector<int> indeg(numCourses, 0);
        for (const auto& p : prerequisites) {
            next[p[1]].push_back(p[0]); // p[1] 是 p[0] 的先修
            indeg[p[0]]++;
        }
        vector<int> order;
        queue<int> q;
        for (int i = 0; i < numCourses; i++) {
            if (indeg[i] == 0) {
                q.push(i);
                order.push_back(i); // 入队即写入：入队顺序 = 拓扑序
            }
        }
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : next[u]) {
                if (--indeg[v] == 0) { // 先修全部就位
                    q.push(v);
                    order.push_back(v);
                }
            }
        }
        // 长度不齐 = 有环：环上课程永不入队
        return static_cast<int>(order.size()) == numCourses ? order : vector<int>{};
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 结果写入 | 入队时一次写入 | 相同 | 已配套 |
| 更新逻辑 | 入度清零并入队 | 相同 | 已达标 |
| 边界处理 | 空先修表输出 0..n-1、环返回 `{}`、n=1 均正确 | 相同 | 已达标 |
| 与 207 互通性 | 双题同构，只有"计数 vs 序列"之差 | 相同 | 已达标——把互通清单写进笔记 |

用户解法与推荐最优解逐行同构，本题完成质量高；两道课程表一次成型，迁移零损耗。

## 下一步建议

- 复盘任务：写出 207 → 210 的互改清单（`bool→vector<int>`、`ans++→ans.push_back`、返回值三处），确认"可行性问题"就是"顺序问题的投影"。
- 衔接任务：第 2 天 802（Eventual Safe States）考查"反图 + 出度清零"的镜像形态——今天练的是入度清零，明天对称练习出度清零，提前预告对称性。

## 后续练习

1. `802. Find Eventual Safe States` - 第 2 天题单，反向入度版拓扑，检验本题骨架的对称迁移。
2. `444. Sequence Reconstruction`（Plus）- 拓扑序"唯一性"判定变体，作为进阶可选。

## 代码同步

- 已将最优解作为新的解题函数写入：[src/210.course-schedule-ii.cpp](../src/210.course-schedule-ii.cpp)
- 新函数名：`findOrderOpt`，位于原 `class Solution` 中 `public:` 之前的私有区域
- 保留用户原实现：是
