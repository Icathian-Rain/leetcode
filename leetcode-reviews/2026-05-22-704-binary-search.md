# 题解点评 - 704. Binary Search

## 基本信息

- 日期：2026-05-22
- 主题：二分查找 - 基础区间与插入位置
- 难度：简单
- 本次结果：待提交验证，源码逻辑检查通过
- 对应源码：`src/704.binary-search.cpp`
- 资料来源：[LeetCode 中文题目页](https://leetcode.cn/problems/binary-search/) + [leetcode.ca 镜像页](https://leetcode.ca/all/704.html) + 本地源码
- 查询日期：2026-05-22

## 用户思路概述

1. `s1` 使用半开区间 `[l, r)`，初始范围为整个数组。
2. 每轮计算 `m = l + (r - l) / 2`，避免直接相加带来的溢出风险。
3. 如果 `nums[m] == target`，直接返回下标。
4. 如果中点值小于目标，丢弃左侧和中点；否则丢弃右侧。
5. `s2` 直接使用 `lower_bound` 找到第一个大于等于 `target` 的位置，再检查是否真正命中。

## 用户解法复杂度

- 时间复杂度：`O(log n)`
- 空间复杂度：`O(1)`
- 复杂度来源：每次循环都排除约一半搜索范围，只维护常数个下标变量。

## 用户代码注释版

```cpp
class Solution {
public:
    int s1(vector<int>& nums, int target) {
        int n=nums.size();
        int l=0, r=n; // 半开区间 [l, r)。
        while(l<r) {
            int m=l+(r-l)/2;
            if(nums[m] == target) {
                return m;
            } else if(nums[m] < target) {
                l = m+1; // target 只可能在 m 右侧。
            } else {
                r = m;   // target 只可能在 m 左侧，m 不保留。
            }
        }
        return -1;
    }

    int s2(vector<int>& nums, int target) {
        int n=nums.size();
        int m = lower_bound(nums.begin(), nums.end(), target) - nums.begin();
        if(m == n || nums[m] != target) {
            return -1;
        }
        return m;
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 区间定义 | 能正确使用半开区间 `[l, r)`。 | 不会漏掉边界元素。 | 继续在注释里写清 `r` 是否可取。 |
| 命中返回 | 找到目标时直接返回。 | 符合本题“任意目标下标”的要求。 | 这是基础查找题最直接的写法。 |
| 库函数迁移 | 能用 `lower_bound` 简化代码。 | 代码短，但训练时容易跳过边界推理。 | 建议先手写模板，再用库函数核对语义。 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 半开区间和库函数版本都正确，复杂度最优。 | 公开提交当前走库函数，训练二分边界时手感会少一点。 | 可以提交，建议复盘 `s1`。 |
| 推荐最优解 | 使用闭区间模板，命中逻辑直观。 | 要注意 `left <= right` 和 `right = middle - 1` 配套。 | 适合作为“查找具体值”的基础模板。 |

## 最优解法

1. 令搜索范围为闭区间 `[left, right]`。
2. 每轮比较 `nums[middle]` 和 `target`。
3. 命中则返回中点；偏小则收缩左边界，偏大则收缩右边界。
4. 当 `left > right` 时，区间已经为空，返回 `-1`。

- 最优时间复杂度：`O(log n)`
- 最优空间复杂度：`O(1)`

### 最优解代码

```cpp
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left = 0;
        int right = static_cast<int>(nums.size()) - 1;

        while (left <= right) {
            int middle = left + (right - left) / 2;
            if (nums[middle] == target) {
                return middle;
            }
            if (nums[middle] < target) {
                left = middle + 1;
            } else {
                right = middle - 1;
            }
        }

        return -1; // 闭区间被排空，说明目标不存在。
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | 半开区间 `[l, r)` 或库函数边界。 | 闭区间 `[left, right]`。 | 两套都可以，关键是自洽。 |
| 更新逻辑 | `l = m + 1` / `r = m`。 | `left = middle + 1` / `right = middle - 1`。 | 根据区间定义配套更新端点。 |
| 边界处理 | 未命中返回 `-1`。 | 区间为空后返回 `-1`。 | 当前正确。 |
| 复杂度 | `O(log n)` / `O(1)`。 | `O(log n)` / `O(1)`。 | 已达到最优。 |

## 下一步建议

建议把 `s1` 的半开区间版本默写一遍，再对照闭区间版本，明确两者的循环条件和右边界更新差异。

## 后续练习

1. `35. Search Insert Position` - 把“查找命中”推进到“找插入边界”。
2. `34. Find First and Last Position of Element in Sorted Array` - 继续练习重复元素中的左右边界。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/704.binary-search.cpp`
- 新函数名：`searchOpt`
- 保留用户原实现：是
