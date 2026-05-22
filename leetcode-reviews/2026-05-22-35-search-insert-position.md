# 题解点评 - 35. Search Insert Position

## 基本信息

- 日期：2026-05-22
- 主题：二分查找 - 基础区间与插入位置
- 难度：简单
- 本次结果：待提交验证，源码逻辑检查通过
- 对应源码：`src/35.search-insert-position.cpp`
- 资料来源：[LeetCode 中文题目页](https://leetcode.cn/problems/search-insert-position/) + [leetcode.ca 镜像页](https://leetcode.ca/all/35.html) + 本地源码
- 查询日期：2026-05-22

## 用户思路概述

1. `s1` 明确目标是找第一个大于等于 `target` 的位置。
2. 使用半开区间 `[l, r)`，初始 `r = nums.size()`，允许答案落在数组末尾之后。
3. 若 `nums[m] < target`，说明插入位置一定在右侧。
4. 否则保留 `m`，继续在左侧查找更靠前的合法位置。
5. `s2` 使用 `lower_bound` 直接返回同样语义的位置。

## 用户解法复杂度

- 时间复杂度：`O(log n)`
- 空间复杂度：`O(1)`
- 复杂度来源：每次比较后都排除一半候选插入位置。

## 用户代码注释版

```cpp
class Solution {
public:
    int s1(vector<int>& nums, int target) {
        // 找到第一个大于等于 target 的位置。
        int n=nums.size();
        int l=0, r=n;
        while(l<r) {
            int m=l+(r-l)/2;
            if(nums[m] < target) {
                l = m+1;
            } else {
                r = m; // m 可能就是答案，所以不能写成 m - 1。
            }
        }
        return l;
    }

    int s2(vector<int>& nums, int target) {
        return lower_bound(nums.begin(), nums.end(), target)-nums.begin();
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 边界语义 | 已经抓住“第一个大于等于”的语义。 | 正好对应插入位置。 | 这是本题最重要的理解点。 |
| 答案可在末尾 | 初始 `r = n`。 | 能正确返回 `nums.size()`。 | 继续保留半开区间模板。 |
| 库函数语义 | `lower_bound` 使用正确。 | 简洁稳定。 | 训练阶段仍建议先写手动版。 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 手写版和库函数版都准确表达 lower_bound。 | 公开函数当前只调用库函数，边界训练量偏少。 | 可以提交，建议复盘手写版。 |
| 推荐最优解 | 保持半开区间，直接返回左边界。 | 需要理解 `right = middle` 的保留含义。 | 适合作为“找第一个满足条件”的模板。 |

## 最优解法

1. 搜索范围设置为 `[0, n)`，因为插入位置可能等于 `n`。
2. 当中点值小于目标时，左侧和中点都不可能是答案。
3. 否则中点可能是答案，保留中点并继续向左收缩。
4. 循环结束时 `left == right`，就是第一个大于等于 `target` 的位置。

- 最优时间复杂度：`O(log n)`
- 最优空间复杂度：`O(1)`

### 最优解代码

```cpp
class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int left = 0;
        int right = static_cast<int>(nums.size());

        while (left < right) {
            int middle = left + (right - left) / 2;
            if (nums[middle] < target) {
                left = middle + 1;
            } else {
                right = middle;
            }
        }

        return left; // 第一个大于等于 target 的位置，也是插入位置。
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | 半开区间 `[l, r)`。 | 半开区间 `[left, right)`。 | 当前已经正确。 |
| 更新逻辑 | 小于目标时丢左侧，否则保留中点。 | 同样逻辑。 | 继续理解“保留可能答案”。 |
| 边界处理 | 可返回 `0` 或 `n`。 | 同样覆盖。 | 当前正确。 |
| 复杂度 | `O(log n)` / `O(1)`。 | `O(log n)` / `O(1)`。 | 已达到最优。 |

## 下一步建议

建议把这题作为第 5 周的核心模板记住：只要题目问“第一个大于等于某值的位置”，就先想到这个半开区间框架。

## 后续练习

1. `704. Binary Search` - 对比“找具体值”和“找边界”的差异。
2. `278. First Bad Version` - 把 lower_bound 语义迁移到状态变化题。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/35.search-insert-position.cpp`
- 新函数名：`searchInsertOpt`
- 保留用户原实现：是
