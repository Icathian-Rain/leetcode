# 题解点评 - 394. Decode String

## 基本信息

- 日期：2026-05-10
- 主题：栈与队列 - 表达式、路径与嵌套结构
- 难度：中等
- 本次结果：待提交验证，源码逻辑检查通过
- 对应源码：`src/394.decode-string.cpp`
- 资料来源：本地周计划（题号、英文题名和难度已于 2026-05-08 通过 LeetCode GraphQL 校准）+ 本地源码；本次未重新联网校准
- 查询日期：未联网

## 用户思路概述

1. 用 `ptr` 扫描字符串，用 `vector<string> stk` 保存数字、左括号、字母片段和已经展开的子串。
2. 遇到连续数字时，通过 `getDigits` 取出完整数字字符串并入栈。
3. 遇到字母或 `[` 时，把它作为字符串入栈。
4. 遇到 `]` 时，持续弹出直到遇到 `[`，把弹出的内容反转后拼成当前括号内的子串。
5. 再弹出重复次数，把子串重复对应次数后压回栈，作为外层上下文的一部分。
6. 扫描结束后，把栈中所有片段拼接成答案。

## 用户解法复杂度

- 时间复杂度：`O(L)`
- 空间复杂度：`O(L)`
- 复杂度来源：`L` 表示最终解码字符串长度量级；每层展开都需要构造实际输出片段，栈保存尚未完成的上下文和中间字符串。

## 用户代码注释版

```cpp
class Solution {
public:
    string getDigits(string& s, int& ptr) {
        string res = "";
        while(ptr < s.size() && isdigit(s[ptr])) {
            res.push_back(s[ptr]);
            ptr++;
        }
        return res;
    }

    string getString(vector<string>& v) {
        string res = "";
        for(auto str: v) {
            res += str;
        }
        return res;
    }

    string decodeString(string s) {
        int n=s.size();
        vector<string> stk; // 同时保存数字、"["、字母片段和已展开片段。
        int ptr = 0;
        while(ptr < n) {
            char ch = s[ptr];
            if(isdigit(ch)) {
                string digits = getDigits(s, ptr);
                stk.push_back(digits);
            } else if(isalpha(ch) || ch == '[') {
                stk.push_back(string(1, ch));
                ptr++;
            } else {
                ptr++; // 跳过 ']'

                vector<string> sub;
                while(stk.back() != "[") {
                    sub.push_back(stk.back());
                    stk.pop_back();
                }
                stk.pop_back(); // 弹出 '['
                reverse(sub.begin(), sub.end());
                string tmp = getString(sub); // 当前括号内的字符串。

                int times = stoi(stk.back());
                stk.pop_back();

                string ans="";
                while(times--) ans+=tmp; // 展开当前层。
                stk.push_back(ans); // 展开结果作为外层的一个片段。
            }
        }

        return getString(stk);
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 嵌套上下文 | 能在遇到 `]` 时回收到最近一层 `[` 并展开。 | 正确抓住嵌套结构的后进先出性质。 | 复盘时说清每个 `]` 只结算最近未闭合的一层。 |
| 多位数字 | `getDigits` 能读取完整数字。 | 能处理 `12[a]` 这类输入。 | 推荐直接用整数累积，避免数字字符串再转换。 |
| 状态类型 | 同一个 `vector<string>` 同时保存多种语义。 | 正确但复盘成本较高。 | 可拆成重复次数栈和前缀字符串栈，状态更清楚。 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 能正确处理嵌套、多位数字和普通前后缀。 | 栈内元素语义混杂，需要反转子片段。 | 可通过本题，适合理解“遇到右括号结算最近一层”。 |
| 推荐最优解 | 用两个栈分别保存次数和外层前缀，当前层字符串单独维护。 | 需要更清楚地管理进入和退出括号时的状态切换。 | 更适合沉淀成嵌套解析模板。 |

## 最优解法

1. 用 `repeat` 累积当前数字，用 `current` 保存当前层正在构造的字符串。
2. 遇到 `[` 时，把当前重复次数和当前层前缀分别入栈，然后清空 `repeat` 和 `current`，进入内层。
3. 遇到字母时加入 `current`。
4. 遇到 `]` 时，弹出重复次数和外层前缀，把当前层字符串展开后接回外层前缀。
5. 扫描结束后，`current` 就是完整解码结果。

- 最优时间复杂度：`O(L)`
- 最优空间复杂度：`O(L)`

### 最优解代码

```cpp
class Solution {
public:
    string decodeString(string s) {
        stack<int> repeatStack;
        stack<string> prefixStack;
        string current;
        int repeat = 0;

        for (char ch : s) {
            if (isdigit(ch)) {
                repeat = repeat * 10 + (ch - '0');
            } else if (ch == '[') {
                repeatStack.push(repeat);
                prefixStack.push(current);
                repeat = 0;
                current.clear();
            } else if (ch == ']') {
                int times = repeatStack.top();
                repeatStack.pop();
                string prefix = prefixStack.top();
                prefixStack.pop();

                string expanded;
                while (times--) {
                    expanded += current;
                }
                // 闭合一层括号后，恢复外层前缀并接上当前层展开结果。
                current = prefix + expanded;
            } else {
                current.push_back(ch);
            }
        }

        return current;
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | 单一字符串栈混合保存数字、括号和片段。 | 次数栈保存重复次数，前缀栈保存外层字符串。 | 拆分状态语义，降低嵌套题调试难度。 |
| 更新逻辑 | 遇 `]` 后弹到 `[`，反转片段再展开。 | 遇 `[` 保存上下文，遇 `]` 恢复上下文。 | 推荐把进入/退出一层上下文写成对称操作。 |
| 边界处理 | 多位数字、嵌套和普通前后缀都覆盖。 | 同样覆盖。 | 当前正确性基础很好。 |
| 复杂度 | `O(L)` / `O(L)` | `O(L)` / `O(L)` | 已达到最优量级。 |

## 下一步建议

建议重写一次双栈版本。你当前方案已经正确，重写的价值主要是训练“当前层状态”和“外层上下文”分离。

## 后续练习

1. `726. Number of Atoms` - 更复杂的嵌套解析和计数恢复。
2. `856. Score of Parentheses` - 继续练遇到闭合边界时结算最近一层。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/394.decode-string.cpp`
- 新函数名：`decodeStringOpt`
- 保留用户原实现：是
