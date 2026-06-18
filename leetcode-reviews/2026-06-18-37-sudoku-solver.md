# 题解点评 - 37. Sudoku Solver

## 基本信息

- 日期：2026-06-18
- 主题：回溯 / 高约束棋盘填数
- 难度：困难
- 本次结果：有主要风险，约束建模正确
- 对应源码：`src/37.sudoku-solver.cpp`
- 资料来源：LeetCode 官方题目页 `https://leetcode.cn/problems/sudoku-solver/`
- 查询日期：2026-06-18

## 用户思路概述

1. 用 `line`、`column`、`block` 分别记录行、列、九宫格中哪些数字已经出现。
2. 先扫描棋盘，把空格位置放入 `spaces`。
3. `dfs(board, pos)` 表示正在填第 `pos` 个空格。
4. 对当前空格尝试数字 `1..9`，只有行列宫都未使用时才放入。
5. 填完整个 `spaces` 后设置 `valid = true`，用全局标记停止后续搜索。

## 用户解法复杂度

- 时间复杂度：最坏 `O(9^E)`，`E` 为空格数量
- 空间复杂度：`O(E + 1)`
- 复杂度来源：每个空格最多尝试 9 个数字，约束表让合法性判断为 `O(1)`。

## 用户代码注释版

```cpp
class Solution {
    bool line[9][9];
    bool column[9][9];
    bool block[3][3][9];
    bool valid;
    vector<pair<int, int>> spaces;

    void dfs(vector<vector<char>>& board, int pos) {
        if (pos == spaces.size()) {
            valid = true;
            return;
        }

        auto [i, j] = spaces[pos];
        for (int digit = 0; digit < 9 && !valid; digit++) {
            if (!line[i][digit] && !column[j][digit] && !block[i / 3][j / 3][digit]) {
                line[i][digit] = column[j][digit] = block[i / 3][j / 3][digit] = true;
                board[i][j] = digit + '0' + 1;
                dfs(board, pos + 1);
                line[i][digit] = column[j][digit] = block[i / 3][j / 3][digit] = false;
                // 风险：失败分支返回时没有把 board[i][j] 恢复成 '.'。
            }
        }
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 约束建模 | 行、列、宫格三张表 | 正确把合法性判断降到 `O(1)` | 模型非常适合本题 |
| 空格序列 | 先收集 `spaces` | 递归只关注待填格，结构清楚 | 之后可优化为空格排序 |
| 回溯恢复 | 恢复约束表，但未恢复棋盘字符 | 可能留下失败分支的临时数字，虽然约束表主导搜索 | 失败时同步恢复 `board[i][j] = '.'` |
| 调试输出 | `cout << spaces.size()` | LeetCode 提交不应输出调试信息 | 删除调试输出 |
| 状态复用 | `spaces` 没有在入口清空 | 多次调用同一对象会残留 | 入口清空或局部化 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 约束表和空格递归方向正确 | 棋盘未恢复、调试输出、成员状态复用风险 | 思路可用，实现要修稳 |
| 推荐最优解 | 局部状态、失败分支恢复棋盘、无调试输出 | 仍是指数搜索 | 标准数独回溯 |

## 最优解法

1. 扫描棋盘，初始化行、列、宫格约束表。
2. 收集所有空格。
3. 递归填空格列表中的下一个位置。
4. 尝试数字时同步更新棋盘和三张约束表。
5. 分支失败时恢复棋盘和约束表；分支成功时直接返回。

- 最优时间复杂度：最坏 `O(9^E)`
- 最优空间复杂度：`O(E + 1)`

### 最优解代码

```cpp
class Solution {
public:
    void solveSudoku(vector<vector<char>>& board) {
        bool rows[9][10] = {};
        bool cols[9][10] = {};
        bool boxes[3][3][10] = {};
        vector<pair<int, int>> blanks;

        for (int row = 0; row < 9; ++row) {
            for (int col = 0; col < 9; ++col) {
                if (board[row][col] == '.') {
                    blanks.push_back({row, col});
                } else {
                    int digit = board[row][col] - '0';
                    rows[row][digit] = cols[col][digit] = boxes[row / 3][col / 3][digit] = true;
                }
            }
        }

        function<bool(int)> dfs = [&](int index) {
            if (index == static_cast<int>(blanks.size())) return true;

            auto [row, col] = blanks[index];
            for (int digit = 1; digit <= 9; ++digit) {
                if (rows[row][digit] || cols[col][digit] || boxes[row / 3][col / 3][digit]) continue;
                rows[row][digit] = cols[col][digit] = boxes[row / 3][col / 3][digit] = true;
                board[row][col] = static_cast<char>('0' + digit);
                if (dfs(index + 1)) return true;
                board[row][col] = '.';
                rows[row][digit] = cols[col][digit] = boxes[row / 3][col / 3][digit] = false; // 回溯时恢复棋盘和约束表。
            }
            return false;
        };

        dfs(0);
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | 成员约束表和 `spaces` | 入口局部状态 | 避免多次调用残留 |
| 更新逻辑 | 设置数字和约束，递归 | 相同 | 主干正确 |
| 边界处理 | 用 `valid` 停止搜索 | 递归返回 bool 停止搜索 | 控制流更直接 |
| 恢复动作 | 只恢复约束表 | 同时恢复棋盘和约束表 | 保持状态一致 |

## 下一步建议

建议重写当前题一次，把 `valid` 改成 `bool dfs` 返回值，并删除所有调试输出。这样数独模板会更接近 N 皇后那种“选择、递归、撤销”的标准形态。

## 后续练习

1. `51. N-Queens` - 对比列/对角线约束和行/列/宫格约束。
2. `52. N-Queens II` - 练习只计数时如何复用棋盘约束模板。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/37.sudoku-solver.cpp`
- 新函数名：`solveSudokuOpt`
- 保留用户原实现：是
