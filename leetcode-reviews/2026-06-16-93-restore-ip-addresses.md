# 题解点评 - 93. Restore IP Addresses

## 基本信息

- 日期：2026-06-16
- 主题：回溯 / 固定段数字符串切分
- 难度：中等
- 本次结果：待提交验证，源码逻辑检查通过
- 对应源码：`src/93.restore-ip-addresses.cpp`
- 资料来源：LeetCode 官方题目页 `https://leetcode.cn/problems/restore-ip-addresses/`
- 查询日期：2026-06-16

## 用户思路概述

1. 用 `path` 保存当前已经切出的 IP 段数值。
2. `dfs(s, start)` 表示下一段从 `start` 开始。
3. 如果遇到字符 `'0'`，只允许切出单独的 `0` 段，避免前导零。
4. 否则向后累积最多若干位数字，只要数值在 `0..255` 就继续递归。
5. 当字符串用完且正好切出 4 段时，用 `tostr()` 拼接答案。

## 用户解法复杂度

- 时间复杂度：`O(1)`，更具体地说搜索分支上界很小
- 空间复杂度：`O(1)`，不计返回结果
- 复杂度来源：IP 地址固定为 4 段，每段最多 3 位，因此递归深度和分支数量都有常数上界。

## 用户代码注释版

```cpp
class Solution {
public:
    vector<string> ans;
    vector<int> path;

    string tostr() {
        string res = "";
        for (int i = 0; i < 4; i++) {
            res += to_string(path[i]);
            if (i != 3) res += ".";
        }
        return res;
    }

    void dfs(string& s, int start) {
        if (start == s.length() || path.size() == 4) {
            if (start == s.length() && path.size() == 4) {
                ans.push_back(tostr()); // 字符用完且正好 4 段才合法。
            }
            return;
        }
        if (s[start] == '0') {
            path.push_back(0); // 前导零规则：0 只能单独成段。
            dfs(s, start + 1);
            path.pop_back();
            return;
        }

        int tmp = 0;
        for (int i = start; i < s.length(); i++) {
            tmp = tmp * 10 + (s[i] - '0');
            if (tmp >= 0 && tmp <= 255) {
                path.push_back(tmp);
                dfs(s, i + 1);
                path.pop_back();
            } else {
                break;
            }
        }
    }

    vector<string> restoreIpAddresses(string s) {
        dfs(s, 0);
        return ans;
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 段数限制 | `path.size() == 4` 停止 | 正确避免超过 4 段 | 可进一步用剩余字符数剪枝 |
| 前导零 | `'0'` 单独处理 | 正确覆盖 `0000`、`010` 等边界 | 这是 IP 题最常错的点，处理得不错 |
| 段长度 | 依靠数值超过 255 停止 | 正确性可过，但循环可限制最多 3 位 | 写 `i < start + 3` 更直接 |
| 状态作用域 | 成员变量保存答案和路径 | 单次调用可过，多次调用有残留风险 | 推荐局部化 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 前导零和值域判断明确，主干正确 | 缺少剩余长度剪枝；段长度上界不够显式 | 适合本题，效率可更干净 |
| 推荐最优解 | 段数、剩余字符数、前导零和值域都显式约束 | 代码稍长 | 适合固定段数字符串切分题 |

## 最优解法

1. 用 `segments` 保存已经切出的字符串段。
2. 每层先检查剩余字符数是否能填满剩余段数。
3. 枚举当前段长度 1 到 3。
4. 过滤前导零和值域超过 255 的段。
5. 正好 4 段且用完字符串时收集答案。

- 最优时间复杂度：`O(1)`
- 最优空间复杂度：`O(1)`，不计返回结果

### 最优解代码

```cpp
class Solution {
public:
    vector<string> restoreIpAddresses(string s) {
        vector<string> result;
        vector<string> segments;

        function<void(int)> dfs = [&](int start) {
            int used = static_cast<int>(segments.size());
            int remainChars = static_cast<int>(s.size()) - start;
            int remainSegments = 4 - used;
            if (remainChars < remainSegments || remainChars > remainSegments * 3) {
                return; // 剩余字符数量无法填满剩余段数。
            }

            if (used == 4) {
                if (start == static_cast<int>(s.size())) {
                    result.push_back(segments[0] + "." + segments[1] + "." +
                                     segments[2] + "." + segments[3]);
                }
                return;
            }

            int value = 0;
            for (int end = start; end < static_cast<int>(s.size()) && end < start + 3; ++end) {
                value = value * 10 + (s[end] - '0');
                if (value > 255) {
                    break;
                }
                if (end > start && s[start] == '0') {
                    break; // 多位段不能以 0 开头。
                }
                segments.push_back(s.substr(start, end - start + 1));
                dfs(end + 1);
                segments.pop_back();
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
| 状态定义 | `path` 存数值段 | `segments` 存字符串段 | 减少最后拼接成本 |
| 更新逻辑 | 切段后递归 | 相同 | 主干正确 |
| 边界处理 | 覆盖前导零和值域 | 增加段长和剩余字符剪枝 | 让约束更显式 |
| 复杂度 | 常数级搜索 | 常数级搜索 | 优化清晰度和剪枝 |

## 下一步建议

建议补测 `0000`、`010010`、`101023`，重点观察前导零和剩余段数剪枝。

## 后续练习

1. `131. Palindrome Partitioning` - 对比“任意段数切分”和“固定 4 段切分”。
2. `22. Generate Parentheses` - 对比“切已有字符串”和“生成合法字符串”。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/93.restore-ip-addresses.cpp`
- 新函数名：`restoreIpAddressesOpt`
- 保留用户原实现：是
