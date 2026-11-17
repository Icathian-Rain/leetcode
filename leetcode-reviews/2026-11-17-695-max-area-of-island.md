# 题解点评 - 695. Max Area of Island（岛屿的最大面积）

## 基本信息

- 日期：2026-11-17
- 主题：第 11 周图论 BFS 与 DFS - 网格连通块
- 难度：中等
- 本次结果：逻辑推演正确（用户未明确确认测试状态，暂记待验证）
- 对应源码：[src/695.max-area-of-island.cpp](../src/695.max-area-of-island.cpp)
- 资料来源：[LeetCode 中国版官方题目页](https://leetcode.cn/problems/max-area-of-island/)，2026-11-17 查询
- 约束要点：`1 <= m, n <= 50`，`grid[i][j]` 为 0 或 1；四方向连通；无岛屿返回 0

## 用户思路概述

1. 外层扫描网格，遇到 `1` 时启动一次 BFS。
2. BFS 内维护 `sum` 累积本岛面积：起点入队即改 0 并 `sum++`；邻居为 1 时入队即改 0 并 `sum++`。
3. 每次 BFS 结束用 `ans = max(ans, sum)` 更新全局最大面积。
4. 返回 `ans`。

## 用户解法复杂度

- 时间复杂度：`O(m × n)`（每格至多入队一次）
- 空间复杂度：`O(m × n)`（队列最坏，如全图陆地）
- 复杂度来源：入队即沉岛保证无重复；外层双重循环线性扫描。

## 用户代码注释版

> 只在点评文档中展示加注释版本；不把这些注释写回 `src/*.cpp` 的用户原代码。

```cpp
using pii=pair<int, int>;
const int DIRECT[][2] = {{1,0}, {-1,0}, {0, 1}, {0, -1}};
class Solution {
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int m=grid.size(), n=grid[0].size();
        int ans=0;
        for(int x=0; x<m; x++) {
            for(int y=0; y<n; y++) {
                if(grid[x][y] != 1) continue;
                int sum=0;              // 本岛面积
                queue<pii> q;
                grid[x][y] = 0;         // 入队即沉岛，改写即访问标记
                sum ++;
                q.push({x, y});
                while(!q.empty()) {
                    auto [cx, cy] = q.front(); q.pop();
                    for(int i=0; i<4; i++) {
                        int nx=cx+DIRECT[i][0], ny=cy+DIRECT[i][1];
                        if(nx>=0 && nx<m && ny>=0 && ny<n && grid[nx][ny]==1) {
                            grid[nx][ny] = 0;   // 入队同时沉岛，防止重复入队
                            sum++;
                            q.push({nx, ny});
                        }
                    }
                }
                ans=max(ans, sum);      // 每座岛结算一次最大值
            }
        }
        return ans;
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 与 200 的骨架迁移 | BFS 沉岛 + 外层扫连通块，与昨日 200 的 `Opt` 版几乎逐行同构 | 一天内完成"计数 → 累积"的迁移，说明第 1 天的网格 BFS 骨架已内化 | 复盘时指出与 200 的唯一差异：`ans++` 换成 `sum++` + `max` |
| 入队即计数 | 起点 `sum++` 与邻居 `sum++` 都在入队时完成 | 正确：计数与沉岛绑定，每格恰好计一次 | 已达标 |
| 全水网格 | 无 `1` 时 `ans` 保持 0 | 正确覆盖"无岛屿返回 0" | 已达标 |
| 单格岛 | 起点入队 `sum=1` 后无邻居，`max` 正确 | 正确 | 已达标 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法（BFS 沉岛 + 块内累积） | `O(mn)` 最优级；与 200 骨架统一，迁移成本最低 | 无实质缺点 | 连通块统计类问题 |
| 递归 DFS 返回面积 | 代码更短（DFS 返回子树大小累加） | `m,n<=50` 无风险；大规模有栈深问题 | 习惯递归时的等价选择 |

## 最优解法

1. 外层扫描遇 `1` 启动 BFS/DFS，把整岛沉没并累积面积。
2. 每岛面积与全局最大值比较；扫描结束返回。
- 关键不变量：入队（或进入递归）即沉岛并计数，每格恰好贡献一次面积。
- 最优时间复杂度：`O(m × n)`
- 最优空间复杂度：`O(m × n)`（队列/栈最坏）

### 最优解代码

```cpp
class Solution {
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int m = static_cast<int>(grid.size());
        int n = static_cast<int>(grid[0].size());
        int ans = 0;
        const int dx[] = {1, -1, 0, 0}, dy[] = {0, 0, 1, -1};
        for (int x = 0; x < m; x++) {
            for (int y = 0; y < n; y++) {
                if (grid[x][y] != 1) continue;
                int area = 0;
                queue<pair<int, int>> q;
                grid[x][y] = 0; // 入队即沉岛并计数，每格恰好计一次
                area++;
                q.push({x, y});
                while (!q.empty()) {
                    auto [cx, cy] = q.front(); q.pop();
                    for (int i = 0; i < 4; i++) {
                        int nx = cx + dx[i], ny = cy + dy[i];
                        if (nx >= 0 && nx < m && ny >= 0 && ny < n && grid[nx][ny] == 1) {
                            grid[nx][ny] = 0;
                            area++;
                            q.push({nx, ny});
                        }
                    }
                }
                ans = max(ans, area);
            }
        }
        return ans;
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | `sum` + `ans` | `area` + `ans` | 仅命名差异 |
| 更新逻辑 | 入队即沉岛即计数 | 相同 | 已达标 |
| 边界处理 | 全水、单格岛均正确 | 相同 | 已达标 |
| 复杂度 | 时间 `O(mn)`、空间 `O(mn)` | 相同 | 已达最优 |

用户解法与推荐最优解逐行同构，本题完成质量高。

## 下一步建议

- 补一次提交确认：本地推演正确，建议在 LeetCode 提交一次以确认记录状态。
- 复盘任务：说出本题与 200 的"唯一一行差异"——确认是模式迁移而非重新发明。

## 后续练习

1. `463. Island Perimeter` - 同日题单，连通块不扩张、只看邻居关系，是"何时不需要搜索"的对照案例。
2. `827. Making A Large Island` - 面积统计 + 块编号的进阶变体，作为周末拔高可选。

## 代码同步

- 已将最优解作为新的解题函数写入：[src/695.max-area-of-island.cpp](../src/695.max-area-of-island.cpp)
- 新函数名：`maxAreaOfIslandOpt`，位于原 `class Solution` 中 `public:` 之前的私有区域
- 保留用户原实现：是
