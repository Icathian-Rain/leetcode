# 题解点评 - 131. Palindrome Partitioning

## 基本信息

- 日期：2026-06-16
- 主题：回溯 / 字符串切分与段合法性
- 难度：中等
- 本次结果：待提交验证，源码逻辑检查通过
- 对应源码：`src/131.palindrome-partitioning.cpp`
- 资料来源：LeetCode 官方题目页 `https://leetcode.cn/problems/palindrome-partitioning/`
- 查询日期：2026-06-16

## 用户思路概述

1. 先用二维表 `f[left][right]` 预处理每个子串是否为回文串。
2. 用 `path` 保存当前已经切出的回文段。
3. `dfs(s, start)` 表示下一段从 `start` 开始切。
4. 枚举段结束位置 `i`，只有 `s[start..i]` 是回文时才进入下一层。
5. 当 `start == s.length()` 时，说明整串已经切完，收集当前方案。

## 用户解法复杂度

- 时间复杂度：`O(n^2 + n * 2^n)`
- 空间复杂度：`O(n^2 + n)`，不计返回结果
- 复杂度来源：回文表预处理为 `O(n^2)`；切分方案数量指数级，复制路径和子串有额外成本。

## 用户代码注释版

```cpp
class Solution {
    vector<vector<int>> f;
    vector<vector<string>> ans;
    vector<string> path;

public:
    void dfs(string s, int start) {
        if (start == s.length()) {
            ans.push_back(path); // 所有字符都被切分完，当前路径是一组合法方案。
            return;
        }
        for (int i = start; i < s.length(); i++) {
            if (f[start][i]) {
                path.push_back(s.substr(start, i - start + 1));
                dfs(s, i + 1);
                path.pop_back();
            }
        }
    }

    vector<vector<string>> partition(string s) {
        int n = s.length();
        f.assign(n, vector<int>(n, true));
        for (int i = n - 1; i >= 0; i--) {
            for (int j = i + 1; j < n; j++) {
                f[i][j] = (s[i] == s[j]) && f[i + 1][j - 1]; // 由内层子串推出外层。
            }
        }
        dfs(s, 0);
        return ans;
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 切分状态 | `start` 表示下一段起点 | 能把字符串切分转成组合式回溯 | 继续保持“枚举下一段终点”的模型 |
| 段合法性 | 预处理回文表 | 避免每次递归重复检查子串 | 这是本题很稳的优化 |
| 状态传递 | `dfs(string s, ...)` 按值传参 | 每层复制字符串，增加不必要开销 | 改成引用或 lambda 捕获 |
| 状态作用域 | 成员变量保存结果与路径 | 单次可过，多次调用有残留风险 | 推荐入口局部化 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | DP 预处理 + 回溯切分，方向很好 | 字符串按值传递；成员状态复用风险 | 适合本题，稍改即可成为模板 |
| 推荐最优解 | 局部状态、避免字符串复制，回文表语义更明确 | 代码略长 | 适合字符串切分题复用 |

## 最优解法

1. 预处理 `isPalindrome[left][right]`。
2. 用 `start` 表示下一段起点。
3. 枚举 `end`，只有回文段才加入路径。
4. 当 `start == n` 时收集完整切分。

- 最优时间复杂度：`O(n^2 + n * 2^n)`
- 最优空间复杂度：`O(n^2 + n)`，不计返回结果

### 最优解代码

```cpp
class Solution {
public:
    vector<vector<string>> partition(string s) {
        int n = static_cast<int>(s.size());
        vector<vector<bool>> isPalindrome(n, vector<bool>(n, true));
        for (int left = n - 1; left >= 0; --left) {
            for (int right = left + 1; right < n; ++right) {
                isPalindrome[left][right] =
                    (s[left] == s[right]) && isPalindrome[left + 1][right - 1];
            }
        }

        vector<vector<string>> result;
        vector<string> current;
        function<void(int)> dfs = [&](int start) {
            if (start == n) {
                result.push_back(current);
                return;
            }

            for (int end = start; end < n; ++end) {
                if (!isPalindrome[start][end]) {
                    continue;
                }
                current.push_back(s.substr(start, end - start + 1));
                dfs(end + 1);
                current.pop_back();
            }
        };

        dfs(0);
        return result;
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | 成员变量 | 局部变量 | 避免状态残留 |
| 更新逻辑 | 枚举结束位置并递归 | 相同 | 主干正确 |
| 边界处理 | 切到末尾收集 | 相同 | 正确 |
| 复杂度 | 有额外字符串复制 | 避免递归复制字符串 | 改 `dfs` 参数 |

## 下一步建议

这题建议重点复盘“段合法性先判断，再进入下一层”。这个思维可以直接迁移到 IP 地址、括号生成和后续棋盘约束题。

## 后续练习

1. `93. Restore IP Addresses` - 同样是切段，但段数、长度和值域都有约束。
2. `22. Generate Parentheses` - 不切已有字符串，而是在生成过程中维护合法前缀。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/131.palindrome-partitioning.cpp`
- 新函数名：`partitionOpt`
- 保留用户原实现：是
