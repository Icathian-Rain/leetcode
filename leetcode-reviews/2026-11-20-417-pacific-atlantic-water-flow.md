# 题解点评 - 417. Pacific Atlantic Water Flow（太平洋大西洋水流问题）

## 基本信息

- 日期：2026-11-20
- 主题：第 11 周图论 BFS 与 DFS - 反向搜索与边界思维
- 难度：中等
- 本次结果：通过（用户确认已通过测试）
- 对应源码：[src/417.pacific-atlantic-water-flow.cpp](../src/417.pacific-atlantic-water-flow.cpp)
- 资料来源：[LeetCode 中国版官方题目页](https://leetcode.cn/problems/pacific-atlantic-water-flow/)，2026-11-20 查询
- 约束要点：`1 <= m, n <= 200`，`0 <= heights <= 10^5`；水可流向高度**小于等于**当前格的相邻格（等高可流动）

## 用户思路概述

1. 反向建模：不从每个格子正向试流，而是从海洋"逆流而上"——太平洋以左列 + 上行为源点，大西洋以右列 + 下行为源点。
2. 两张独立标记矩阵 `pflag`/`aflag`：源点先标记再入队（多源一次入队）；BFS 扩展条件是邻居未标记且 `heights[邻居] >= heights[当前]`——逆流方向上"邻居不低于当前"即水能流下来。
3. 两遍 BFS 结束后，双标记交集即能同时到达两洋的格子。

## 用户解法复杂度

- 时间复杂度：`O(m × n)`（两遍 BFS，每格在每张标记下至多入队一次）
- 空间复杂度：`O(m × n)`（两张标记矩阵 + 队列）
- 复杂度来源：多源入队与"标记即访问"保证每格至多处理一次；反向搜索让"全格逐点正向试流"（`O(mn · mn)` 级）变成两遍线性扫描。

## 用户代码注释版

> 只在点评文档中展示加注释版本；不把这些注释写回 `src/*.cpp` 的用户原代码。

```cpp
using pii = pair<int, int>;
const int DIRECT[][2]={{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
class Solution {
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        int m=heights.size(), n=heights[0].size();
        vector<vector<int>> pflag(m, vector<int>(n, false)), aflag(m, vector<int>(n, false));
        // 太平洋源点：左列全部 + 上行（角点只入队一次，j 从 1 起）
        queue<pii> q;
        for(int i=0; i<m; i++) {
            pflag[i][0]=true;
            q.push({i, 0});
        }
        for(int j=1; j<n; j++) {
            pflag[0][j]=true;
            q.push({0, j});
        }
        while(!q.empty()) {
            auto [x, y] = q.front(); q.pop();
            for(int i=0; i<4; i++) {
                int nx=x+DIRECT[i][0], ny=y+DIRECT[i][1];
                // 逆流而上：邻居不低于当前，水才可能从邻居流到当前
                if(nx>=0 && nx<m && ny>=0 && ny<n && pflag[nx][ny]==false && heights[nx][ny]>=heights[x][y]) {
                    pflag[nx][ny]=true;
                    q.push({nx, ny});
                }
            }
        }

        // 大西洋源点：右列全部 + 下行（角点不重复）
        for(int i=0; i<m; i++) {
            aflag[i][n-1]=true;
            q.push({i, n-1});
        }
        for(int j=0; j<n-1; j++) {
            aflag[m-1][j]=true;
            q.push({m-1, j});
        }
        while(!q.empty()) {
            auto [x, y] = q.front(); q.pop();
            for(int i=0; i<4; i++) {
                int nx=x+DIRECT[i][0], ny=y+DIRECT[i][1];
                if(nx>=0 && nx<m && ny>=0 && ny<n && aflag[nx][ny]==false && heights[nx][ny]>=heights[x][y]) {
                    aflag[nx][ny]=true;
                    q.push({nx, ny});
                }
            }
        }

        // 双标记交集即答案
        vector<vector<int>> ans;
        for(int i=0; i<m; i++) {
            for(int j=0; j<n; j++) {
                if(pflag[i][j] && aflag[i][j]) {
                    ans.push_back({i, j});
                }
            }
        }
        return ans;
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 反向建模 | 从海洋出发逆流标记，而非从每格正向试流 | 本题最核心的决策，方向选对；与 1020/542 的"反向/目标出发"一脉相承，说明这一思维已稳定 | 口头论证"逆流条件为什么是 `>=` 而不是 `>`"——等高可流动的题面条件要精确落到比较符上 |
| 角点去重 | 太平洋侧 `j` 从 1 起、大西洋侧 `j < n-1` | 细节正确（角点不重复入队）；实际上重复入队一次也无害（标记已置位），这个处理是"精确但不必要"的好习惯 | 知道它是优化而非正确性要求即可 |
| 两遍代码的重复 | 太平洋段与大西洋段 structurally 逐行相同，仅标记矩阵与源点不同 | 次要级问题：约 20 行重复逻辑，复用一个私有辅助函数（传入标记矩阵和源点集合）可减半 | 复盘时用辅助函数重写一遍，对照感受"参数化的两个变化点" |
| 代码卫生 | 源码第 71-73 行有多余空行、`// p test` 调试注释 | 次要级问题：无功能影响，但提交文件中残留调试痕迹 | 按 AGENTS.md 约定，提交解法保持最小化 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法（双遍多源 BFS） | `O(mn)` 最优级；与本周多源模板完全同构 | 两段重复代码 | 边界反向可达类标准写法 |
| 递归 DFS 版 | 同复杂度，代码可稍短 | 两百规模无栈风险，通用性略弱于 BFS | 等价选择 |
| 正向逐格试流 | 思路直白 | `O(mn · mn)` 级，正确答案但复杂度不达标 | 反面教材 |

## 最优解法

1. 抽象出"从一组边界源点逆流标记"的辅助函数：传入边界集合与目标标记矩阵。
2. 太平洋：左列 + 上行入队，标记能逆流到达的格；大西洋：右列 + 下行同理。
3. 两张标记的交集即答案。
- 关键不变量：水从 `u` 流到 `v`（`h[v] <= h[u]`）⟺ 逆流搜索中从 `v` 能爬到 `u`（`h[u] >= h[v]`），同一比较符的对偶关系保证反向标记与正向可达完全等价。
- 最优时间复杂度：`O(m × n)`
- 最优空间复杂度：`O(m × n)`

### 最优解代码

```cpp
class Solution {
    // 从一组边界源点逆流标记可达格：邻居不低于当前即可回溯
    void bfsMark(vector<vector<int>>& h, vector<vector<char>>& mark, vector<pair<int,int>>& seeds) {
        const int dx[] = {1, -1, 0, 0}, dy[] = {0, 0, 1, -1};
        int m = static_cast<int>(h.size());
        int n = static_cast<int>(h[0].size());
        queue<pair<int,int>> q;
        for (auto [x, y] : seeds) {
            mark[x][y] = 1;     // 入队即标记
            q.push({x, y});
        }
        while (!q.empty()) {
            auto [x, y] = q.front(); q.pop();
            for (int d = 0; d < 4; d++) {
                int nx = x + dx[d], ny = y + dy[d];
                if (nx >= 0 && nx < m && ny >= 0 && ny < n
                    && !mark[nx][ny] && h[nx][ny] >= h[x][y]) { // 等高可流动
                    mark[nx][ny] = 1;
                    q.push({nx, ny});
                }
            }
        }
    }
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        int m = static_cast<int>(heights.size());
        int n = static_cast<int>(heights[0].size());
        vector<vector<char>> pac(m, vector<char>(n, 0)), atl(m, vector<char>(n, 0));
        vector<pair<int,int>> pSeeds, aSeeds;
        for (int j = 0; j < n; j++) {
            aSeeds.push_back({m - 1, j});          // 下行属于大西洋
            if (j == 0) continue;
            pSeeds.push_back({0, j});              // 上行属于太平洋（角点归下式）
        }
        for (int i = 0; i < m; i++) {
            pSeeds.push_back({i, 0});              // 左列属于太平洋
            if (i != m - 1) aSeeds.push_back({i, n - 1}); // 右列属于大西洋
        }
        bfsMark(heights, pac, pSeeds);
        bfsMark(heights, atl, aSeeds);
        // 双标记交集即双洋可达格
        vector<vector<int>> ans;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (pac[i][j] && atl[i][j]) ans.push_back({i, j});
            }
        }
        return ans;
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | 两段独立 BFS + 独立标记 | 同一辅助函数参数化复用 | 重复逻辑收进 helper，两个变化点（标记与源点）作参数 |
| 更新逻辑 | 入队即标记 + `>=` 逆流条件 | 相同 | 已达标 |
| 边界处理 | 角点去重正确 | 角点归属显式分类 | 已达标 |
| 复杂度 | 时间 `O(mn)`、空间 `O(mn)` | 相同 | 已达最优 |

## 下一步建议

- 进入下一题：本题双边界反向标记是本日的模板题，130/1254 是它的两个退化变体。
- 复盘任务：说出"题面单向流动（往低处）为什么能换成反向搜索（往高处爬）"的一句对偶论证。

## 后续练习

1. `130. Surrounded Regions` - 同日题单，本题去掉高度权重后的纯连通版。
2. `778. Swim in Rising Water` - 高度矩阵 + 上升水位下的最早时刻，是本题高度语义的进阶（配合二分/并查集），作为周末拔高可选。

## 代码同步

- 已将最优解作为新的解题函数写入：[src/417.pacific-atlantic-water-flow.cpp](../src/417.pacific-atlantic-water-flow.cpp)
- 新函数名：`pacificAtlanticOpt`（配套私有辅助 `bfsMark`），位于原 `class Solution` 中 `public:` 之前的私有区域
- 保留用户原实现：是（含两段重复结构，未替用户重构）
