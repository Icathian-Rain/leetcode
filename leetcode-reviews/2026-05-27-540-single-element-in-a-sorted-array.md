# 题解点评 - 540. Single Element in a Sorted Array

## 基本信息

- 日期：2026-05-27
- 主题：第 5 周二分查找 - 第 7 天综合复盘与设计迁移
- 难度：中等
- 本次结果：有边界风险，需修正后提交
- 对应源码：`src/540.single-element-in-a-sorted-array.cpp`
- 资料来源：LeetCode 中文题目页、leetcode.ca
- 查询日期：2026-05-27

## 用户思路概述

1. 利用有序数组中成对元素出现的结构，通过下标奇偶判断当前元素应该和左边还是右边配对。
2. 若当前位置的配对关系被破坏，就把右边界收缩到当前位置；否则向右排除一段。
3. 循环结束后返回 `nums[l]`。

## 用户解法复杂度

- 时间复杂度：`O(log n)`
- 空间复杂度：`O(1)`
- 复杂度来源：每轮通过配对结构排除一半候选区间。

## 用户代码注释版

```cpp
class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        int n=nums.size();
        if(n == 1) return nums[0];
        int l=0, r=n;
        while(l<r) {
            int m=l+(r-l)/2;
            if(m%2==1) {
                // 奇数下标正常应与左侧配对。
                if(nums[m] != nums[m-1]) r = m;
                else l=m+1;
            } else {
                // 偶数下标正常应与右侧配对；当 m == n-1 时这里会越界。
                if(nums[m] != nums[m+1]) r=m;
                else l=m+1;
            }
        }
        return nums[l];
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 配对结构 | 已经抓住单一元素前后配对奇偶会翻转 | 方向判断基础正确 | 把 `mid` 统一调整到偶数下标，再比较 `mid` 与 `mid + 1` |
| 边界安全 | 半开区间中可能让偶数 `m` 落到 `n - 1` | 会访问 `nums[n]`，属于阻塞级风险 | 使用闭区间 `[0, n - 1]` 并保证 `mid + 1` 有效 |
| 收缩步长 | 配对完整时只移动到 `m + 1` | 仍可能正确推进，但表达不够贴合“排除一对” | 配对完整时直接 `left = middle + 2` |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 能想到用奇偶下标判断配对关系 | 尾部越界风险，区间含义偏松 | 适合复盘思路，不建议直接提交 |
| 推荐最优解 | 区间安全，配对含义清晰，代码短 | 需要记住先把 `middle` 调成偶数 | 适合作为成对结构变化题模板 |

## 最优解法

1. 使用闭区间 `[left, right]`，答案始终在区间内。
2. 每轮把 `middle` 调整为偶数，让它指向一组候选配对的左端。
3. 如果 `nums[middle] == nums[middle + 1]`，说明这对完整，单一元素在右侧；否则答案在左侧含 `middle`。

- 最优时间复杂度：`O(log n)`
- 最优空间复杂度：`O(1)`

### 最优解代码

```cpp
class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        int left = 0;
        int right = static_cast<int>(nums.size()) - 1;

        while (left < right) {
            int middle = left + (right - left) / 2;
            if (middle % 2 == 1) {
                --middle; // 始终让 middle 指向一组候选配对的左端。
            }

            if (nums[middle] == nums[middle + 1]) {
                left = middle + 2; // 当前配对完整，单一元素在右侧。
            } else {
                right = middle; // 配对结构从 middle 开始被破坏，答案在左侧含 middle。
            }
        }

        return nums[left];
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | 半开区间内找破坏点 | 闭区间内答案始终存在 | 让区间语义保护数组访问 |
| 更新逻辑 | 奇偶分支分别比较左右 | 统一比较一组配对 | 减少分支，降低越界概率 |
| 边界处理 | `m == n - 1` 时可能访问 `m + 1` | `left < right` 配合偶数化保证安全 | 手推单一元素在末尾的样例 |
| 复杂度 | `O(log n)` / `O(1)` | `O(log n)` / `O(1)` | 复杂度已达标，主要修正确性 |

## 下一步建议

建议重写当前题一次，重点手推 `[1,1,2,2,3]` 和 `[1,2,2,3,3]`，确认不会访问越界。

## 后续练习

1. `34. Find First and Last Position of Element in Sorted Array` - 继续训练边界含义。
2. `658. Find K Closest Elements` - 练习把答案建模为连续窗口。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/540.single-element-in-a-sorted-array.cpp`
- 新函数名：`singleNonDuplicateOpt`
- 保留用户原实现：是
