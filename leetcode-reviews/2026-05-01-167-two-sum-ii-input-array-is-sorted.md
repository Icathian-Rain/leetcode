# 题解点评 - 167. Two Sum II - Input Array Is Sorted

## 基本信息

- 日期：2026-05-01
- 主题：双指针与滑动窗口 - 相向双指针与移动依据
- 难度：中等
- 本次结果：通过（用户反馈已完成，源码逻辑检查通过）
- 对应源码：`src/167.two-sum-ii-input-array-is-sorted.cpp`
- 资料来源：LeetCode 中文题页（题号和题名）+ 本地计划；LeetCode 官方英文页访问受限
- 查询日期：2026-05-01

## 用户思路概述

你利用数组已经非递减排序的条件，把指针放在数组两端。若当前和小于 `target`，说明左端数太小，需要右移左指针；若当前和大于 `target`，说明右端数太大，需要左移右指针；相等时返回 1-indexed 下标。

这是本题最标准的有序数组相向双指针解法。

## 主要问题

- 整体算法正确，没有阻塞级问题，复杂度也达到最优。
- `numbers[i] + numbers[j]` 在代码里计算了两次。当前题目约束下通常不会成为性能问题，但提取成 `sum` 能让移动依据更清楚。
- 如果题目约束允许非常大的整数，加法可能溢出 `int`。LeetCode 当前约束一般安全，但面试中可以用 `long long sum` 作为稳健习惯。

## 做得好的地方

- 明确使用排序单调性决定移动方向，没有退回哈希表做法。
- 返回 `{i + 1, j + 1}`，正确处理了题目要求的 1-indexed 下标。
- 循环条件 `i < j` 保证不会重复使用同一个元素。

## 最优解法

推荐最优解是相向双指针。关键不变量是：当 `numbers[left] + numbers[right] < target` 时，固定 `left` 与任何不超过 `right` 的右侧元素相加都不会更大到足以命中，所以可以安全丢弃 `left`；反之当和过大时，可以安全丢弃 `right`。

- 时间复杂度：`O(n)`
- 空间复杂度：`O(1)`

## 最优解代码

```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int left = 0;
        int right = static_cast<int>(numbers.size()) - 1;

        while (left < right) {
            long long sum = static_cast<long long>(numbers[left]) + numbers[right];
            if (sum == target) {
                return {left + 1, right + 1};
            }
            if (sum < target) {
                ++left;
            } else {
                --right;
            }
        }

        return {};
    }
};
```

## 对比与改进方向

你的实现已经掌握了核心模式。后续写有序数组双指针时，重点不是记住代码，而是能先说明“为什么当前指针可以被排除”。这道题中，排除依据完全来自数组的排序单调性。

## 下一步建议

进入下一题即可。后续可以把这个模式迁移到 `3Sum`：先固定一个数，再对剩余有序区间使用同样的左右指针。

## 后续练习

1. `15. 3Sum` - 把两数之和的相向双指针扩展到组合搜索。
2. `633. Sum of Square Numbers` - 同样依赖有序值域上的左右指针收缩。
