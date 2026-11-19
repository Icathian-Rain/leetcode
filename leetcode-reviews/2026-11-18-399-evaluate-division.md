# 题解点评 - 399. Evaluate Division（除法求值）

## 基本信息

- 日期：2026-11-18
- 主题：第 11 周图论 BFS 与 DFS - 图复制与状态映射
- 难度：中等
- 本次结果：通过（用户确认已通过测试）
- 对应源码：[src/399.evaluate-division.cpp](../src/399.evaluate-division.cpp)
- 资料来源：本地参考，**未联网校准**（官方页校准未完成）；难度与约束按通行信息整理，待办题目信息可在下次联网时复核
- 约束要点：方程数量与查询数量均不超过 20 个量级；`values[i] > 0`；变量为小写字母串；查询中出现未知变量返回 `-1.0`；不可达返回 `-1.0`

## 用户思路概述

1. 建带权无向图：每条方程 `a / b = w` 存两条边——`a→b` 权 `w`，`b→a` 权 `1/w`（反向边取倒数）。
2. 每个查询 `(u, v)`：任一变量没在图中出现，直接 `-1.0`；否则清空访问集，DFS 从 `u` 走到 `v`，沿途把边权连乘。
3. DFS 到达 `target` 返回 `1.0`（乘法单位元），上层逐层乘回来；某分支失败返回 `-1.0` 由上层继续尝试其他邻居。
4. 全部失败返回 `-1.0`。

## 用户解法复杂度

- 时间复杂度：建图 `O(E)`；每个查询一次完整搜索 `O(V + E)`，总计 `O(E + Q(V + E))`；本题规模（E、Q ≤ 20 量级）下完全无压力
- 空间复杂度：`O(V + E)`（邻接表 + 访问集）
- 复杂度来源：图与查询规模都极小，DFS 逐查询搜索是标准做法；数据加大时应换带权并查集。

## 用户代码注释版

> 只在点评文档中展示加注释版本；不把这些注释写回 `src/*.cpp` 的用户原代码。

```cpp
class Solution {
    unordered_map<string, vector<pair<string, double>>> g;  // 变量 -> (邻居, 边权)
    unordered_set<string> vis;

    double dfs(string u, string target) {
        if(u == target) return 1.0;    // 到达：返回乘法单位元，沿途权值连乘即答案
        vis.insert(u);                 // 进入即标记，防环
        for(auto [v, w]: g[u]) {
            if(vis.count(v)) continue;
            double res = dfs(v, target);
            if(res != -1.0) return w*res;  // 子分支可达：乘上本边权向上返回
        }
        return -1.0;                   // 所有分支不可达
    }
public:
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        int n=equations.size();
        for(int i=0; i<n; i++) {
            vector<string> eq = equations[i];
            double w = values[i];
            string u=eq[0], v=eq[1];
            g[u].push_back({v, w});       // 正向边：u/v = w
            g[v].push_back({u, 1.0/w});   // 反向边：v/u = 1/w（values > 0 保证安全）
        }
        vector<double> ans;
        for(auto q: queries) {
            string u=q[0], v=q[1];
            if(g.count(u) == 0 || g.count(v) == 0) {
                ans.push_back(-1.0);      // 未知变量：不必搜索
                continue;
            }
            vis.clear();                  // 查询间重置访问标记
            ans.push_back(dfs(u, v));     // 含 u == v 的情形：直接返回 1.0
        }
        return ans;
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 建模转换 | 商关系 → 带权无向边，反向取倒数 | 这是本题最难的一步，转换正确说明"图建模"正在内化；路径连乘 = 商的传递 | 口头说出"为什么 a/b * b/c = a/c 恰好对应路径乘积" |
| 单位元返回值 | `u == target` 返回 `1.0` | 正确且优雅：同时覆盖"查询同名变量"（如 `["a","a"]`）的官方陷阱样例——只要 `a` 存在，答案必为 1.0 | 想清官方样例 `[["a","a"]]` 与未知变量 `["x","x"]` 的区别（前者存在图中返回 1.0，后者走未知分支返回 -1.0） |
| 成员状态与清理 | `g`/`vis` 是类成员，查询间 `vis.clear()` | 正确但成员化让函数依赖隐式状态；`vis` 若漏 clear 会把上个查询的标记带到下个查询 | 迁移时注意：状态入参（局部 map）更显式，成员状态易在复用时踩坑 |
| 提前剪枝 | 任一变量未出现直接 `-1.0` | 正确：避免在空邻接表上做无意义搜索 | 已达标 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法（带权图 + 逐查询 DFS） | 建模直观；`O(E + Q(V+E))` 足够；边权连乘语义清晰 | 大数据量下逐查询搜索不够好 | 本题规模的标准写法 |
| 带权并查集 | 每次查询近 `O(1)`（带路径压缩），整体 `O((E+Q) α)` | 实现更绕：find 时要同步维护节点到根的权积 | 数据量大或查询多的版本；第 12 周并查集主题的预告 |

## 最优解法

1. 建带权无向图（正向 `w`、反向 `1/w`）。
2. BFS 版逐查询搜索：队列携带"当前变量 × 累计积"，起点积为 1.0；首次到达目标返回累计积。
- 关键不变量：队列里的每个元素代表"从 u 到该变量的一条路径及其权积"；同一变量可能有多条路径，首次达到目标的路径乘积即答案（等价类内任意路径乘积相同）。
- 最优时间复杂度：`O(E + Q(V + E))`（本题规模）；带权并查集可达 `O((E+Q) α)`
- 最优空间复杂度：`O(V + E)`

### 最优解代码

```cpp
class Solution {
public:
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        // 带权无向图：a/v = w 正反向各存一条
        unordered_map<string, vector<pair<string, double>>> g;
        for (int i = 0; i < static_cast<int>(equations.size()); i++) {
            const string& u = equations[i][0];
            const string& v = equations[i][1];
            double w = values[i];
            g[u].push_back({v, w});      // 正向
            g[v].push_back({u, 1.0 / w}); // 反向取倒数（values > 0）
        }
        vector<double> ans;
        for (const auto& q : queries) {
            const string& u = q[0];
            const string& v = q[1];
            // 未知变量：不搜索直接 -1
            if (!g.count(u) || !g.count(v)) {
                ans.push_back(-1.0);
                continue;
            }
            // BFS 携带路径累计积；u == v 时起点即为答案 1.0
            unordered_set<string> vis{u};
            queue<pair<string, double>> bfs;
            bfs.push({u, 1.0});
            double result = -1.0;
            while (!bfs.empty() && result < 0) {
                auto [cur, prod] = bfs.front(); bfs.pop();
                if (cur == v) { result = prod; break; }
                for (auto [nb, w] : g[cur]) {
                    if (vis.insert(nb).second) { // insert 返回 false 说明已访问
                        bfs.push({nb, prod * w});
                    }
                }
            }
            ans.push_back(result);
        }
        return ans;
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | 类成员 `g`/`vis` + 递归栈 | 局部状态 + BFS 队列携带权积 | 成员状态 vs 局部状态的取舍，迁移时留意隐式耦合 |
| 更新逻辑 | 递归返回连乘 | 队列携带累计积 | 语义等价 |
| 边界处理 | 未知变量、同名查询、查询间 clear 均正确 | 相同（访问集每查询新建） | 已达标 |
| 复杂度 | `O(E + Q(V+E))` | 相同 | 已达本题规模最优 |

## 下一步建议

- 进入下一题单：第 3 天题单处理完毕（138 为第 4 周已完成题，按历史记录计），明天进入第 4 天多源按层扩散。
- 复盘任务：写出"商的传递 = 路径乘积"一句论证，并给 `["x","x"]` 和 `["a","a"]` 各标一个正确返回值——确认样例陷阱都想过一遍。

## 后续练习

1. `2309. Greatest English Letter in Upper and Lower Case` 无关；更贴切的是 `2421. Number of Good Paths` - 带权并查集的进阶形态，作为第 12 周前的预习可选。
2. `127. Word Ladder` - 第 6 天题单的隐式图搜索，与本题的"边权传递"互补（那题按层计数）。

## 代码同步

- 已将最优解作为新的解题函数写入：[src/399.evaluate-division.cpp](../src/399.evaluate-division.cpp)
- 新函数名：`calcEquationOpt`，位于原 `class Solution` 中 `public:` 之前的私有区域
- 保留用户原实现：是（含类成员 `g`/`vis` 的隐式状态，未替用户重构）
