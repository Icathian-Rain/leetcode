# 题解点评 - 128. Longest Consecutive Sequence

## 基本信息

- 日期：2026-04-29
- 主题：数组与哈希
- 难度：中等
- 本次结果：已完成；本地语法验证通过
- 对应源码：`src/128.longest-consecutive-sequence.cpp`
- 资料来源：LeetCode 官方题目页（https://leetcode.com/problems/longest-consecutive-sequence/）+ 本地源码
- 查询日期：2026-04-29

## 用户思路概述

你先把所有数字放入 `unordered_set`，然后只从“没有前驱”的数字开始向后扩展连续序列。也就是说，如果 `num - 1` 存在，就跳过当前数字；只有 `num` 是某段连续序列的起点时，才一路检查 `num + 1`、`num + 2`。

这是本题最关键的集合边界思路：每个连续段只从起点扩展一次。

## 主要问题

- 没有阻塞级问题：当前写法符合本题期望的平均 `O(n)` 解法。
- 性能细节：可以在建表前 `reserve`，减少大输入下 `unordered_set` 的 rehash 次数；这不是正确性问题。
- 边界表达：`num - 1`、`cur++` 在 LeetCode 当前数值范围内安全，但如果写成更通用的库代码，可以用更宽的整数或先判断边界。

## 做得好的地方

- 正确处理了重复元素：先入集合，重复值不会造成重复计数。
- 只从序列起点扩展，避免了从每个元素都向后扫导致的退化。
- 空数组单独返回 `0`，避免了 `ans = 1` 在空输入上的误判。

## 最优解法

推荐解法与当前写法一致。核心是不排序，而是用哈希集合回答“某个值是否存在”。遍历每个不同数字时，只有当 `num - 1` 不存在，`num` 才是一段连续序列的起点；从起点向后扩展得到该段长度。因为每个数字最多被某个起点扩展经过一次，平均时间复杂度是线性的。

- 时间复杂度：`O(n)`，哈希操作按平均 `O(1)` 计算
- 空间复杂度：`O(n)`

## 最优解代码

```cpp
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> seen;
        seen.reserve(nums.size() * 2);
        for (int num : nums) {
            seen.insert(num);
        }

        int best = 0;
        for (int num : seen) {
            if (seen.find(num - 1) != seen.end()) {
                continue;
            }

            int length = 1;
            int current = num + 1;
            while (seen.find(current) != seen.end()) {
                ++length;
                ++current;
            }

            best = max(best, length);
        }

        return best;
    }
};
```

## 对比与改进方向

你已经抓住了“只从边界出发”的关键。这个模式可以迁移到很多集合题：不要问“每个点能扩多远”，而是先定义什么点有资格成为一段结构的起点。

## 下一步建议

进入下一题即可。口头复盘时建议强调：`num - 1` 不存在是本题的去重扫描条件，它决定了为什么整体不是 `O(n^2)`。

## 后续练习

1. `594. Longest Harmonious Subsequence` - 继续练习用集合 / 频次表识别相邻值关系。
2. `352. Data Stream as Disjoint Intervals` - 把连续段边界维护升级成动态数据结构设计。
