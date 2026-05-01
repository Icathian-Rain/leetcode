# 题解点评 - 125. Valid Palindrome

## 基本信息

- 日期：2026-05-01
- 主题：双指针与滑动窗口 - 相向双指针与移动依据
- 难度：简单
- 本次结果：通过（用户反馈已完成，源码逻辑检查通过）
- 对应源码：`src/125.valid-palindrome.cpp`
- 资料来源：LeetCode 中文题页（题号和题名）+ 本地计划；LeetCode 官方英文页访问受限
- 查询日期：2026-05-01

## 用户思路概述

你使用左右两个指针从字符串两端向中间扫描。每一轮先跳过非字母数字字符，再把两侧字符统一转成小写比较；一旦不同就返回 `false`，全部匹配后返回 `true`。

这正是本题最直接的相向双指针做法：只比较有效字符，并且每次比较后缩小未确认区间。

## 主要问题

- 整体算法正确，没有阻塞级问题，时间和空间都达到最优。
- 当前 `for` 循环头里有 `i++, j--`，循环体内部又会移动 `i` 和 `j` 跳过无效字符。逻辑仍然正确，但移动责任分散，复盘时容易误以为指针每轮固定移动一次。更推荐使用 `while (left < right)`，把所有移动都写在循环体里。
- `isNumber`、`isLetter`、`lower` 都手写 ASCII 判断，符合题目要求；如果使用标准库函数，要注意 `isalnum` / `tolower` 需要把字符转换为 `unsigned char`，否则某些非 ASCII 输入下有未定义行为风险。本题可以继续保留手写判断。

## 做得好的地方

- 先跳过无效字符再比较，避免把标点、空格纳入回文判断。
- `lower` 只转换大写字母，不会错误修改数字。
- 能覆盖空格字符串、大小写混合、两端标点等核心边界。

## 最优解法

推荐最优解仍是相向双指针。关键不变量是：`left` 左侧和 `right` 右侧的有效字符已经完成匹配；当前只需要在 `[left, right]` 中继续寻找下一对有效字符。若这对字符忽略大小写后不同，则整串不可能是回文。

- 时间复杂度：`O(n)`
- 空间复杂度：`O(1)`

## 最优解代码

```cpp
class Solution {
    bool isAlphaNumeric(char ch) {
        return ('0' <= ch && ch <= '9') ||
               ('a' <= ch && ch <= 'z') ||
               ('A' <= ch && ch <= 'Z');
    }

    char toLowerAscii(char ch) {
        if ('A' <= ch && ch <= 'Z') {
            return static_cast<char>(ch - 'A' + 'a');
        }
        return ch;
    }

public:
    bool isPalindrome(string s) {
        int left = 0;
        int right = static_cast<int>(s.size()) - 1;

        while (left < right) {
            while (left < right && !isAlphaNumeric(s[left])) {
                ++left;
            }
            while (left < right && !isAlphaNumeric(s[right])) {
                --right;
            }
            if (toLowerAscii(s[left]) != toLowerAscii(s[right])) {
                return false;
            }
            ++left;
            --right;
        }

        return true;
    }
};
```

## 对比与改进方向

你的解法和推荐最优解本质一致，主要差距是控制流表达。双指针题建议把“跳过无效状态、比较当前状态、收缩边界”三个动作集中在同一个 `while` 循环中，这样更容易说清楚指针移动依据。

## 下一步建议

进入下一题即可。本题可作为“相向指针 + 过滤无效元素”的入门模板。

## 后续练习

1. `680. Valid Palindrome II` - 在相向双指针基础上增加一次删除机会，训练分支判断。
2. `345. Reverse Vowels of a String` - 同样需要两端扫描和跳过非目标字符。
