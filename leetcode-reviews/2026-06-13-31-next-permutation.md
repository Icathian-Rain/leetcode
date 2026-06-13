# 题解点评 - 31. Next Permutation

## 基本信息

- 日期：2026-06-13
- 主题：排列 / 原地构造下一个字典序
- 难度：中等
- 本次结果：待提交验证，源码逻辑检查通过
- 对应源码：`src/31.next-permutation.cpp`
- 资料来源：LeetCode 官方题目页 `https://leetcode.cn/problems/next-permutation/`
- 查询日期：2026-06-13

## 用户思路概述

1. 从右往左找到第一个 `nums[i] < nums[i + 1]` 的位置，这个位置是可以变大的主元。
2. 如果找到了主元，再从右往左找第一个大于 `nums[i]` 的元素并交换。
3. 最后反转主元右侧后缀，让后缀变成最小升序状态。
4. 如果整个数组都是降序，主元不存在，直接反转整个数组，得到最小排列。

## 用户解法复杂度

- 时间复杂度：`O(n)`
- 空间复杂度：`O(1)`
- 复杂度来源：最多三次线性扫描：找主元、找交换对象、反转后缀。

## 用户代码注释版

```cpp
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int n = nums.size();
        int i = n - 2;
        while (i >= 0 && nums[i] >= nums[i + 1]) {
            i--; // 找到从右往左第一个可以变大的位置。
        }

        if (i >= 0) {
            int j = n - 1;
            while (j >= 0 && nums[j] <= nums[i]) {
                j--; // 后缀是降序，从右往左第一个更大的值就是最小可交换值。
            }
            swap(nums[i], nums[j]);
        }

        reverse(nums.begin() + i + 1, nums.end()); // 让后缀变成最小状态。
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 主元定位 | 从右往左找 `nums[i] < nums[i+1]` | 正确找到需要增大的最低位 | 记住右侧后缀在此时一定是降序 |
| 交换对象 | 从右侧找第一个更大的元素 | 正确保证增幅最小 | 因为后缀降序，所以从右找第一个大于主元即可 |
| 后缀处理 | 交换后反转后缀 | 正确得到下一个字典序，而不是任意更大排列 | 反转是本题最关键的收尾动作 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 已经是标准最优解，边界处理自然覆盖降序数组 | 变量命名可以更语义化 | 适合直接提交 |
| 推荐最优解 | 与用户解法复杂度相同，命名更强调主元和后继 | 无本质差异 | 用作复盘模板 |

## 最优解法

1. 从右往左找到第一个升序相邻对的左端点 `pivot`。
2. 如果 `pivot` 存在，从右往左找到第一个大于它的 `successor` 并交换。
3. 反转 `pivot + 1` 到末尾的后缀，使后缀变成最小字典序。

- 最优时间复杂度：`O(n)`
- 最优空间复杂度：`O(1)`

### 最优解代码

```cpp
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int pivot = static_cast<int>(nums.size()) - 2;
        while (pivot >= 0 && nums[pivot] >= nums[pivot + 1]) {
            --pivot;
        }

        if (pivot >= 0) {
            int successor = static_cast<int>(nums.size()) - 1;
            while (nums[successor] <= nums[pivot]) {
                --successor;
            }
            swap(nums[pivot], nums[successor]);
        }

        // pivot 右侧原本是降序，翻转后得到最小后缀。
        reverse(nums.begin() + pivot + 1, nums.end());
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | `i/j` 表示主元和交换位置 | `pivot/successor` 语义更明确 | 复盘时用语义名讲清角色 |
| 更新逻辑 | 找主元、交换、反转 | 相同 | 已经掌握标准流程 |
| 边界处理 | 降序数组反转全数组 | 相同 | 正确 |
| 复杂度 | `O(n)` / `O(1)` | `O(n)` / `O(1)` | 已最优 |

## 下一步建议

这题建议重点复盘“为什么右侧后缀一定是降序”。一旦这个点想通，交换后只需要反转后缀就很自然。

## 后续练习

1. `46. Permutations` - 对比“生成所有排列”和“只构造下一个排列”的差异。
2. `31. Next Permutation` 手写复盘 - 用 `[1,3,2]`、`[2,3,1]`、`[3,2,1]` 三组手推。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/31.next-permutation.cpp`
- 新函数名：`nextPermutationOpt`
- 保留用户原实现：是
