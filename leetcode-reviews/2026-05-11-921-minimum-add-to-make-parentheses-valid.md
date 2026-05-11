# 题解点评 - 921. Minimum Add to Make Parentheses Valid

## 基本信息

- 日期：2026-05-11
- 主题：栈与队列 - 括号合法性进阶
- 难度：中等
- 本次结果：待提交验证，源码逻辑检查通过
- 对应源码：`src/921.minimum-add-to-make-valid-parentheses.cpp`
- 资料来源：本地周计划（题号、英文题名和难度已于 2026-05-08 通过 LeetCode GraphQL 校准）+ 本地源码；本次未重新联网校准
- 查询日期：未联网

## 用户思路概述

1. 用 `left` 记录当前还没有被匹配的左括号数量。
2. 用 `ans` 记录为了修复已经遇到的非法右括号，需要补多少个左括号。
3. 遇到 `(` 时，`left++`，表示多了一个等待匹配的左括号。
4. 遇到 `)` 时，如果 `left > 0`，就消耗一个左括号；否则说明这个右括号缺少左括号，需要 `ans++`。
5. 扫描结束后，剩余的 `left` 个左括号都需要补右括号，因此返回 `ans + left`。

## 用户解法复杂度

- 时间复杂度：`O(n)`
- 空间复杂度：`O(1)`
- 复杂度来源：字符串只扫描一次，只维护两个计数变量。

## 用户代码注释版

```cpp
class Solution {
public:
    int minAddToMakeValid(string s) {
        int ans=0;  // 已经确定需要补的左括号数量。
        int left=0; // 尚未匹配的左括号数量。
        for(auto ch: s) {
            if(ch == '(') {
                left++;
            } else {
                if(left > 0) {
                    left--; // 当前右括号匹配一个已有左括号。
                } else {
                    ans++; // 当前右括号缺少左括号，只能新增一个。
                }
            }
        }
        return ans+left; // 剩余左括号都需要补右括号。
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 状态定义 | `left` 表示未匹配左括号，`ans` 表示缺失左括号。 | 建模准确，空间最优。 | 复盘时把两个变量分别命名成“缺左”和“剩左”，语义更直观。 |
| 修复成本 | 右括号无法匹配时立即计入答案，剩余左括号最后计入答案。 | 正确覆盖两类不合法来源。 | 做括号修复题时先判断要补的是左括号、右括号，还是删除位置。 |
| 算法选择 | 不使用栈，只用计数完成。 | 更轻量，符合本题只需要数量的目标。 | 这是本题的最优表达，不需要额外结构。 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 线性时间、常数空间，状态很清楚。 | 变量名 `ans/left` 可进一步语义化。 | 适合只要求最少添加数量的括号题。 |
| 推荐最优解 | 与用户思路一致，只调整命名和分支表达。 | 本质复杂度没有变化。 | 可作为直接提交模板。 |

## 最优解法

1. 维护 `unmatchedLeft` 表示当前还没有匹配的左括号。
2. 维护 `missingLeft` 表示已经遇到多少个无法匹配的右括号。
3. 扫描字符串，左括号增加 `unmatchedLeft`。
4. 右括号优先匹配一个已有左括号；如果没有，则需要新增一个左括号。
5. 最终答案是缺失左括号数量加剩余未匹配左括号数量。

- 最优时间复杂度：`O(n)`
- 最优空间复杂度：`O(1)`

### 最优解代码

```cpp
class Solution {
public:
    int minAddToMakeValid(string s) {
        int missingLeft = 0;
        int unmatchedLeft = 0;

        for (char ch : s) {
            if (ch == '(') {
                ++unmatchedLeft;
            } else if (unmatchedLeft > 0) {
                // 当前右括号优先匹配最近尚未闭合的左括号。
                --unmatchedLeft;
            } else {
                ++missingLeft;
            }
        }

        return missingLeft + unmatchedLeft;
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | `ans` 和 `left`。 | `missingLeft` 和 `unmatchedLeft`。 | 命名更贴近括号修复语义。 |
| 更新逻辑 | 右括号分匹配成功和缺左两类。 | 同样处理。 | 当前逻辑已经稳定。 |
| 边界处理 | 全左、全右、空匹配段都覆盖。 | 同样覆盖。 | 已覆盖关键边界。 |
| 复杂度 | `O(n)` / `O(1)` | `O(n)` / `O(1)` | 已达到最优。 |

## 下一步建议

进入下一题即可。今天要记住一个判断：如果题目只问数量，通常不必保存下标。

## 后续练习

1. `1249. Minimum Remove to Make Valid Parentheses` - 从数量扩展到具体删除哪些位置。
2. `1541. Minimum Insertions to Balance a Parentheses String` - 在规则变化后继续练计数状态。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/921.minimum-add-to-make-parentheses-valid.cpp`
- 新函数名：`minAddToMakeValidOpt`
- 保留用户原实现：是
