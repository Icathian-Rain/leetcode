# 题解点评 - 994. Rotting Oranges（腐烂的橘子）

## 基本信息

- 日期：2026-11-19
- 主题：第 11 周图论 BFS 与 DFS - 多源按层扩散
- 难度：中等
- 本次结果：通过（用户确认已通过测试）
- 对应源码：[src/994.rotting-oranges.cpp](../src/994.rotting-oranges.cpp)
- 资料来源：[LeetCode 中国版官方题目页](https://leetcode.cn/problems/rotting-oranges/)，2026-11-19 查询
- 约束要点：`1 <= m, n <= 10`；`0` 空、`1` 新鲜、`2` 腐烂；返回全部腐烂的最小分钟数，无法全腐烂返回 `-1`，初始无新鲜橘子返回 `0`

## 用户思路概述

1. 初始扫描：所有腐烂橘子入队（多源起点），同时统计新鲜橘子数 `cnt`。
2. 按层 BFS：循环条件 `!q.empty() && cnt > 0`，每轮取出当前层全部 `sz` 个节点，向四方向传染——邻居为新鲜则 `cnt--`、改 2、入队。每完成一层，分钟数 `ans++`。
3. 结束后 `cnt == 0` 返回 `ans`，否则说明有橘子永远够不到，返回 `-1`。

## 用户解法复杂度

- 时间复杂度：`O(m × n)`（每格至多入队一次）
- 空间复杂度：`O(m × n)`（队列最坏）
- 复杂度来源：多源同层扩散，每格至多被传染改造一次；层计数靠"一次处理整层"。

## 用户代码注释版

> 只在点评文档中展示加注释版本；不把这些注释写回 `src/*.cpp` 的用户原代码。

```cpp
using pii=pair<int, int>;
const int DIRECT[][2]={{1,0}, {-1, 0}, {0, 1}, {0, -1}};
class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        int m=grid.size(), n=grid[0].size();
        queue<pii> q;
        int ans=0;
        int cnt=0;               // 新鲜橘子剩余数
        for(int i=0; i<m; i++) {
            for(int j=0; j<n; j++) {
                if(grid[i][j] == 2) {
                    q.push({i, j});   // 全部腐烂橘子同时入队：多源起点
                } else if(grid[i][j] == 1) {
                    cnt++;
                }
            }
        }

        while(!q.empty() && cnt>0) {    // 没有新鲜橘子时不再扩散，避免多算一轮
            int sz=q.size();            // 本层节点数，锁定后逐个处理
            for(int i=0; i<sz; i++) {
                auto [x, y]=q.front(); q.pop();
                for(int j=0; j<4; j++) {
                    int nx=x+DIRECT[j][0], ny=y+DIRECT[j][1];
                    if(nx>=0 && nx<m && ny>=0 && ny<n && grid[nx][ny]==1) {
                        cnt--;
                        grid[nx][ny]=2;   // 改值即标记，防重复入队
                        q.push({nx, ny});
                    }
                }
            }
            ans++;                       // 一层扩散 = 1 分钟
        }
        return cnt == 0 ? ans : -1;      // 有剩余新鲜橘子即不可达
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 多源同层入队 | 初始扫描把全部烂橘子一次入队 | 正确且是本题关键：所有源共用一个队列，天然公平地逐层向外，某橘子被最早到达的源传染即最短时间 | 口头对比"逐源 BFS"（每个源单独搜，`O(mn·源数)`）说明多源为何更优 |
| 层计数方式 | `sz=q.size()` 锁定本层后再扩散 | 正确的按层 BFS 标准写法；也可队列携带时间戳，两种等价 | 已达标 |
| 循环条件含 `cnt>0` | 新鲜橘子清零即停层计数 | 精确且是细节亮点：没有这一条，队列继续扩散会在末层多算 1 分钟（官方样例 3 `[[0,2]]` 返回 0 也被此覆盖） | 想清"如果只写 `!q.empty()` 会错在哪"——例 3 会把 ans 算成 1 |
| 改 2 即标记 | 传染时改格值 | 与本周标记体系统一 | 已达标 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法（多源按层 BFS） | `O(mn)` 最优级；时间即层数 | 无实质缺点 | 多源扩散计时类标准写法 |
| 时间戳携带 | 免去 sz 锁层 | 无实质差异 | 等价写法 |
| 逐源 BFS | 思路直白 | 时间乘上源数，非最优 | 反面教材，用于理解多源的必要性 |

## 最优解法

1. 全部烂橘子作为多源起点一次入队，统计新鲜数量。
2. 按层 BFS：每层处理完 `ans++`；新鲜橘子清零立即停止层计数。
3. 新鲜有剩余返回 `-1`，否则返回 `ans`。
- 关键不变量：第 `k` 层的节点恰好是"最早 `k` 分钟被传染"的橘子——多源 BFS 首次到达即最短。
- 最优时间复杂度：`O(m × n)`
- 最优空间复杂度：`O(m × n)`

### 最优解代码

```cpp
class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        int m = static_cast<int>(grid.size());
        int n = static_cast<int>(grid[0].size());
        queue<pair<int, int>> q;
        int fresh = 0;
        const int dx[] = {1, -1, 0, 0}, dy[] = {0, 0, 1, -1};
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 2) q.push({i, j}); // 多源同时入队
                else if (grid[i][j] == 1) fresh++;
            }
        }
        int minutes = 0;
        while (!q.empty() && fresh > 0) { // fresh 归零提前停，防止末层多算 1 分钟
            int sz = static_cast<int>(q.size());
            for (int i = 0; i < sz; i++) { // 一次处理整层
                auto [x, y] = q.front(); q.pop();
                for (int d = 0; d < 4; d++) {
                    int nx = x + dx[d], ny = y + dy[d];
                    if (nx >= 0 && nx < m && ny >= 0 && ny < n && grid[nx][ny] == 1) {
                        grid[nx][ny] = 2; // 改值即标记
                        fresh--;
                        q.push({nx, ny});
                    }
                }
            }
            minutes++;
        }
        return fresh == 0 ? minutes : -1;
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | `cnt` + 层锁定 | `fresh` + 同构 | 仅命名差异 |
| 更新逻辑 | 层内传染 + 改 2 即标记 | 相同 | 已达标 |
| 边界处理 | 无新鲜提前停、不可达 -1、例 3 返回 0 均正确 | 相同 | 已达标 |
| 复杂度 | 时间 `O(mn)`、空间 `O(mn)` | 相同 | 已达最优 |

用户解法与推荐最优解逐行同构，本题完成质量高。

## 下一步建议

- 进入下一题：本题多源计时模板已是标准形态，542/286 是同一模板去掉计时的"纯距离填充"变体。
- 复盘任务：说出"为什么多源 BFS 首次到达即最短"——单源 BFS 的层次保证在多源下依然成立，因为各源共享同一套层推进。

## 后续练习

1. `542. 01 Matrix` - 同日题单，同一模板换"计时"为"写距离"，直接迁移。
2. `1162. As Far from Land as Possible` - 多源 BFS 反向（从陆地求最远水域），检验对源选择的理解。

## 代码同步

- 已将最优解作为新的解题函数写入：[src/994.rotting-oranges.cpp](../src/994.rotting-oranges.cpp)
- 新函数名：`orangesRottingOpt`，位于原 `class Solution` 中 `public:` 之前的私有区域
- 保留用户原实现：是
