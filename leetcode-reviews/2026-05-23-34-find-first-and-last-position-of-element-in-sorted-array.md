# 题解点评 - 34. Find First and Last Position of Element in Sorted Array

## 基本信息

- 日期：2026-05-23
- 主题：二分查找 - 边界定位与近似答案
- 难度：中等
- 本次结果：待提交验证，源码逻辑检查通过
- 对应源码：`src/34.find-first-and-last-position-of-element-in-sorted-array.cpp`
- 资料来源：本地周计划与源码，题号/题名/难度沿用已校准计划；未联网校准
- 查询日期：未联网

## 用户思路概述

1. 写了手写二分版本 `s1`：先找第一个大于等于 `target` 的位置。
2. 如果左边界越界或对应值不是 `target`，说明目标不存在，返回 `{-1, -1}`。
3. 再找第一个大于 `target` 的位置，将它减一作为右边界。
4. 写了标准库版本 `s2`：用 `lower_bound` 和 `upper_bound` 表达同一套边界语义。
5. 公开函数当前调用 `s2`，提交代码简洁且符合最优复杂度。

## 用户解法复杂度

- 时间复杂度：`O(log n)`
- 空间复杂度：`O(1)`
- 复杂度来源：`lower_bound` 和 `upper_bound` 都是在有序数组上进行二分查找。

## 用户代码注释版

> 只在点评文档中展示加注释版本；不要把这些注释写回 `src/*.cpp` 的用户原代码。

```cpp
class Solution {
    vector<int> s1(vector<int>& nums, int target) {
        int n=nums.size();
        int l=0, r=n;
        while(l<r) {
            int m=l+(r-l)/2;
            if(nums[m] >= target) {
                r=m; // 找第一个 >= target 的位置，m 可能是左边界。
            } else {
                l=m+1;
            }
        }

        if(l == n|| nums[l] != target) {
            return {-1, -1}; // lower_bound 没命中，目标不存在。
        }
        int ansL = l;

        l=0, r=n;
        while(l<r) {
            int m=l+(r-l)/2;
            if(nums[m] > target) {
                r=m; // 找第一个 > target 的位置。
            } else {
                l=m+1;
            }
        }

        int ansR = l-1; // 第一个 > target 的前一位就是右边界。
        return {ansL, ansR};
    }

    vector<int> s2(vector<int>& nums, int target) {
        int n=nums.size();
        int ansL=lower_bound(nums.begin(), nums.end(), target)-nums.begin();
        if(ansL == n || nums[ansL]!=target) {
            return {-1, -1};
        }
        int ansR = upper_bound(nums.begin(), nums.end(), target)-nums.begin()-1;
        return {ansL, ansR};
    }
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        return s2(nums, target);
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 左右边界语义 | 能区分第一个 `>= target` 和第一个 `> target` | 正确找到重复元素范围 | 继续把比较符和返回值绑定起来复盘 |
| 不存在处理 | 在左边界处检查越界和命中 | 空数组、目标不存在都能覆盖 | 这是边界题的必要检查，不能省略 |
| 手写与库函数 | 同时保留 `s1` 和 `s2` | 训练和提交都兼顾 | 训练时优先手写，提交时用库函数也可以 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 手写版本语义完整，库函数版本简洁可靠 | `s1/s2` 命名可以更语义化 | 适合所有有序数组重复元素范围查询 |
| 推荐最优解 | 直接用标准库表达边界，注释强调右边界来源 | 需要熟悉 `upper_bound` 返回的是后一位 | 适合 LeetCode 提交和复盘边界语义 |

## 最优解法

1. 用 `lower_bound` 找到第一个不小于 `target` 的位置。
2. 如果该位置越界或值不是 `target`，说明目标不存在。
3. 用 `upper_bound` 找到第一个大于 `target` 的位置。
4. 右边界是 `upper_bound` 返回位置的前一位。

- 最优时间复杂度：`O(log n)`
- 最优空间复杂度：`O(1)`

### 最优解代码

```cpp
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        auto first = lower_bound(nums.begin(), nums.end(), target);
        if (first == nums.end() || *first != target) {
            return {-1, -1};
        }

        // upper_bound 指向第一个大于 target 的位置，左移一格就是最后一次出现。
        auto afterLast = upper_bound(nums.begin(), nums.end(), target);
        return {
            static_cast<int>(first - nums.begin()),
            static_cast<int>(afterLast - nums.begin() - 1)
        };
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | `s1/s2` 表示两个版本 | 直接用 `first/afterLast` 命名边界 | 辅助函数名可改成 `searchRangeManual` 和 `searchRangeLibrary` |
| 更新逻辑 | 手写二分与库函数都正确 | 库函数版本更短 | 保持能手写的能力 |
| 边界处理 | 空数组和不存在都覆盖 | 相同 | 继续强化越界先于取值 |
| 复杂度 | `O(log n)` / `O(1)` | `O(log n)` / `O(1)` | 已达最优 |

## 下一步建议

进入下一题。复盘时建议把 `lower_bound`、`upper_bound`、`第一个 true` 三者统一到一张比较符表里。

## 后续练习

1. `658. Find K Closest Elements` - 在有序数组中继续处理连续答案段的边界。
2. `981. Time Based Key-Value Store` - 把右边界查询迁移到设计题的时间戳数组。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/34.find-first-and-last-position-of-element-in-sorted-array.cpp`
- 新函数名：`searchRangeOpt`
- 保留用户原实现：是
