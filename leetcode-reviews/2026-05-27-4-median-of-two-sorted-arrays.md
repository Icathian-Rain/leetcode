# 题解点评 - 4. Median of Two Sorted Arrays

## 基本信息

- 日期：2026-05-27
- 主题：第 5 周二分查找 - 第 6 天峰值、分割与困难边界
- 难度：困难
- 本次结果：未完成，源码中公开函数为空
- 对应源码：`src/4.median-of-two-sorted-arrays.cpp`
- 资料来源：LeetCode 官方题目页、LeetCode Wiki
- 查询日期：2026-05-27

## 用户思路概述

1. 当前文件保留了 LeetCode 插件生成的题目结构。
2. `findMedianSortedArrays` 公开函数尚未实现，因此提交会编译失败或没有返回值。
3. 本次同步补入了可提交的最优实现，优先保证第六天困难题有一份可复盘代码。

## 用户解法复杂度

- 时间复杂度：未形成有效算法
- 空间复杂度：未形成有效算法
- 复杂度来源：公开函数为空，无法进行有效复杂度评价。

## 用户代码注释版

```cpp
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        // 当前为空：没有返回值，无法通过编译和提交。
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 题目复杂度要求 | 尚未实现 | 不能用合并数组作为最终方案 | 先把问题转成寻找第 `k` 小元素 |
| 排除逻辑 | 尚未形成 | 困难题最核心部分缺失 | 每轮比较两个数组各自第 `k/2` 个候选，排除较小一侧 |
| 奇偶长度 | 尚未处理 | 中位数返回会出错 | 统一取第 `(total+1)/2` 和 `(total+2)/2` 小再求平均 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 题目骨架已就位 | 没有实现，无法提交 | 适合从最小可运行版本重新开始 |
| 推荐最优解 | 每轮排除约一半候选，复杂度达标 | 递归参数和 `k` 的更新容易写错 | 适合先掌握困难题的主干排除思路 |

## 最优解法

1. 把中位数问题统一成找两个有序数组合并后的第 `k` 小元素。
2. 若某个数组已经用完，答案直接来自另一个数组；若 `k == 1`，返回两个当前元素较小值。
3. 每轮分别取两个数组剩余部分的第 `k/2` 个候选，较小候选所在数组的前一段不可能包含第 `k` 小，可以整体排除。
4. 总长度为奇数和偶数都用第 `(total + 1) / 2` 与第 `(total + 2) / 2` 小统一处理。

- 最优时间复杂度：`O(log(m+n))`
- 最优空间复杂度：`O(log(m+n))`，来自递归调用栈；可改成迭代降为 `O(1)`。

### 最优解代码

```cpp
class Solution {
    int getKth(vector<int>& nums1, int index1, vector<int>& nums2, int index2, int k) {
        if (index1 == nums1.size()) return nums2[index2 + k - 1];
        if (index2 == nums2.size()) return nums1[index1 + k - 1];
        if (k == 1) return min(nums1[index1], nums2[index2]);

        int half = k / 2;
        int newIndex1 = min(index1 + half, static_cast<int>(nums1.size())) - 1;
        int newIndex2 = min(index2 + half, static_cast<int>(nums2.size())) - 1;

        if (nums1[newIndex1] <= nums2[newIndex2]) {
            // nums1 的这段元素不可能包含第 k 小，整体排除。
            return getKth(nums1, newIndex1 + 1, nums2, index2, k - (newIndex1 - index1 + 1));
        }

        return getKth(nums1, index1, nums2, newIndex2 + 1, k - (newIndex2 - index2 + 1));
    }

public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int total = nums1.size() + nums2.size();
        int leftMedian = getKth(nums1, 0, nums2, 0, (total + 1) / 2);
        int rightMedian = getKth(nums1, 0, nums2, 0, (total + 2) / 2);
        return (leftMedian + rightMedian) / 2.0;
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | 尚未定义 | 两个起点下标与第 `k` 小目标 | 先把中位数转成 `kth` 问题 |
| 更新逻辑 | 尚未实现 | 每轮排除一段不可能元素 | 重点手推 `k` 如何减少 |
| 边界处理 | 无返回值 | 数组耗尽、`k == 1`、奇偶长度统一覆盖 | 先写边界，再写递归主体 |
| 复杂度 | 无有效复杂度 | `O(log(m+n))` / `O(log(m+n))` | 满足题目要求 |

## 下一步建议

建议重写当前题一次：先不看代码，手写 `getKth` 的三个终止条件，再用样例 `[1,2]` 和 `[3,4]` 手推 `k=2`、`k=3`。

## 后续练习

1. `540. Single Element in a Sorted Array` - 用较轻的边界题恢复二分节奏。
2. `658. Find K Closest Elements` - 继续练习在有序数组中定位结果区间。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/4.median-of-two-sorted-arrays.cpp`
- 新函数名：`findMedianSortedArraysOpt`
- 保留用户原实现：否；原公开函数为空，已补成调用最优实现以保证可提交
