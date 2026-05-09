# 题解点评 - 20. Valid Parentheses

## 基本信息

- 日期：2026-05-08
- 主题：栈与队列 - 基础栈语义与状态回退
- 难度：简单
- 本次结果：待提交验证，源码逻辑检查通过
- 对应源码：`src/20.valid-parentheses.cpp`
- 资料来源：本地周计划（题号、英文题名和难度已于 2026-05-08 通过 LeetCode GraphQL 校准）+ 本地源码；本次未重新联网校准
- 查询日期：未联网

## 用户思路概述

1. 用 `stack<char>` 保存还没有匹配成功的左括号。
2. 遇到左括号时入栈，表示这个括号等待后续右括号匹配。
3. 遇到右括号时，先判断栈是否为空，再用 `compare` 检查栈顶左括号是否和当前右括号成对。
4. 扫描结束后，如果栈中仍有左括号，说明还有未闭合状态，返回 `false`；否则返回 `true`。

## 用户解法复杂度

- 时间复杂度：`O(n)`
- 空间复杂度：`O(n)`
- 复杂度来源：字符串只扫描一次；最坏情况下所有字符都是左括号，需要全部入栈。

## 用户代码注释版

```cpp
class Solution {
public:
    bool compare(char a, char b) {
        // 判断栈顶左括号和当前右括号是否正好成对。
        if((a == '(' && b == ')') || (a == '[' && b == ']') || (a == '{' && b == '}')) {
            return true;
        } else {
            return false;
        }
    }

    bool isValid(string s) {
        stack<char> st; // 保存尚未匹配的左括号，栈顶就是最近的左括号。
        for(auto ch: s) {
            if(ch == '(' || ch == '[' || ch == '{') {
                st.push(ch);
            } else if(ch == ')' || ch == ']' || ch == '}') {
                if(st.empty()) return false; // 没有左括号可匹配，直接非法。
                if(compare(st.top(), ch) == false) return false;
                st.pop(); // 匹配成功后移除最近的未闭合左括号。
            } else {
                return false; // 本题输入通常只含括号，这个分支是额外防御。
            }
        }
        if(!st.empty()) return false;
        return true;
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 栈语义 | 用栈保存最近未匹配左括号。 | 正确命中本题核心，能够处理嵌套结构。 | 复盘时明确说出“右括号只能匹配最近的左括号”。 |
| 非法状态 | 空栈遇右括号、类型不匹配、结束后栈非空都处理到。 | 正确性覆盖完整。 | 继续保持提前返回，让非法路径短而清楚。 |
| 代码表达 | `compare` 可以工作，但每次传入两个字符判断。 | 逻辑正确，表达略分散。 | 可改成由右括号直接映射所需左括号，判断更集中。 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 正确、直观，边界覆盖完整。 | `compare` 分支略重复，其他字符分支对本题不是必要核心。 | 适合入门栈匹配题。 |
| 推荐最优解 | 把右括号映射到需要的左括号，非法判断集中。 | 本质复杂度相同。 | 适合作为括号匹配模板。 |

## 最优解法

1. 栈中只保存尚未匹配的左括号。
2. 遇到左括号直接入栈。
3. 遇到右括号时，计算它需要匹配的左括号；如果栈空或栈顶不同，立即返回 `false`。
4. 扫描结束后，只有栈为空才说明所有左括号都被匹配。

- 最优时间复杂度：`O(n)`
- 最优空间复杂度：`O(n)`

### 最优解代码

```cpp
class Solution {
    char matchingOpening(char closing) {
        if (closing == ')') return '(';
        if (closing == ']') return '[';
        if (closing == '}') return '{';
        return '\0';
    }

public:
    bool isValid(string s) {
        stack<char> openings;

        for (char ch : s) {
            if (ch == '(' || ch == '[' || ch == '{') {
                openings.push(ch);
                continue;
            }

            char need = matchingOpening(ch);
            // 右括号必须匹配最近的未闭合左括号。
            if (need == '\0' || openings.empty() || openings.top() != need) {
                return false;
            }
            openings.pop();
        }

        return openings.empty();
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | 栈保存未匹配左括号。 | 同样保存未匹配左括号。 | 状态定义已经稳定。 |
| 更新逻辑 | 用 `compare(st.top(), ch)` 判断匹配。 | 由右括号直接得到需要的左括号。 | 判断条件更集中，口述更顺。 |
| 边界处理 | 三类非法状态都覆盖。 | 同样覆盖，并合并右括号非法判断。 | 当前边界意识很好。 |
| 复杂度 | `O(n)` / `O(n)` | `O(n)` / `O(n)` | 已达到最优。 |

## 下一步建议

进入下一题即可。复盘时重点记住：栈里不是“所有历史字符”，而是“仍等待匹配的左括号”。

## 后续练习

1. `921. Minimum Add to Make Parentheses Valid` - 从判断合法迁移到统计缺口。
2. `1249. Minimum Remove to Make Valid Parentheses` - 继续练习记录无法匹配的位置。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/20.valid-parentheses.cpp`
- 新函数名：`isValidOpt`
- 保留用户原实现：是
