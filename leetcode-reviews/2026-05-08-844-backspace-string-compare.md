# 题解点评 - 844. Backspace String Compare

## 基本信息

- 日期：2026-05-08
- 主题：栈与队列 - 基础栈语义与状态回退
- 难度：简单
- 本次结果：待提交验证，源码逻辑检查通过
- 对应源码：`src/844.backspace-string-compare.cpp`
- 资料来源：本地周计划（题号、英文题名和难度已于 2026-05-08 通过 LeetCode GraphQL 校准）+ 本地源码；本次未重新联网校准
- 查询日期：未联网

## 用户思路概述

1. 分别处理 `s` 和 `t`，用 `fast` 扫描原字符串，用 `slow` 表示处理后字符串的写入位置。
2. 遇到普通字符时，把它写到 `slow` 位置并右移 `slow`。
3. 遇到 `#` 时，如果 `slow > 0`，就把 `slow` 左移一位，相当于删除上一个有效字符。
4. 两个字符串处理完后，先比较有效长度，再逐位比较有效前缀内容。

## 用户解法复杂度

- 时间复杂度：`O(n + m)`
- 空间复杂度：`O(1)`，不计字符串参数自身
- 复杂度来源：两个字符串各扫描一次，并在原字符串对象上覆盖写入有效前缀。

## 用户代码注释版

```cpp
class Solution {
public:
    bool backspaceCompare(string s, string t) {
        int fast=0, slow=0;
        int len1=s.length();
        for(;fast<len1; fast++) {
            if(s[fast] == '#') {
                if(slow > 0) {
                    slow--; // 删除当前有效前缀的最后一个字符。
                }
            } else {
                s[slow] = s[fast]; // 把普通字符写入有效前缀。
                slow++;
            }
        }
        int slen = slow;

        fast=0, slow=0;
        int len2=t.length();
        for(;fast<len2; fast++) {
            if(t[fast] == '#') {
                if(slow > 0) {
                    slow--;
                }
            } else {
                t[slow] = t[fast];
                slow++;
            }
        }
        int tlen=slow;

        if(slen != tlen) return false;
        for(int i=0; i<slen; i++) {
            if(s[i] != t[i]) {
                return false;
            }
        }
        return true;
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 回退语义 | 用 `slow--` 表达退格删除上一个有效字符。 | 建模准确，比显式栈更省空间。 | 复盘时说明有效内容只在 `[0, slow)`。 |
| 边界处理 | 连续 `#` 或开头 `#` 通过 `slow > 0` 稳定处理。 | 能覆盖关键边界。 | 保持这种“不能再退就不退”的判断。 |
| 最优取舍 | 当前会重写参数副本，再比较有效前缀。 | 已是线性且常数额外空间，但还可以不构造结果。 | 可学习从右向左跳过被删除字符的双指针版本。 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 原地构造有效前缀，逻辑清楚，空间常数。 | 需要分别重写两个字符串并再比较一遍。 | 适合训练快慢指针式回退。 |
| 推荐最优解 | 从右向左直接比较下一个有效字符，不构造结果。 | 推理略复杂，需要维护跳过计数。 | 适合面试中展示 `O(1)` 空间且不修改内容的写法。 |

## 最优解法

1. 从两个字符串末尾开始比较，因为退格只会影响它左边的字符。
2. 对每个字符串维护一个 `skip` 计数：遇到 `#` 增加待跳过数量，遇到普通字符且 `skip > 0` 时跳过它。
3. 每轮找到两个字符串当前真正有效的字符下标。
4. 如果一边已经没有有效字符，另一边还有，则不相等；如果两个有效字符不同，也不相等。
5. 两边都比较完后返回 `true`。

- 最优时间复杂度：`O(n + m)`
- 最优空间复杂度：`O(1)`

### 最优解代码

```cpp
class Solution {
    int nextValidIndex(const string& text, int index) {
        int skip = 0;
        while (index >= 0) {
            if (text[index] == '#') {
                ++skip;
            } else if (skip > 0) {
                --skip;
            } else {
                break;
            }
            --index;
        }
        return index;
    }

public:
    bool backspaceCompare(string s, string t) {
        int left = (int)s.size() - 1;
        int right = (int)t.size() - 1;

        while (left >= 0 || right >= 0) {
            left = nextValidIndex(s, left);
            right = nextValidIndex(t, right);

            if (left < 0 || right < 0) {
                return left == right;
            }
            if (s[left] != t[right]) {
                return false;
            }

            --left;
            --right;
        }

        return true;
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | `slow` 表示有效前缀长度。 | `skip` 表示还要跳过多少个左侧字符。 | 两种状态都有效，后者不需要构造结果。 |
| 更新逻辑 | 正向扫描并覆盖有效前缀。 | 反向扫描并寻找下一个有效字符。 | 掌握两种方向，有助于处理不可修改输入。 |
| 边界处理 | 开头退格、连续退格稳定。 | 同样稳定处理字符耗尽。 | 当前边界意识达标。 |
| 复杂度 | `O(n+m)` / `O(1)` | `O(n+m)` / `O(1)` | 复杂度相同，推荐解主要提升迁移面。 |

## 下一步建议

建议补一组边界测试：`"####"` vs `""`、`"bxj##tw"` vs `"bxo#j##tw"`。之后可以进入第 2 天结构模拟题。

## 后续练习

1. `1047. Remove All Adjacent Duplicates In String` - 继续练字符串中的最近状态回退。
2. `1209. Remove All Adjacent Duplicates in String II` - 把回退扩展到带计数的成组删除。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/844.backspace-string-compare.cpp`
- 新函数名：`backspaceCompareOpt`
- 保留用户原实现：是
