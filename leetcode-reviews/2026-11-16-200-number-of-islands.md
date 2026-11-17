# 题解点评 - 200. Number of Islands（岛屿数量）

## 基本信息

- 日期：2026-11-16
- 主题：第 11 周图论 BFS 与 DFS - 图遍历入口
- 难度：中等
- 本次结果：通过（用户确认已测试通过）
- 对应源码：[src/200.number-of-islands.cpp](../src/200.number-of-islands.cpp)
- 资料来源：[LeetCode 中国版官方题目页](https://leetcode.cn/problems/number-of-islands/)，2026-11-16 查询
- 约束要点：`1 <= m, n <= 300`；`grid[i][j]` 为 `'0'` 或 `'1'`；四方向连通；网格四周视为水

## 用户思路概述

1. 扫描整个网格，遇到 `'1'` 时岛屿计数 `ans++`，并以该格为起点 DFS。
2. DFS 把当前格改为 `'0'`（沉岛，即访问标记），再向四个方向递归所有为 `'1'` 的邻居。
3. 一次 DFS 恰好淹没一座完整岛屿；外层扫描继续找下一座。
4. 返回计数。

## 用户解法复杂度

- 时间复杂度：`O(m × n)`（每格至多被访问常数次：外层扫一次 + DFS 内被邻居检查）
- 空间复杂度：`O(m × n)`（递归栈最坏，如整图全是陆地时的蛇形路径）
- 复杂度来源：DFS 沉岛保证每格只进递归一次；外层双重循环线性扫描。

## 用户代码注释版

> 只在点评文档中展示加注释版本；不把这些注释写回 `src/*.cpp` 的用户原代码。

```cpp
const int DIRECT[][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
class Solution {
    void dfs(vector<vector<char>>& grid, int x, int y) {
        int m=grid.size(), n=grid[0].size();
        grid[x][y] = '0';   // 沉岛：改写原图即访问标记，防止环上重复访问
        for(int i=0; i<4; i++) {
            int nx=x+DIRECT[i][0], ny=y+DIRECT[i][1];
            if(nx >= 0 && nx < m && ny >= 0 && ny < n && grid[nx][ny] == '1') {
                dfs(grid, nx, ny);
            }
        }
        return ;
    }
public:
    int numIslands(vector<vector<char>>& grid) {
        int m=grid.size(), n=grid[0].size();
        int ans=0;
        for(int x=0; x<m; x++) {
            for(int y=0; y<n; y++) {
                if(grid[x][y] == '1') {
                    dfs(grid, x, y);   // 一次 DFS 恰好淹没一座岛
                    ans++;
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
| 沉岛即标记 | 进入 DFS 即改 `'0'`，不撤销 | 正确：与 733 的"改色即标记"同源，本题改写后不再满足扩展条件 | 已达标；把两题的标记技巧归为一句话记 |
| 计数时机 | 外层遇 `'1'` 即计数并整岛淹没 | 正确：计数与 DFS 的对应关系（一次 DFS = 一座岛）是本题核心 | 口头回答"为什么外层每遇一次 '1' 恰是一座新岛" |
| 递归深度 | DFS 递归，`m,n <= 300` | 300×300 全陆地最坏递归深度可达 9×10^4，LeetCode 默认栈通常可承受；但这是本题最经典的风险点 | 知道大规模网格应换 BFS/迭代 DFS；本题规模下 DFS 是通行选择 |
| 递归终止 | 无显式 base case | 正确：越界和 `'0'` 判断在循环内完成，递归入口保证坐标合法，无需额外终止条件 | 想清"边界检查放循环里还是函数入口"两种写法的取舍 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法（DFS 沉岛） | `O(mn)` 最优级；代码最短 | 递归栈深风险（本题规模内安全） | 本题规模下的标准写法 |
| BFS 沉岛 | 无栈深风险 | 代码略长，需要队列和坐标打包 | 大规模网格或面试官要求时 |
| 并查集 | 可扩展到动态加边/在线查询（如 305. Number of Islands II） | 静态统计时杀鸡用牛刀 | 动态版本或第 12 周主题前奏 |

## 最优解法

1. 外层扫描，遇 `'1'` 计数加一。
2. 从该格 BFS（或 DFS）把整座岛改成 `'0'`：入队即沉岛，四方向邻居为 `'1'` 时入队并改写。
3. 扫描结束返回计数。
- 关键不变量：任意时刻网格中剩余的 `'1'` 都属于尚未统计的岛；一次搜索恰好消除一座完整连通块。
- 最优时间复杂度：`O(m × n)`
- 最优空间复杂度：`O(m × n)`（BFS 队列或 DFS 栈最坏；BFS 队列实际可到 `O(min(m,n))`）

### 最优解代码

```cpp
class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int m = static_cast<int>(grid.size());
        int n = static_cast<int>(grid[0].size());
        int ans = 0;
        const int dx[] = {1, -1, 0, 0}, dy[] = {0, 0, 1, -1};
        for (int x = 0; x < m; x++) {
            for (int y = 0; y < n; y++) {
                if (grid[x][y] != '1') continue;
                ans++; // 遇到新岛：一次 BFS 恰好淹没一座
                queue<pair<int, int>> q;
                grid[x][y] = '0'; // 入队即沉岛，改写即访问标记
                q.push({x, y});
                while (!q.empty()) {
                    auto [cx, cy] = q.front(); q.pop();
                    for (int i = 0; i < 4; i++) {
                        int nx = cx + dx[i], ny = cy + dy[i];
                        if (nx >= 0 && nx < m && ny >= 0 && ny < n && grid[nx][ny] == '1') {
                            grid[nx][ny] = '0'; // 防止重复入队
                            q.push({nx, ny});
                        }
                    }
                }
            }
        }
        return ans;
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | 递归沉岛 | 队列沉岛 | 大规模网格优先 BFS；本题两者皆可 |
| 更新逻辑 | 进入即改 `'0'` | 入队即改 `'0'` | 两种标记时机都正确，注意各自防重入队/重入递归的方式 |
| 边界处理 | 越界判断在循环内 | 相同 | 已达标 |
| 复杂度 | 时间 `O(mn)`、空间 `O(mn)`（栈） | 相同（队列） | 已达最优 |

用户解法正确且达最优复杂度；同步的 `Opt` 函数展示 BFS 版本，与 733 的 BFS 风格统一。

## 下一步建议

- 进入下一题单：第 1 天三题全部通过，图遍历入口完成。
- 复盘任务：把 1971、733、200 三题的"访问标记"写法列成一句话对照（不撤销 / 改色即标记 / 沉岛即标记），确认理解统一。

## 后续练习

1. `695. Max Area of Island` - 第 2 天题单首题，本题骨架加"块内累积面积"，直接迁移。
2. `305. Number of Islands II` - 动态加岛的并查集版本（Plus 题），作为扩展视野可选。

## 代码同步

- 已将最优解作为新的解题函数写入：[src/200.number-of-islands.cpp](../src/200.number-of-islands.cpp)
- 新函数名：`numIslandsOpt`，位于原 `class Solution` 中 `public:` 之前的私有区域
- 保留用户原实现：是
