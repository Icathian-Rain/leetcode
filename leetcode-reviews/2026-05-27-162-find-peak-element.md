# 题解点评 - 162. Find Peak Element

## 基本信息

- 日期：2026-05-27
- 主题：第 5 周二分查找 - 第 6 天峰值、分割与困难边界
- 难度：中等
- 本次结果：待提交验证，源码逻辑检查通过
- 对应源码：`src/162.find-peak-element.cpp`
- 资料来源：LeetCode 官方题目页
- 查询日期：2026-05-27

## 用户思路概述

1. 先处理 `n == 1`，单元素直接返回下标 `0`。
2. 定义 `check(m)`，把当前位置分成峰值、向右上升、向左或左侧可保留三种状态。
3. 在 `[0, n)` 区间中二分；命中峰值时直接返回，否则根据 `check` 结果收缩左右边界。

## 用户解法复杂度

- 时间复杂度：`O(log n)`
- 空间复杂度：`O(1)`
- 复杂度来源：每轮根据 `mid` 附近元素排除一侧区间，只使用常数额外变量。

## 用户代码注释版

```cpp
class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int n=nums.size();
        if(n == 1) return 0; // 单元素在虚拟 -inf 边界下必然是峰值。

        auto check = [&](int m) {
            if(m == 0) {
                // 左边界只需要和右邻居比较。
                if(nums[m] > nums[m+1]) return 0;
                return -1;
            } else if(m == n-1) {
                // 右边界只需要和左邻居比较。
                if(nums[m] > nums[m-1]) return 0;
                return -1;
            } else {
                if(nums[m] > nums[m-1] && nums[m] > nums[m+1]) return 0;
                if(nums[m] < nums[m+1]) return 1; // 右侧上升，右边存在峰值。
                return -1; // 否则向左侧收缩。
            }
        };

        int l=0, r=n;
        while(l<r) {
            int m=l+(r-l)/2;
            int res = check(m);
            if(res == 0) return m;
            if(res == -1) r = m;
            else l = m+1;
        }
        return 0;
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 峰值不要求唯一 | 已经接受“找到任意峰值”并可提前返回 | 正确性成立 | 继续保持，不要额外寻找最大值 |
| 收缩依据 | 能根据上升方向判断右侧存在峰值 | 命中核心模式 | 可进一步简化为只比较 `nums[mid]` 和 `nums[mid + 1]` |
| 边界处理 | 单独处理首尾，逻辑正确但分支偏多 | 可读性稍重 | 用右闭区间 `[0, n - 1]` 可以天然避免访问越界 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 能覆盖边界，方向判断正确 | `check` 返回值语义需要额外记忆，分支较多 | 适合训练“当前位置状态分类” |
| 推荐最优解 | 只比较相邻两项，区间语义更轻 | 初学时需要理解“沿上坡一定能到峰值” | 适合本题和第 1901 题迁移 |

## 最优解法

1. 使用闭区间 `[left, right]`，答案始终在区间内。
2. 比较 `nums[middle]` 与 `nums[middle + 1]`：如果左侧更高或开始下降，峰值在左半部分含 `middle`；否则峰值在右半部分。
3. 循环结束时 `left == right`，该位置就是一个峰值。

- 最优时间复杂度：`O(log n)`
- 最优空间复杂度：`O(1)`

### 最优解代码

```cpp
class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int left = 0;
        int right = static_cast<int>(nums.size()) - 1;

        while (left < right) {
            int middle = left + (right - left) / 2;
            if (nums[middle] > nums[middle + 1]) {
                right = middle; // 下降方向左侧一定存在峰值，middle 也要保留。
            } else {
                left = middle + 1; // 上升方向右侧一定存在峰值。
            }
        }

        return left;
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | `check` 返回三类状态 | 区间内始终存在峰值 | 把“存在性”作为循环不变量 |
| 更新逻辑 | 根据峰值、左收缩、右收缩分支 | 只按相邻坡度收缩 | 减少边界特判 |
| 边界处理 | 显式处理首尾 | 闭区间保证 `mid + 1` 有效 | 优先选择能天然规避越界的区间 |
| 复杂度 | `O(log n)` / `O(1)` | `O(log n)` / `O(1)` | 主要优化表达稳定性 |

## 下一步建议

继续进入 `1901. Find a Peak Element II`，重点观察“一维坡度方向”如何迁移到“按行或按列收缩”。

## 后续练习

1. `1901. Find a Peak Element II` - 把峰值存在性从一维迁移到二维。
2. `852. Peak Index in a Mountain Array` - 用更强的单峰条件巩固相邻比较。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/162.find-peak-element.cpp`
- 新函数名：`findPeakElementOpt`
- 保留用户原实现：是
