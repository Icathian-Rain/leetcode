# 题解点评 - 463. Island Perimeter（岛屿的周长）

## 基本信息

- 日期：2026-11-17
- 主题：第 11 周图论 BFS 与 DFS - 网格连通块
- 难度：简单
- 本次结果：逻辑推演正确（用户未明确确认测试状态，暂记待验证）
- 对应源码：[src/463.island-perimeter.cpp](../src/463.island-perimeter.cpp)
- 资料来源：[LeetCode 中国版官方题目页](https://leetcode.cn/problems/island-perimeter/)，2026-11-17 查询
- 约束要点：`1 <= row, col <= 100`；恰好一个岛屿，岛内无湖；对角线不算相邻

## 用户思路概述

1. 扫描每个陆地格，检查它的四个邻居。
2. 邻居越界或为水时，该方向贡献一条边界，`ans++`。
3. 累加所有边界贡献即为周长。

## 用户解法复杂度

- 时间复杂度：`O(m × n)`（每格检查 4 个邻居）
- 空间复杂度：`O(1)`
- 复杂度来源：单次遍历，无搜索、无额外结构。

## 用户代码注释版

> 只在点评文档中展示加注释版本；不把这些注释写回 `src/*.cpp` 的用户原代码。

```cpp
using pii = pair<int, int>;
const int DIRECT[][2] = {{1,0}, {-1,0}, {0, 1}, {0, -1}};
class Solution {
public:
    int islandPerimeter(vector<vector<int>>& grid) {
        int m=grid.size(), n=grid[0].size();
        int ans=0;
        for(int x=0; x<m; x++) {
            for(int y=0; y<n; y++) {
                if(grid[x][y] != 1) continue;      // 只看陆地格
                for(int i=0; i<4; i++) {
                    int nx=x+DIRECT[i][0], ny=y+DIRECT[i][1];
                    // 邻居越界或为水：该方向是岛屿边界，贡献 1 条边
                    if(nx<0 || nx >= m || ny < 0 || ny >= n || grid[nx][ny] == 0) {
                        ans++;
                    }
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
| 不需要搜索 | 纯邻居检查，无 BFS/DFS | 正确且是本题的关键判断：周长是"局部性质"的逐格累加，不需要知道连通块形状；题目保证单岛无湖也免去了多岛区分 | 口头回答"为什么这题不需要连通性信息"——这是本日最有价值的模式识别 |
| 越界即边界 | 邻居出网格也算贡献 | 正确：网格四周视为水 | 已达标 |
| 逐边计数 vs 公式法 | 每格逐方向检查 | 正确；另一种写法是 `4*陆地数 - 2*相邻陆地边数`，只查上左邻居 | 两种等价，本写法更直白 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法（逐格逐向检查） | `O(mn)`/`O(1)`；逻辑最直白，不依赖"单岛"假设 | 每格查 4 个邻居，常数略大 | 通用写法，多岛也适用 |
| 公式法（4L - 2E） | 只查上、左两个邻居，常数减半 | 需要想到公式；多岛时同样成立 | 追求常数优化时 |
| DFS/BFS | —— | 本题完全不需要搜索，属于过度设计 | 反面教材，用于对照"何时不需要搜索" |

## 最优解法

1. 每个陆地格检查四邻居，邻居为水或越界即贡献一条边。
2. 累加全部贡献。
- 关键不变量：周长 = 所有陆地格的"暴露边"总数；每条暴露边恰好被它所属的一个陆地格计一次。
- 最优时间复杂度：`O(m × n)`
- 最优空间复杂度：`O(1)`

### 最优解代码

```cpp
class Solution {
public:
    int islandPerimeter(vector<vector<int>>& grid) {
        int m = static_cast<int>(grid.size());
        int n = static_cast<int>(grid[0].size());
        int ans = 0;
        const int dx[] = {1, -1, 0, 0}, dy[] = {0, 0, 1, -1};
        for (int x = 0; x < m; x++) {
            for (int y = 0; y < n; y++) {
                if (grid[x][y] != 1) continue;
                for (int i = 0; i < 4; i++) {
                    int nx = x + dx[i], ny = y + dy[i];
                    // 越界或水：该方向是暴露边
                    if (nx < 0 || nx >= m || ny < 0 || ny >= n || grid[nx][ny] == 0) {
                        ans++;
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
| 状态定义 | 无状态累加 | 相同 | 已达标 |
| 更新逻辑 | 逐格逐向检查 | 相同 | 已达标 |
| 边界处理 | 越界即边界正确 | 相同 | 已达标 |
| 复杂度 | 时间 `O(mn)`、空间 `O(1)` | 相同 | 已达最优 |

用户解法与推荐最优解逐行同构，本题完成质量高。

## 下一步建议

- 补一次提交确认：本地推演正确，建议在 LeetCode 提交一次以确认记录状态。
- 复盘任务：写出"本题为什么不需要搜索"的一句话；再对照 695 想"面积为什么需要连通信息而周长不需要"。

## 后续练习

1. `1020. Number of Enclaves` - 同日题单，回到搜索，但起点从边界出发，检验"从哪里开始搜"的意识。
2. `1568. Minimum Number of Days to Disconnect Island` - 周长与连通性结合的困难变体，作为周末拔高可选。

## 代码同步

- 已将最优解作为新的解题函数写入：[src/463.island-perimeter.cpp](../src/463.island-perimeter.cpp)
- 新函数名：`islandPerimeterOpt`，位于原 `class Solution` 中 `public:` 之前的私有区域
- 保留用户原实现：是
