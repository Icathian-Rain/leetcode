# 题解点评 - 1293. Shortest Path in a Grid with Obstacles Elimination（网格中的最短路径）

## 基本信息

- 日期：2026-11-22
- 主题：第 11 周图论 BFS 与 DFS - 综合复盘与图建模（第 7 天）
- 难度：困难
- 本次结果：通过（用户确认已通过测试）
- 对应源码：[src/1293.shortest-path-in-a-grid-with-obstacles-elimination.cpp](../src/1293.shortest-path-in-a-grid-with-obstacles-elimination.cpp)
- 资料来源：[LeetCode 中国版官方题目页](https://leetcode.cn/problems/shortest-path-in-a-grid-with-obstacles-elimination/)，2026-11-22 查询
- 约束要点：`1 <= m, n <= 40`；`1 <= k <= m*n`；起终点必为 0；四方向移动；步数口径为**移动步数**（路径长度 = 边数），比 1091 的节点数口径少 1

## 题意与本日定位

- 从 `(0,0)` 走到 `(m-1,n-1)`，途中至多消除 `k` 个障碍（每次消除消耗一次额度），求最少步数。
- 本日定位：**状态扩展**——1091/127/752 的"节点 = 位置或状态"，本题节点 = `(x, y, 剩余额度)`，三维状态是全周隐式图建模的收官检验。

## 用户思路概述

1. 状态 `(x, y, re)`：坐标 + 剩余可消除额度；`re = 当前 k - 已消除数`。
2. 不用三维 visited，改用 `best[x][y]`（二维）：记录该格子见过的**最大剩余额度**。扩展时 `next = re - grid[nx][ny]`，仅当 `next > best[nx][ny]` 才入队——即支配剪枝：新状态只有在"剩余额度严格更充裕"时才值得再搜。
3. **层计数 BFS**：`for(int steps=0; !q.empty(); steps++)` + 内层 `count=q.size()` 锁住当前层，步数不用存进状态。
4. 出队时判定终点，返回 `steps`。

## 用户解法复杂度

- 时间复杂度：`O(m·n·k)`（每格至多 k 个不同剩余额度级别，极端 k=m·n 时 O(m²n²) ≈ 40⁴ = 2.56×10⁶）
- 空间复杂度：`O(m·n)`（best 二维数组 + 队列）
- 复杂度来源：支配剪枝后每格只保留"剩余额度递增序列"的状态串，队列里同格状态严格递减于历史，总量 `O(m·n·k)` 不变，但二维 best 比三维 `vis[x][y][re]` 省 k 倍内存。

## 支配剪枝正确性论证（本日核心复盘点）

- 新状态 `(x, y, re')` 想入队，要求 `re' > best[x][y]`。设此前已有一个更早层的状态 `(x, y, r)`，`r >= re'`。层计数 BFS 保证后来者步数 ≥ 先来者（边权均等）。则该后继状态的任何后续路径：先来者以**不多步数 + 不小于额度**同样可走（后续路径的障碍消耗只依赖路径形状，与怎么到达无关）。故新状态被支配，剪去不失最优。
- 对比朴素三维版：`vis[x][y][re]` 只判"该三元组没来过"，同格不同额度都要存；支配剪枝进一步压掉"额度更小"的重复，是更强的不变式。

## 用户代码注释版

> 只在点评文档中展示加注释版本；不把这些注释写回 `src/*.cpp` 的用户原代码。

```cpp
const int DIRECT[][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
using ti = tuple<int, int, int>;
class Solution {
public:
    int shortestPath(vector<vector<int>>& grid, int k) {
        int m=grid.size(), n=grid[0].size();
        vector<vector<int>> best(m, vector<int>(n, -1));  // 该格见过的最大剩余额度；-1 兼未到访
        queue<ti> q;
        best[0][0] = k;
        q.push({0, 0, k});
        for(int steps=0; !q.empty(); steps++) {   // 层计数：steps 隐式递增
            for(int count=q.size(); count>0; count--) {   // 锁住当前层
                auto [x, y, re] = q.front(); q.pop();
                if(x == m-1 && y == n-1) return steps;      // 出队判终点：层号即步数
                for(int i=0; i<4; i++) {
                    int nx=x+DIRECT[i][0], ny=y+DIRECT[i][1];
                    if(nx<0 || nx>=m || ny<0 || ny >=n) continue;
                    int next=re-grid[nx][ny];              // 走入障碍扣 1 额度，空白不扣
                    if(next <= best[nx][ny]) continue;      // 支配剪枝：额度不更充裕则弃
                    best[nx][ny] = next;
                    q.push({nx, ny, next});
                }
            }
        }
        return -1;
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 状态加资源维度 | 节点 = `(x, y, 剩余额度)` | 直接命中本题的考察核心——1091 的节点是格子，本题节点是"格子 × 剩余资源"，这是状态扩展的收官形态 | 归纳一句：**当"到达过的格子"不足以区分路径好坏时，就把路径差异（资源消耗）并入节点定义** |
| 支配剪枝 | `next <= best[nx][ny]` 弃 | 比朴素三维 visited 更强的剪枝：后到且额度更小的状态必然次优 | 保证自己读懂了正确性论证——“先前状态既有步数优势又有额度优势”缺一不可（只有步数优势无额度优势时不成立！例如平移绕后带额度过来） |
| 层计数 BFS | `steps` 外层递增 + `count` 锁层 | 免把步数塞进 tuple；层保证收齐 | 与 1091/994 同一骨架三用；两种步数载体都应熟练 |
| 出队判终点 | `(0,0)` 即终点时返回 0 正确（1×1 网格） | 起点即终点由层 0 出队覆盖 | 已达标 |
| 步数口径 | 返回 `steps` = 边数 | 正确对齐题面"步数"口径（1091 是节点数，差 1） | 两题口径并排记忆："数格子" or "数移动" |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法（层计数 BFS + 支配剪枝） | 量级最优；二维 best 省内存；剪枝强于三维版 | 支配正确性论证需要一层理解门槛 | 本题标准最优写法之一 |
| 三维 visited BFS | 防重逻辑最直白 | 空间 O(m·n·k)；状态重复率高 | 状态维度不多时的朴素底版 |
| A*（曼哈顿启发） | 实践中扩展节点更少 | 需要启发可采纳的证明；本题规模不必要 | 网格更大、k 更大时 |
| 数学校验捷径 | `k >= m+n-2` 时答案恒为 `m+n-2`（额度够直接平推）O(1) 短路 | 只省一个大 k 常数场景 | 大 k 输入的常数优化 |

## 最优解法

1. 短路判定：`k >= m+n-2` 直接返回 `m+n-2`——额度至少够消除一条平推直线路径上的全部障碍（一路恰有至多 `m+n-2` 个格子会途经）。
2. 层计数 BFS，状态 `(x, y, re)`，`best[x][y]` 记录最大剩余额度并做支配剪枝。
- 关键不变量：队列中任何时刻同格状态按入队顺序剩余额度严格递增；任一保留状态都不被既有状态支配。
- 最优时间复杂度：`O(m·n·k)`（短路后 O(1)）
- 最优空间复杂度：`O(m·n)`

### 最优解代码

```cpp
class Solution {
public:
    int shortestPath(vector<vector<int>>& grid, int k) {
        int m = static_cast<int>(grid.size());
        int n = static_cast<int>(grid[0].size());
        // 额度至少够平推一路：曼哈顿路径不绕行，答案封顶 m+n-2
        if (k >= m + n - 2) return m + n - 2;
        const int dx[] = {1, 0, -1, 0};
        const int dy[] = {0, 1, 0, -1};
        vector<vector<int>> best(m, vector<int>(n, -1)); // 该格最大剩余额度
        queue<tuple<int, int, int>> q;
        best[0][0] = k;
        q.emplace(0, 0, k);
        for (int steps = 0; !q.empty(); steps++) {   // 层计数：层号即步数
            for (int cnt = static_cast<int>(q.size()); cnt > 0; cnt--) {
                auto [x, y, re] = q.front(); q.pop();
                if (x == m - 1 && y == n - 1) return steps;
                for (int d = 0; d < 4; d++) {
                    int nx = x + dx[d], ny = y + dy[d];
                    if (nx < 0 || nx >= m || ny < 0 || ny >= n) continue;
                    int nxt = re - grid[nx][ny];   // 障碍扣额度
                    if (nxt <= best[nx][ny]) continue; // 支配剪枝：不更充裕则弃
                    best[nx][ny] = nxt;
                    q.emplace(nx, ny, nxt);
                }
            }
        }
        return -1;
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | `(x,y,re)` + 二维 best | 相同 | 已配套 |
| 剪枝强度 | 支配剪枝（强于三维 visited） | 相同 | 已达高级形态 |
| 层计数 / 短路 | 层计数有 | 层计数 + `k >= m+n-2` O(1) 短路 | 大 k 场景常数捷径值得形成条件反射 |
| 边界处理 | 1×1 网格、全障碍不可达均正确 | 相同（短路不影响正确性） | 已达标 |
| 复杂度 | 时间 `O(m·n·k)`、空间 `O(m·n)` | 相同 | 已达最优 |

用户解法与推荐最优解同构（后者仅多 O(1) 短路），本题作为第 7 天困难题完成质量高，支配剪枝是全周最有含金量的一个自选实现。

## 下一步建议

- 复盘任务：向自己复述支配剪枝正确性论证的"缺一不可"——步数优势与额度优势必须同时持有，只占步数优势不能剪（绕路攒额度是本题唯一会骗过弱剪枝的打法）。
- 口径练习：1091（节点数）与 1293（边数）并排，写出两题返回表达式各自的 +1/-1 位置。

## 后续练习

1. `LCP 64` 或 `2290. Minimum Obstacle Removal to Reach Corner`（双向权重 0-1 / 最短路替代视角）——把"消除额度"翻转为"求最少消除数"，体会资源维度当目标 vs 当约束的两个方向。
2. `864. Shortest Path to Get All Keys` - 状态里带"钥匙集合"位掩码，是本题资源维度思路在更复杂资源上的延伸。

## 代码同步

- 已将最优解作为新的解题函数写入：[src/1293.shortest-path-in-a-grid-with-obstacles-elimination.cpp](../src/1293.shortest-path-in-a-grid-with-obstacles-elimination.cpp)
- 新函数名：`shortestPathOpt`，位于原 `class Solution` 中 `public:` 之前的私有区域
- 保留用户原实现：是
