# 题解点评 - 1091. Shortest Path in Binary Matrix（二进制矩阵中的最短路径）

## 基本信息

- 日期：2026-11-21
- 主题：第 11 周图论 BFS 与 DFS - 最短路径与状态扩展
- 难度：中等
- 本次结果：通过（用户确认已通过测试）
- 对应源码：[src/1091.shortest-path-in-binary-matrix.cpp](../src/1091.shortest-path-in-binary-matrix.cpp)
- 资料来源：[LeetCode 中国版官方题目页](https://leetcode.cn/problems/shortest-path-in-binary-matrix/)，2026-11-21 查询
- 约束要点：`1 <= n <= 100`；8 方向移动（含斜向）；路径长度按节点数计（起点计入，`[[0,1],[1,0]]` 答案为 2）；起点或终点为 1 返回 -1

## 用户思路概述

1. 起点为 1 直接返回 -1；`dist` 矩阵初始化 -1 兼作未访问标记。
2. 起点 `(0,0)` 入队，`dist[0][0] = 1`（按节点数计数，起点即 1）。
3. 8 方向 BFS：邻居为 0 且未访问时填 `dist[邻居] = dist[当前] + 1` 并入队——填值即标记，首达即最短。
4. 返回 `dist[n-1][n-1]`：恰为终点节点数，不可达时仍是初始 -1。

## 用户解法复杂度

- 时间复杂度：`O(n²)`（每格至多入队一次，8 方向常数扩展）
- 空间复杂度：`O(n²)`（dist 矩阵兼结果与标记）
- 复杂度来源：BFS 首达保证；dist 矩阵一物三用（距离 + 结果 + visited）。

## 用户代码注释版

> 只在点评文档中展示加注释版本；不把这些注释写回 `src/*.cpp` 的用户原代码。

```cpp
using pii=pair<int, int>;
const int DIRECT[][2] = {{1,0}, {-1,0}, {0,1}, {0,-1}, {1,1}, {1, -1}, {-1, -1}, {-1, 1}};  // 8 方向
class Solution {
public:
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        if(grid[0][0] != 0) return -1;    // 起点即墙：官方示例 3 的陷阱
        int n=grid.size();
        vector<vector<int>> dist(n, vector<int>(n, -1));  // -1 兼作未访问
        queue<pii> q;
        q.push({0, 0});
        dist[0][0]=1;                     // 按节点数计数：起点为 1
        while(!q.empty()) {
            auto [x, y]=q.front(); q.pop();
            for(int i=0; i<8; i++) {
                int nx=x+DIRECT[i][0], ny=y+DIRECT[i][1];
                if(nx>=0 && nx<n && ny>=0 && ny<n && grid[nx][ny]==0 && dist[nx][ny] ==-1) {
                    dist[nx][ny] = dist[x][y]+1;   // 填值即标记；首达即最短
                    q.push({nx, ny});
                }
            }
        }
        return dist[n-1][n-1];            // 不可达时保持 -1，天然作为返回值
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 计数口径 | `dist[0][0] = 1`，返回节点数 | 正确对齐题面"长度 = 途经单元格总数"的口径——比常见的边数口径多做了一步换算意识 | 复盘时说出"节点数 = 边数 + 1，所以起点从 1 起计"，避免下次凭惯性从 0 写起 |
| 8 方向扩展 | 方向数组直接列出全部 8 个偏移 | 正确；不要试图用两层循环生成 8 方向省 bytes，显式数组更可读 | 已达标 |
| -1 双关 | dist 初值 -1 既是"未访问"也是"不可达返回值" | 优雅：`grid[n-1][n-1] == 1`（终点是墙）与"扫不到"两种失败统一返回 -1 | 确认自己意识到这层双关，而非碰巧 |
| 起点检查 | `grid[0][0] != 0` 显式返回 -1 | 正确覆盖示例 3 陷阱 | 想清还需要单独检查终点吗——不需要，双关已覆盖 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法（BFS + dist 矩阵） | `O(n²)` 最优级；dist 一物三用 | 无实质缺点 | 无权最短路标准写法 |
| 层计数 BFS（sz 锁层） | 免 dist 矩阵，只 visited | 需要单独处理终点判定 | 等价写法 |
| A* | 同量级本题无收益 | 过度设计 | 加权或大规模时 |

## 最优解法

1. 起点为 1 返回 -1；dist 矩阵（-1 = 未访问），起点 dist = 1。
2. 8 方向 BFS：邻居为 0 且 dist == -1 时填 `dist[当前] + 1`，入队。
3. 返回 `dist[n-1][n-1]`。
- 关键不变量：BFS 层 `k` 上的格子其最短路径节点数为 `k`；首达即最短对 8 方向同样成立（各边权均等）。
- 最优时间复杂度：`O(n²)`
- 最优空间复杂度：`O(n²)`

### 最优解代码

```cpp
class Solution {
public:
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        int n = static_cast<int>(grid.size());
        if (grid[0][0] != 0) return -1; // 起点是墙
        vector<vector<int>> dist(n, vector<int>(n, -1)); // -1 = 未访问，也是失败返回值
        queue<pair<int, int>> q;
        // 8方向
        const int dx[] = {1, -1, 0, 0, 1, 1, -1, -1};
        const int dy[] = {0, 0, 1, -1, 1, -1, 1, -1};
        dist[0][0] = 1; // 节点数口径：起点即 1
        q.push({0, 0});
        while (!q.empty()) {
            auto [x, y] = q.front(); q.pop();
            for (int d = 0; d < 8; d++) {
                int nx = x + dx[d], ny = y + dy[d];
                if (nx >= 0 && nx < n && ny >= 0 && ny < n
                    && grid[nx][ny] == 0 && dist[nx][ny] == -1) {
                    dist[nx][ny] = dist[x][y] + 1; // 填值即标记
                    q.push({nx, ny});
                }
            }
        }
        return dist[n - 1][n - 1]; // 不可达时是 -1
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | dist 一物三用 | 相同 | 已配套 |
| 更新逻辑 | 8 方向 + 填值即标记 | 相同 | 已达标 |
| 边界处理 | 起点-1、-1 双关、n=1 均正确 | 相同 | 已达标 |
| 复杂度 | 时间 `O(n²)`、空间 `O(n²)` | 相同 | 已达最优 |

用户解法与推荐最优解逐行同构，本题完成质量高。

## 下一步建议

- 补一次提交确认：本题推演正确，建议在 LeetCode 提交确认状态。
- 复盘任务：说出节点数口径与边数口径的换算（差 1），并想清如果题目改成边数口径，自己的代码要改哪两处。

## 后续练习

1. `127. Word Ladder` - 同日题单，节点从格子变成单词，检验"图的节点不一定是坐标"的意识。
2. `1293. Shortest Path in a Grid with Obstacles Elimination` - 第 7 天困难题，本题加"资源维度"的扩展，直接衔接。

## 代码同步

- 已将最优解作为新的解题函数写入：[src/1091.shortest-path-in-binary-matrix.cpp](../src/1091.shortest-path-in-binary-matrix.cpp)
- 新函数名：`shortestPathBinaryMatrixOpt`，位于原 `class Solution` 中 `public:` 之前的私有区域
- 保留用户原实现：是
