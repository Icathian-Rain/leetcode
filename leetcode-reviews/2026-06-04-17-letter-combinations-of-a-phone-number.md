# 题解点评 - 17. Letter Combinations of a Phone Number

## 基本信息

- 日期：2026-06-04
- 主题：回溯，第 1 天枚举入口与路径意识
- 难度：中等
- 本次结果：有边界错误，递归主体正确
- 对应源码：`src/17.letter-combinations-of-a-phone-number.cpp`
- 资料来源：本地周计划与源码，题目信息沿用第 7 周计划的 LeetCode 官方校准记录
- 查询日期：2026-06-03

## 用户思路概述

1. 建立数字到字母串的映射 `keyboard`。
2. 用 `str` 保存当前已经拼出的字母组合。
3. 递归参数 `idx` 表示处理到第几位数字；当前位逐个选择可用字母，进入下一位后再撤销。
4. 当 `idx == digits.size()` 时，将当前字符串加入答案。

## 用户解法复杂度

- 时间复杂度：`O(4^n * n)`
- 空间复杂度：`O(n)`，不计输出结果
- 复杂度来源：每一位最多有 4 个选择，生成每个结果需要保存长度为 `n` 的字符串；递归深度为 `n`。

## 用户代码注释版

```cpp
class Solution {
public:
    vector<string> ans;
    string str;
    vector<string> keyboard;

    void dfs(string digits, int idx) {
        if(idx == digits.size()) {
            ans.push_back(str); // 空 digits 时也会走到这里，导致返回 [""]。
            return;
        }
        int pos = digits[idx] - '0';
        for(int i=0; i<keyboard[pos].size(); i++) {
            str.push_back(keyboard[pos][i]); // 选择当前数字对应的一个字母。
            dfs(digits, idx+1);
            str.pop_back(); // 撤销当前字母，尝试同层下一个字母。
        }
    }

    vector<string> letterCombinations(string digits) {
        keyboard = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
        dfs(digits, 0);
        return ans;
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 层含义 | `idx` 表示当前处理的数字位置 | 搜索树结构正确 | 继续保持“每层处理一位”的口述方式 |
| 路径维护 | `push_back` 和 `pop_back` 成对出现 | 不会污染其他组合 | 这是回溯核心动作 |
| 空输入 | 没有提前处理 `digits.empty()` | 会返回 `[""]`，不符合题意 | 入口处直接返回空数组 |
| 成员状态 | `ans/str/keyboard` 是成员变量 | 多次调用会残留 | 推荐改成局部变量和 lambda |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 主体递归正确，选择列表清楚 | 空输入错误，成员变量复用风险 | 修边界后可提交 |
| 推荐最优解 | 入口处理空串，状态局部化 | 需要熟悉 lambda 写法 | 更稳的提交版本 |

## 最优解法

1. 如果 `digits` 为空，直接返回空数组。
2. 用局部映射表、局部结果和当前路径，避免成员状态残留。
3. 每层根据当前数字取出可选字母，逐个选择后进入下一位，返回后撤销。

- 最优时间复杂度：`O(4^n * n)`
- 最优空间复杂度：`O(n)`，不计输出结果

### 最优解代码

```cpp
class Solution {
public:
    vector<string> letterCombinations(string digits) {
        if (digits.empty()) {
            return {};
        }

        const vector<string> mapping = {
            "", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"
        };
        vector<string> result;
        string path;

        function<void(int)> dfs = [&](int index) {
            if (index == digits.size()) {
                result.push_back(path);
                return;
            }
            for (char letter : mapping[digits[index] - '0']) {
                path.push_back(letter);
                dfs(index + 1);
                path.pop_back();
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
| 状态定义 | 成员 `ans/str/keyboard` | 入口局部变量 | 避免跨调用残留 |
| 更新逻辑 | 当前位逐个选字母 | 相同 | 主体思路保留 |
| 边界处理 | 空串进入终止条件并收集 | 空串直接返回空数组 | 先读清题意的空输入 |
| 复杂度 | `O(4^n*n)` | `O(4^n*n)` | 主要改正确性和稳定性 |

## 下一步建议

建议先修空输入，再用 `"23"` 和 `""` 各手推一次。只要边界补上，这题的回溯主体已经很好。

## 后续练习

1. `784. Letter Case Permutation` - 继续练习字符串每一位的选择。
2. `22. Generate Parentheses` - 练习生成过程中持续保持合法状态。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/17.letter-combinations-of-a-phone-number.cpp`
- 新函数名：`letterCombinationsOpt`
- 保留用户原实现：是
