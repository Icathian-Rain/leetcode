# 题解点评 - 744. Find Smallest Letter Greater Than Target

## 基本信息

- 日期：2026-05-22
- 主题：二分查找 - 基础区间与插入位置
- 难度：简单
- 本次结果：待提交验证，源码逻辑检查通过
- 对应源码：`src/744.find-smallest-letter-greater-than-target.cpp`
- 资料来源：[LeetCode 中文题目页](https://leetcode.cn/problems/find-smallest-letter-greater-than-target/) + [leetcode.ca 镜像页](https://leetcode.ca/all/744.html) + 本地源码
- 查询日期：2026-05-22

## 用户思路概述

1. `s1` 明确目标是寻找第一个严格大于 `target` 的字符。
2. 使用半开区间 `[l, r)`，初始右边界为 `letters.size()`。
3. 当 `letters[m] <= target` 时，说明当前位置不满足“严格更大”，向右查找。
4. 否则保留中点，继续寻找更靠左的合法字符。
5. 如果最终位置等于 `n`，说明需要按题意回绕到 `letters[0]`。

## 用户解法复杂度

- 时间复杂度：`O(log n)`
- 空间复杂度：`O(1)`
- 复杂度来源：二分查找每轮排除一半字符范围，只维护常数个变量。

## 用户代码注释版

```cpp
class Solution {
public:
    char s1(vector<char>& letters, char target) {
        // 寻找第一个大于 target 的字符。
        int n=letters.size();
        int l=0, r=n;
        while(l<r) {
            int m=l+(r-l)/2;
            if(letters[m] <= target) {
                l=m+1; // 当前字符不够大，答案只可能在右侧。
            } else {
                r=m;   // 当前字符可能是答案，保留它。
            }
        }
        return l==n ? letters[0]: letters[l]; // 超过末尾时回绕。
    }

    char s2(vector<char>& letters, char target) {
        int n=letters.size();
        int m=upper_bound(letters.begin(), letters.end(), target) - letters.begin();
        return m==n ? letters[0]: letters[m];
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 严格大于 | 使用 `<= target` 排除不合法位置。 | 正确区别于大于等于。 | 这个比较符是本题核心。 |
| 回绕边界 | `l == n` 时返回 `letters[0]`。 | 覆盖目标大于等于所有字符的情况。 | 继续把返回边界单独检查。 |
| 库函数选择 | 使用 `upper_bound`。 | 语义正好是第一个大于目标的位置。 | 能和手写版互相验证。 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 手写版和库函数版都准确，回绕边界处理正确。 | 测试用例注释里第一条格式看起来不完整，但不影响提交代码。 | 可以提交，是今天完成质量最好的一题之一。 |
| 推荐最优解 | 保持手写 upper_bound 语义，便于迁移。 | 要小心 `<=` 和 `<` 的差别。 | 适合训练“第一个严格满足”的边界查找。 |

## 最优解法

1. 搜索范围为 `[0, n)`。
2. 如果中点字符小于等于目标，它不能作为答案，左边界右移。
3. 否则中点可能是答案，右边界收缩到中点。
4. 结束后若位置等于 `n`，返回第一个字符；否则返回当前位置字符。

- 最优时间复杂度：`O(log n)`
- 最优空间复杂度：`O(1)`

### 最优解代码

```cpp
class Solution {
public:
    char nextGreatestLetter(vector<char>& letters, char target) {
        int left = 0;
        int right = static_cast<int>(letters.size());

        while (left < right) {
            int middle = left + (right - left) / 2;
            if (letters[middle] <= target) {
                left = middle + 1;
            } else {
                right = middle;
            }
        }

        // 如果所有字母都不大于 target，按题意回绕到第一个字母。
        return left == static_cast<int>(letters.size()) ? letters[0] : letters[left];
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | 半开区间 `[l, r)`。 | 半开区间 `[left, right)`。 | 当前已经正确。 |
| 更新逻辑 | `<= target` 时右移。 | 同样逻辑。 | 继续用比较符表达边界语义。 |
| 边界处理 | `l == n` 时回绕。 | 同样回绕。 | 当前正确。 |
| 复杂度 | `O(log n)` / `O(1)`。 | `O(log n)` / `O(1)`。 | 已达到最优。 |

## 下一步建议

建议把 `35` 和 `744` 放在一起复盘：前者是第一个 `>= target`，后者是第一个 `> target`。二分边界题的差异往往就藏在一个比较符里。

## 后续练习

1. `278. First Bad Version` - 继续练习第一个满足条件的位置。
2. `34. Find First and Last Position of Element in Sorted Array` - 把一个边界扩展成左右两个边界。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/744.find-smallest-letter-greater-than-target.cpp`
- 新函数名：`nextGreatestLetterOpt`
- 保留用户原实现：是
