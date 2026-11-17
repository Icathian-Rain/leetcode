# 题解点评 - 1971. Find if Path Exists in Graph（寻找图中是否存在路径）

## 基本信息

- 日期：2026-11-16
- 主题：第 11 周图论 BFS 与 DFS - 图遍历入口
- 难度：简单
- 本次结果：通过（用户确认已测试通过）
- 对应源码：[src/1971.find-if-path-exists-in-graph.cpp](../src/1971.find-if-path-exists-in-graph.cpp)
- 资料来源：[LeetCode 中国版官方题目页](https://leetcode.cn/problems/find-if-path-exists-in-graph/)，2026-11-16 查询
- 约束要点：`1 <= n <= 2*10^5`，`0 <= edges.length <= 2*10^5`；无重边、无自环；双向边

## 用户思路概述

1. 从边列表建邻接表：无向图每条边 `u-v` 在 `adj[u]` 和 `adj[v]` 各存一份。
2. 从 `source` 出发 DFS：当前节点等于 `destination` 直接返回 `true`；否则标记 `vis[x] = true`，依次尝试所有未访问邻居，任一分支可达即返回 `true`。
3. 所有分支都走不通返回 `false`。

## 用户解法复杂度

- 时间复杂度：`O(n + m)`（建表 + 遍历，每个节点和每条边最多访问一次）
- 空间复杂度：`O(n + m)`（邻接表 + visited 数组）
- 复杂度来源：邻接表存储双向边；DFS 遍历每条边至多两次（每端一次）。

## 用户代码注释版

> 只在点评文档中展示加注释版本；不把这些注释写回 `src/*.cpp` 的用户原代码。

```cpp
class Solution {
    bool dfs(int x, int destination, vector<vector<int>>& adj, vector<bool>& vis) {
        if(x == destination) {
            return true;          // 到达终点，整条调用链短路返回
        }
        vis[x] = true;            // 进入即标记，防止环导致无限递归
        for(auto next: adj[x]) {
            // 未访问的邻居才继续；任一分支可达即向上返回 true
            if(!vis[next] && dfs(next, destination, adj, vis)) {
                return true;
            }
        }
        return false;             // 所有邻居都不可达
    }
public:
    bool validPath(int n, vector<vector<int>>& edges, int source, int destination) {
        vector<vector<int>> adj(n);
        for(auto e: edges) {
            int u=e[0], v=e[1];
            adj[u].push_back(v);
            adj[v].push_back(u);  // 无向图：两个方向都要存
        }
        vector<bool> vis(n, false);
        return dfs(source, destination, adj, vis);
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 访问标记时机 | 进入节点即标记，回溯时不撤销 | 正确：本题求"是否可达"而非"找所有路径"，标记永久有效；若撤销标记会指数爆炸 | 想清"什么时候标记要撤销（回溯周）、什么时候不撤销（连通性）"——这是本周最核心的状态意识 |
| 提前返回 | 到达终点即整链短路 | 正确且高效，避免搜完全图 | 已达标 |
| 递归深度风险 | 递归 DFS 在链状图上深度达 `2*10^5` | 潜在风险：本题 `n` 上限 2*10^5，链形图可能触发栈溢出；实际通过说明测试数据未构造极端链 | 意识到大规模图上迭代 DFS/BFS 或并查集更稳；这是本题最重要的风险点 |
| source == destination | 首次调用即返回 `true` | 正确 | 已达标 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法（递归 DFS） | 结构清晰；提前返回高效 | 大规模链状图递归深度可达 `2*10^5`，有栈溢出风险 | 小规模图或递归深度可控时 |
| 迭代 DFS / BFS | 同为 `O(n+m)`，无栈溢出风险 | 代码略长 | 本题规模下的稳妥选择 |
| 并查集 | 只判连通性时不需要遍历结构；`O(n α(m))` 近线性 | 需要掌握并查集实现；不能回答路径本身 | 只需"是否连通"的批量查询场景，第 12 周主题的前奏 |

## 最优解法

1. 建邻接表后从 `source` 出发 BFS（或迭代 DFS）：出队节点等于 `destination` 即返回 `true`。
2. 每个节点至多入队一次（入队即标记），队列空仍未到达返回 `false`。
- 关键不变量：队列中是"已发现但未扩展"的节点集合；入队即标记保证无重复、无环。
- 最优时间复杂度：`O(n + m)`
- 最优空间复杂度：`O(n + m)`

### 最优解代码

```cpp
class Solution {
public:
    bool validPath(int n, vector<vector<int>>& edges, int source, int destination) {
        vector<vector<int>> adj(n);
        for (const auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]); // 无向图双向存边
        }
        vector<bool> vis(n, false);
        queue<int> q;
        q.push(source);
        vis[source] = true; // 入队即标记，防止重复入队
        while (!q.empty()) {
            int x = q.front(); q.pop();
            if (x == destination) return true; // 扩展前先判终点
            for (int next : adj[x]) {
                if (!vis[next]) {
                    vis[next] = true;
                    q.push(next);
                }
            }
        }
        return false;
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | `vis` + 递归栈 | `vis` + 显式队列 | 大规模图优先显式栈/队列 |
| 更新逻辑 | 进入即标记 + 短路返回 | 入队即标记 + 出队判终点 | 两者等价；BFS 无栈深风险 |
| 边界处理 | `source == destination` 正确 | 相同（首节点入队即判） | 已达标 |
| 复杂度 | 时间 `O(n+m)`、空间 `O(n+m)` | 相同 | 已达最优 |

用户解法正确且达最优复杂度，风险只在递归深度；同步的 `Opt` 函数展示 BFS 版本作为大规模图上的稳妥形态。

## 下一步建议

- 进入下一题：本题作为图遍历入口已达标，直接推进。
- 复盘任务：想清"连通性判定中 visited 为什么不撤销"，与第 7 周回溯的"撤销选择"对照一次。

## 后续练习

1. `733. Flood Fill` - 同日题单，把图遍历搬到网格上，节点从编号变成坐标。
2. `547. Number of Provinces` - 第 7 天题单，连通块统计 + 邻接矩阵输入，检验建图方式的变化。

## 代码同步

- 已将最优解作为新的解题函数写入：[src/1971.find-if-path-exists-in-graph.cpp](../src/1971.find-if-path-exists-in-graph.cpp)
- 新函数名：`validPathOpt`，位于原 `class Solution` 中 `public:` 之前的私有区域
- 保留用户原实现：是
