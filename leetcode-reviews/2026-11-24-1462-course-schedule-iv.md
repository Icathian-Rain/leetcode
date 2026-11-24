# 题解点评 - 1462. Course Schedule IV（课程表 IV）

## 基本信息

- 日期：2026-11-24
- 主题：第 12 周拓扑排序与并查集 - 拓扑顺序变体（第 2 天）
- 难度：中等
- 本次结果：通过（用户确认已通过测试）
- 对应源码：[src/1462.course-schedule-iv.cpp](../src/1462.course-schedule-iv.cpp)
- 资料来源：[LeetCode 中国版官方题目页](https://leetcode.cn/problems/course-schedule-iv/)，2026-11-24 查询
- 约束要点：`2 <= numCourses <= 100`；`0 <= prerequisites.length <= n(n-1)/2`；`1 <= queries.length <= 10^4`；题目保证先修关系无环

## 用户思路概述

1. Kahn 拓扑（与 210 同构的正图、入度清零）+ 一个 `isPre[i][j]` 布尔矩阵：i 是否（直接或间接）先修 j。
2. 处理边 `(u, v)` 时：`isPre[u][v] = true`（直达），然后对每个 i 把 `isPre[i][u]` 整列"或"给 `isPre[i][v]`——u 的全部先修按传递性归入 v。
3. u 被出队处理时其先修集合已最终确定（入度清零才出队），所以此时向 v 的合并是完备的——这是该转移在拓扑序下正确的关键。
4. 查询 O(1) 读矩阵。

## 用户解法复杂度

- 时间复杂度：`O(V·E / ... )` 细算：每条边处理时做一次 O(V) 的列合并，总计 `O(E·V)` ≈ 100×4950 上界约 5×10⁵；加建图与查询 `O(Q)`
- 空间复杂度：`O(V²)`（isPre 矩阵）
- 复杂度来源：传递闭包沿拓扑序合并，`V=100` 时闭包 10⁴ 单元格，每单元写入摊还次数有限——本题规模下非常宽裕。

## 用户代码注释版

> 只在点评文档中展示加注释版本；不把这些注释写回 `src/*.cpp` 的用户原代码。

```cpp
class Solution {
public:
    vector<bool> checkIfPrerequisite(int numCourses, vector<vector<int>>& prerequisites, vector<vector<int>>& queries) {
        vector<vector<int>> graph(numCourses);
        vector<int> pre(numCourses, 0);
        vector<vector<bool>> isPre(numCourses, vector<bool>(numCourses, false));
        for(auto prereq: prerequisites) {
            int u=prereq[0], v=prereq[1];
            graph[u].push_back(v);    // 正图：u 解锁 v（与 210 同构）
            pre[v]++;                 // v 的入度 = 未满足先修数
        }
        queue<int> q;
        for(int i=0; i<numCourses; i++) {
            if(pre[i] == 0) {
                q.push(i);
            }
        }
        while(!q.empty()) {
            auto u=q.front(); q.pop();
            for(auto v: graph[u]) {
                isPre[u][v] = true;              // 直达边：u 是 v 的先修
                for(int i=0; i<numCourses; i++) {
                    isPre[i][v] = isPre[i][v] | isPre[i][u];  // 传递合并：u 的先修全是 v 的先修
                }
                pre[v]--;                        // 注：此处在 u 出队时触发，与入度清零次序无关，安全
                if(pre[v]==0) {
                    q.push(v);                   // v 的先修集合已完整，轮到 v 扩散
                }
            }
        }
        vector<bool> ans;
        for(auto q: queries) {                   // 每查询 O(1) 读闭包
            ans.push_back(isPre[q[0]][q[1]]);
        }
        return ans;
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 闭包沿拓扑序构建 | 转移放在 Kahn 出队伸展处 | 正确的时序安排：u 出队 ⟹ `isPre[·][u]` 已完整 ⟹ 向 v 合并不遗漏 u 的间接先修 | 复述这句"为什么此刻合并是完备的"——本题最核心的论证 |
| 转移方向 | 列合并 `isPre[i][v] |= isPre[i][u]` | 方向干净：v 的先修集合吸收 u 的先修集合（外加直达行） | 想清行列两个方向为什么等价（转置对称），选一种肌肉记忆即可 |
| 查询 O(1) | 矩阵即答案 | 正确：本题查询量 10⁴ 可以离线先算闭包 | 判断题核心：**查询量大且结构不变 ⟹ 预处理闭包；查询量小或图动态变 ⟹ 每查 BFS** |
| 入队保证 | v 入队要求全部先修出队 | 这保证处理边 (u,v) 后 v 的 dep 行再无后续增量——不依赖该点也已正确，但依赖它是最强的清晰论证 | 已达标 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法（拓扑 + 传递闭包） | 查询 O(1)；`V=100` 下 `O(EV)` 毫秒级 | 空间 `O(V²)`；V 大时不可行 | 本题规模的标准解 |
| 每查询 BFS/DFS | 免闭包空间；`O(Q·(V+E))` ≈ 10⁴×5×10³ = 5×10⁷ 偏紧张 | 每查询重复劳动 | 查询少、图大、或图动态变化 |
| Floyd 传递闭包 | 代码最短 `O(V³)` = 10⁶ | 与拓扑无关，V 大时不适用 | V 极小时的最简写法 |
| bitset 闭包 | `O(EV/w)`，列合并 64 倍加速 | 实现细节多 | V 上千时的保留路径 |

## 最优解法

1. Kahn 拓扑 + `reach[i][j]` 布尔矩阵（或 `bitset<100>` 行向量）。
2. 出队 u 伸展边 (u,v)：`reach[u][v]=true`，且 `reach[·][v] |= reach[·][u]`（bitset 版为 `col[v] |= col[u]`）。
3. 查询读矩阵。
- 关键不变量：**u 出队时其先修集合（闭包列）已最终化**；此后对每个 v 的列合并恰一次完整传播。
- 最优时间复杂度：`O(E·V)`（bitset 后 `O(EV/w)`）
- 最优空间复杂度：`O(V²)`

### 最优解代码

```cpp
class Solution {
public:
    vector<bool> checkIfPrerequisite(int numCourses, vector<vector<int>>& prerequisites, vector<vector<int>>& queries) {
        vector<vector<int>> graph(numCourses);
        vector<int> indeg(numCourses, 0);
        vector<vector<bool>> reach(numCourses, vector<bool>(numCourses, false));
        for (const auto& p : prerequisites) {
            graph[p[0]].push_back(p[1]);
            indeg[p[1]]++;
        }
        queue<int> q;
        for (int i = 0; i < numCourses; i++) {
            if (indeg[i] == 0) q.push(i); // 无先修：先出队，其闭包列已完整（空）
        }
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : graph[u]) {
                reach[u][v] = true;        // 直达
                for (int i = 0; i < numCourses; i++) {
                    reach[i][v] = reach[i][v] || reach[i][u]; // 传递：u 的先修全是 v 的先修
                }
                if (--indeg[v] == 0) q.push(v);
            }
        }
        vector<bool> ans;
        ans.reserve(queries.size());
        for (const auto& qr : queries) ans.push_back(reach[qr[0]][qr[1]]);
        return ans;
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 图结构 | 正图 Kahn | 相同 | 已配套 |
| 闭包转移 | 列合并 + 出队时序 | 相同 | 已达标（核心论证要能独立复述） |
| 查询 | O(1) 读矩阵 | 相同 | 已达标 |
| 边界处理 | 空先修表 + 查询反序对读 false，正确 | 相同 | 已达标 |
| 复杂度 | `O(EV)` / `O(V²)` | 相同 | 本题规模下达最优 |

用户解法与推荐最优解逐行同构；"出队时闭包列已完整"的时序利用是本题含金量最高的理解点，作者显然想清楚了这一点。

## 下一步建议

- 复盘任务：写出"预处理闭包 vs 每查询 BFS"的取舍判断式（查询数 × 单查成本 vs 拓扑闭包构建成本），以本题数字代入验证选择正确。
- 进阶小实验（可选）：把 `vector<vector<bool>>` 换成 `vector<bitset<100>>` 重写一遍，实测时间变化——这是把复杂度从 `EV` 降到 `EV/64` 的五分钟实验。

## 后续练习

1. `269. Alien Dictionary` - 同日题单的困难题，把拓扑排序用到字符级建模上。
2. `817` 类链表题不相关；更贴切的是 `2115. Find All Possible Recipes from Given Supplies` - 拓扑可达性的另一道变体。

## 代码同步

- 已将最优解作为新的解题函数写入：[src/1462.course-schedule-iv.cpp](../src/1462.course-schedule-iv.cpp)
- 新函数名：`checkIfPrerequisiteOpt`，位于原 `class Solution` 中 `public:` 之前的私有区域
- 保留用户原实现：是
