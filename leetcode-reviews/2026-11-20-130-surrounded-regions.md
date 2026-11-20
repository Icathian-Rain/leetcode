# 题解点评 - 130. Surrounded Regions（被围绕的区域）

## 基本信息

- 日期：2026-11-20
- 主题：第 11 周图论 BFS 与 DFS - 反向搜索与边界思维
- 难度：中等
- 本次结果：通过（用户确认已通过测试）
- 对应源码：[src/130.surrounded-regions.cpp](../src/130.surrounded-regions.cpp)
- 资料来源：[LeetCode 中国版官方题目页](https://leetcode.cn/problems/surrounded-regions/)，2026-11-20 查询
- 约束要点：`1 <= m, n <= 200`；区域内所有 `O` 均不在棋盘边缘才算被围绕；与边缘 `O` 相连的区域必须保留

## 用户思路概述

1. 用独立 `flag` 矩阵标记"与边界相连的 `O` 所在区域"。
2. 外层扫描仅对边界位置的 `O` 启动 DFS：整区域标记 `flag`。
3. 第二遍全扫：`board` 为 `O` 且 `flag` 为 false 的格子即"被围绕的 `O`"，原地翻转为 `X`。

## 用户解法复杂度

- 时间复杂度：`O(m × n)`（每格至多进入 DFS 与两遍扫描）
- 空间复杂度：`O(m × n)`（flag 矩阵 + 递归栈最坏）
- 复杂度来源：反向保护——只从边界出发搜索，内部被围绕区域根本不会被访问到。

## 用户代码注释版

> 只在点评文档中展示加注释版本；不把这些注释写回 `src/*.cpp` 的用户原代码。

```cpp
class Solution {
    void dfs(int x, int y, vector<vector<bool>>& flag, vector<vector<char>>& board) {
        int m=board.size(), n=board[0].size();
        // 越界 / 墙 / 已访问：三条终止合一
        if(x < 0 || x >= m || y < 0 || y >= n || board[x][y] == 'X' || flag[x][y] == true) {
            return;
        }
        flag[x][y] = true;   // 独立标记：不修改 board，翻转动作集中到第二遍
        dfs(x+1, y, flag, board);
        dfs(x-1, y, flag, board);
        dfs(x, y+1, flag, board);
        dfs(x, y-1, flag, board);
        return ;
    }
public:
    void solve(vector<vector<char>>& board) {
        int m=board.size(), n=board[0].size();
        vector<vector<bool>> flag(m, vector<bool>(n, false));
        for(int i=0; i<m; i++) {
            for(int j=0; j<n; j++) {
                if(i == 0 || i == m-1 || j == 0 || j == n-1) {  // 只在边界启动
                    if(board[i][j] == 'O' && flag[i][j] == false) {
                        dfs(i, j, flag, board);
                    }
                }
            }
        }

        for(int i=0; i<m; i++) {
            for(int j=0; j<n; j++) {
                // 遍历中残留的调试打印（提交不影响正确性，但不合仓库约定）
                cout << flag[i][j] << " ";
                if(board[i][j] == 'O' && flag[i][j] == false) {
                    board[i][j] = 'X';   // 未被保护的全部翻转
                }
            }
            cout << endl;
        }
        return ;
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 反向保护 | 从边界 `O` 出发标记安全区，再翻转未保护 `O` | 方向正确——与 1020/417 同一思维：判"被围绕"等价于保护"非被围绕"，后者可从边界一次搜出 | 口头说出这个"取补集"的转换，确认是有意为之而非套路复述 |
| 独立 flag 而非改写 board | 用独立布尔矩阵，第一遍不改内容，第二遍统一翻转 | 正确且是合理的写法选择：写法直观、翻转动作集中；另一种写法是把边界 `O` 暂改为 `'#'`，第三遍恢复——省 flag 但多一遍恢复 | 对照想一遍 `'#'` 版的写法，权衡"标记载体"的选择 |
| 终止条件合一 | 越界 / 墙 / 已访问三条并成一个入口 if | 简洁且正确——DFS 入口保证坐标在界内时才递归扩展 | 已达标 |
| 调试残留 | 主循环里 `cout << flag[i][j]` 每格打印 | 次要级问题（仓库约定）：AGENTS.md 要求提交解法不混入无关调试逻辑；打印在 LeetCode 上无害，但属于应清理项 | 提交前清掉这两行 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法（边界 DFS + 独立 flag + 二遍翻转） | `O(mn)` 最优级；语义分层清楚（保护、翻转分离） | flag 占 `O(mn)`；调试打印残留 | 标准写法之一 |
| 输入即标记（改 `'#'`） | 免 flag 空间；第三遍恢复 | 修改了内容的中间状态若中途出错较难复盘 | 空间受限时的选择 |
| 并查集 | 可扩展到动态查询 | 静态题用不上 | 过度设计 |

## 最优解法

1. 从四条边的每个 `O` 出发 DFS/BFS，将连通块暂标记为 `'#'`。
2. 全扫一遍：剩余 `O`（未被保护的）翻成 `X`，`#` 恢复为 `O`。
- 关键不变量：一定与边界 `O` 连通的 `O` 绝不在被围绕之列；被围绕的 `O` 只能靠内部分布，从边界出发根本不会碰到它们。
- 最优时间复杂度：`O(m × n)`
- 最优空间复杂度：`O(1)`（借用 `'#'` 时；递归栈除外）或 `O(m × n)`（独立 flag 时）

### 最优解代码

```cpp
class Solution {
public:
    void solve(vector<vector<char>>& board) {
        int m = static_cast<int>(board.size());
        int n = static_cast<int>(board[0].size());
        const int dx[] = {1, -1, 0, 0}, dy[] = {0, 0, 1, -1};
        // 从边界每个 O 出发：与边缘相连的区域标记 '#'（输入即标记，免 flag）
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if ((i == 0 || i == m - 1 || j == 0 || j == n - 1) && board[i][j] == 'O') {
                    queue<pair<int, int>> q;
                    board[i][j] = '#';
                    q.push({i, j});
                    while (!q.empty()) {
                        auto [x, y] = q.front(); q.pop();
                        for (int d = 0; d < 4; d++) {
                            int nx = x + dx[d], ny = y + dy[d];
                            if (nx >= 0 && nx < m && ny >= 0 && ny < n && board[nx][ny] == 'O') {
                                board[nx][ny] = '#'; // 入队即标记
                                q.push({nx, ny});
                            }
                        }
                    }
                }
            }
        }
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == 'O') board[i][j] = 'X'; // 未保护的全部翻转
                else if (board[i][j] == '#') board[i][j] = 'O'; // 恢复保护区
            }
        }
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | 独立 flag 矩阵 | 借用 `'#'` 写在输入里 | 两种标记载体的权衡：独立 flag 易复盘，`'#'` 省空间 |
| 更新逻辑 | DFS 边界启动 + 二遍翻转 | BFS + 三遍收尾 | 两种搜索实现等价 |
| 边界处理 | 角点、全 X、单格矩阵均正确 | 相同 | 已达标 |
| 复杂度 | 时间 `O(mn)`、空间 `O(mn)` | 时间相同、空间 `O(1)` 辅助 | 量级相同，载体不同 |

## 下一步建议

- 进入下一题：本题与 1254 是镜像问题（保护 O / 数水围的陆地），对照间隔最近。
- 复盘任务：清掉调试打印后，说出"被围绕判定 = 边界连通取补集"的一句转换。

## 后续练习

1. `1254. Number of Closed Islands` - 同日题单，同一"边界保护"思想在 0/1 语义反转的网格上。
2. `1020. Number of Enclaves` - 已完成（2026-11-17 记录待验证），三题（1020/130/1254）实为同族，可一起做一次族内对比复盘。

## 代码同步

- 已将最优解作为新的解题函数写入：[src/130.surrounded-regions.cpp](../src/130.surrounded-regions.cpp)
- 新函数名：`solveOpt`，位于原 `class Solution` 中 `public:` 之前的私有区域
- 保留用户原实现：是（含调试打印，未替用户清理）
