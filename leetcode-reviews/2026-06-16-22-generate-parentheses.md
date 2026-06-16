# 题解点评 - 22. Generate Parentheses

## 基本信息

- 日期：2026-06-16
- 主题：回溯 / 合法前缀生成
- 难度：中等
- 本次结果：待提交验证，源码逻辑检查通过
- 对应源码：`src/22.generate-parentheses.cpp`
- 资料来源：LeetCode 官方题目页 `https://leetcode.cn/problems/generate-parentheses/`
- 查询日期：2026-06-16

## 用户思路概述

1. 用 `path` 保存当前生成的括号串。
2. `left` 表示已经放入的左括号数量，`right` 表示已经放入的右括号数量。
3. 当 `left == n && right == n` 时，当前字符串完整合法，加入答案。
4. 当 `left > right` 时可以放右括号，保证任意前缀中右括号不超过左括号。
5. 当 `left < n` 时可以继续放左括号。

## 用户解法复杂度

- 时间复杂度：`O(C_n * n)`，其中 `C_n` 是第 `n` 个卡特兰数
- 空间复杂度：`O(n)`，不计返回结果
- 复杂度来源：只生成合法括号串，每个答案长度为 `2n`，递归深度为 `2n`。

## 用户代码注释版

```cpp
class Solution {
public:
    vector<string> ans;
    string path;

    void dfs(int left, int right, int n) {
        if (left == n && right == n) {
            ans.push_back(path); // 左右括号都用完，当前路径是合法答案。
            return;
        }
        if (left > right) {
            path.push_back(')');
            dfs(left, right + 1, n);
            path.pop_back();
        }
        if (left < n) {
            path.push_back('(');
            dfs(left + 1, right, n);
            path.pop_back();
        }
    }

    vector<string> generateParenthesis(int n) {
        dfs(0, 0, n);
        return ans;
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 合法前缀 | 只在 `left > right` 时放右括号 | 正确避免生成非法前缀 | 这是本题的核心不变量 |
| 左括号上限 | `left < n` 才放左括号 | 正确控制长度 | 继续保持“生成时合法”而不是生成后筛 |
| 分支顺序 | 先尝试右括号，再尝试左括号 | 正确性不受影响，只影响输出顺序 | 常见写法先左后右，更贴近构造直觉 |
| 状态作用域 | 成员变量保存答案和路径 | 单次调用可过，多次调用有残留风险 | 推荐局部化 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 合法性条件正确，回溯动作完整 | 成员变量复用风险；分支顺序略不常见 | 适合本题 |
| 推荐最优解 | 状态局部化，先左后右，模板更常见 | 本质复杂度相同 | 适合合法前缀生成题 |

## 最优解法

1. 维护已经放入的左右括号数量。
2. 左括号数量小于 `n` 时，可以放左括号。
3. 右括号数量小于左括号数量时，可以放右括号。
4. 两者都达到 `n` 时收集答案。

- 最优时间复杂度：`O(C_n * n)`
- 最优空间复杂度：`O(n)`，不计返回结果

### 最优解代码

```cpp
class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> result;
        string current;

        function<void(int, int)> dfs = [&](int left, int right) {
            if (left == n && right == n) {
                result.push_back(current);
                return;
            }

            if (left < n) {
                current.push_back('(');
                dfs(left + 1, right);
                current.pop_back();
            }
            if (right < left) {
                current.push_back(')');
                dfs(left, right + 1);
                current.pop_back();
            }
        };

        dfs(0, 0);
        return result;
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | `left/right` | 相同 | 正确 |
| 更新逻辑 | 合法时放右或左 | 先左后右 | 输出顺序更常见 |
| 边界处理 | 完整使用后收集 | 相同 | 正确 |
| 复杂度 | `O(C_n*n)` | `O(C_n*n)` | 已是标准生成复杂度 |

## 下一步建议

这题建议重点复盘“生成过程中保持合法”。后面遇到棋盘约束、网格路径时，也要尽量在进入下一层前排除非法状态。

## 后续练习

1. `93. Restore IP Addresses` - 继续练习生成过程中剪掉非法前缀。
2. `51. N-Queens` - 把合法前缀思想迁移到棋盘放置。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/22.generate-parentheses.cpp`
- 新函数名：`generateParenthesisOpt`
- 保留用户原实现：是
