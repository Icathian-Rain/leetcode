# 题解点评 - 784. Letter Case Permutation

## 基本信息

- 日期：2026-06-18
- 主题：回溯 / 字符串生成与固定位置
- 难度：中等
- 本次结果：待提交验证，源码逻辑检查通过
- 对应源码：`src/784.letter-case-permutation.cpp`
- 资料来源：LeetCode 官方题目页 `https://leetcode.cn/problems/letter-case-permutation/`
- 查询日期：2026-06-18

## 用户思路概述

1. 用 `path = s` 作为当前正在修改的字符串状态。
2. `dfs(idx)` 表示处理到第 `idx` 个字符。
3. 如果当前字符是数字，直接跳到下一位。
4. 如果当前字符是字母，分别改成小写和大写后递归。
5. 当 `idx == path.length()` 时，收集当前字符串。

## 用户解法复杂度

- 时间复杂度：`O(n * 2^L)`，其中 `L` 是字母数量
- 空间复杂度：`O(n)`，不计返回结果
- 复杂度来源：每个字母有两种选择，每个结果复制长度为 `n` 的字符串。

## 用户代码注释版

```cpp
class Solution {
public:
    vector<string> letterCasePermutation(string s) {
        vector<string> ans;
        string path = s;

        function<void(int)> dfs = [&](int idx) {
            if (idx == path.length()) {
                ans.push_back(path); // 所有位置都处理完，当前字符串是一种结果。
                return;
            }

            if (isdigit(path[idx])) {
                dfs(idx + 1); // 数字位置固定，不产生分支。
            } else if (isalpha(path[idx])) {
                path[idx] = tolower(path[idx]);
                dfs(idx + 1);
                path[idx] = toupper(path[idx]);
                dfs(idx + 1);
            }
        };

        dfs(0);
        return ans;
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 固定位置 | 数字直接跳过 | 正确避免无意义分支 | 这是本题和普通子集生成的差异 |
| 可变位置 | 字母分大小写两支 | 正确生成全部结果 | 可以补一个恢复动作，让状态更对称 |
| 状态存放 | 局部 `ans/path` | 没有成员变量复用风险 | 这个习惯很好 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 结构直接，数字和字母分支清楚 | 字母处理后没有恢复到原字符，虽不影响本题结果，但模板感略弱 | 适合本题 |
| 推荐最优解 | 在分支结束后恢复当前字符，回溯动作更完整 | 本质复杂度相同 | 适合字符串位置决策题 |

## 最优解法

1. 用一个可变字符串保存当前状态。
2. 数字位置直接递归下一位。
3. 字母位置分别尝试小写和大写。
4. 处理完当前位置后恢复原字符，保持回溯模板完整。

- 最优时间复杂度：`O(n * 2^L)`
- 最优空间复杂度：`O(n)`，不计返回结果

### 最优解代码

```cpp
class Solution {
public:
    vector<string> letterCasePermutation(string s) {
        vector<string> result;
        string current = s;

        function<void(int)> dfs = [&](int index) {
            if (index == static_cast<int>(current.size())) {
                result.push_back(current);
                return;
            }

            if (isdigit(current[index])) {
                dfs(index + 1);
                return;
            }

            current[index] = static_cast<char>(tolower(current[index]));
            dfs(index + 1);
            current[index] = static_cast<char>(toupper(current[index]));
            dfs(index + 1);
            current[index] = s[index]; // 恢复当前字符。
        };

        dfs(0);
        return result;
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | 局部字符串 | 局部字符串 | 正确 |
| 更新逻辑 | 字母分两支 | 相同 | 主干正确 |
| 边界处理 | 处理到末尾收集 | 相同 | 正确 |
| 回溯动作 | 未恢复原字符 | 分支结束后恢复 | 养成状态对称恢复习惯 |

## 下一步建议

可以把这题归入“当前位置决策”模板：数字是固定位置，字母是可变位置。

## 后续练习

1. `22. Generate Parentheses` - 对比固定长度字符串生成中的合法前缀限制。
2. `78. Subsets` - 对比“元素选/不选”和“字符大小写二选一”。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/784.letter-case-permutation.cpp`
- 新函数名：`letterCasePermutationOpt`
- 保留用户原实现：是
