# 题解点评 - 1901. Find a Peak Element II

## 基本信息

- 日期：2026-05-27
- 主题：第 5 周二分查找 - 第 6 天峰值、分割与困难边界
- 难度：中等
- 本次结果：待提交验证，源码逻辑检查通过
- 对应源码：`src/1901.find-a-peak-element-ii.cpp`
- 资料来源：LeetCode 官方题目页、LeetCode Wiki
- 查询日期：2026-05-27

## 用户思路概述

1. 在行维度上做二分，每轮选择中间行 `i`。
2. 找到第 `i` 行的最大值列 `j`，这样该位置天然不小于左右邻居。
3. 如果上方或下方存在更大值，就向对应方向收缩行区间；否则返回 `[i, j]`。

## 用户解法复杂度

- 时间复杂度：`O(n log m)`，其中 `m` 是行数，`n` 是列数。
- 空间复杂度：`O(1)`
- 复杂度来源：每轮扫描一整行找最大值，行区间二分收缩。

## 用户代码注释版

```cpp
class Solution {
public:
    vector<int> findPeakGrid(vector<vector<int>>& mat) {
        int m=mat.size();
        int l=0, r=m;
        while(l<r) {
            int i=l+(r-l)/2; // 在行维度上取中间行。
            int j=max_element(mat[i].begin(), mat[i].end())-mat[i].begin();
            // 中间行最大值若小于上方同列值，峰值可以往上找。
            if(i-1>=0 && mat[i][j] < mat[i-1][j]) {
                r = i;
                continue;
            }
            // 若下方同列值更大，沿更大方向往下找。
            if(i+1<m && mat[i][j] < mat[i+1][j]) {
                l = i+1;
                continue;
            }
            return {i, j}; // 上下都不更大，且左右不大于行最大值，是合法峰值。
        }
        return {};
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 行最大值的意义 | 已经用行最大值消掉左右方向风险 | 正确性核心成立 | 复盘时说清“左右邻居不用再单独比较”的原因 |
| 收缩方向 | 能沿上下更大值方向移动 | 满足峰值存在性证明 | 可简化为只和下一行比较，减少双分支 |
| 返回条件 | 上下都不更大时返回当前位置 | 正确 | 注意题目保证相邻元素不相等，严格峰值判断更干净 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 建模准确，直接利用行最大值 | 半开区间加上下双判断略绕 | 适合训练二维峰值存在性 |
| 推荐最优解 | 只比较中间行最大值和下一行同列值 | 需要理解为什么不看上一行也可以 | 适合稳定写出 `O(n log m)` |

## 最优解法

1. 在行区间 `[left, right]` 中二分，取中间行。
2. 找到中间行最大值所在列 `col`，它已经不小于左右邻居。
3. 若 `mat[middle][col] > mat[middle + 1][col]`，峰值在上半部分含当前行；否则峰值在下半部分。
4. 收缩到单行后，再取该行最大值作为答案。

- 最优时间复杂度：`O(n log m)`
- 最优空间复杂度：`O(1)`

### 最优解代码

```cpp
class Solution {
public:
    vector<int> findPeakGrid(vector<vector<int>>& mat) {
        int rows = mat.size();
        int left = 0;
        int right = rows - 1;

        while (left < right) {
            int middle = left + (right - left) / 2;
            int col = max_element(mat[middle].begin(), mat[middle].end()) - mat[middle].begin();
            if (mat[middle][col] > mat[middle + 1][col]) {
                right = middle; // 当前行最大值向上不低，峰值一定在上半部分含 middle。
            } else {
                left = middle + 1; // 下方更大，沿上升方向继续寻找峰值。
            }
        }

        int col = max_element(mat[left].begin(), mat[left].end()) - mat[left].begin();
        return {left, col};
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | 半开行区间 `[l, r)` | 闭区间 `[left, right]` | 用“答案始终在区间内”统一心智 |
| 更新逻辑 | 分别比较上方和下方 | 只比较下一行 | 减少分支，避免重复证明 |
| 边界处理 | 用 `i-1>=0`、`i+1<m` 防越界 | `left < right` 保证 `middle + 1` 有效 | 让循环条件承担边界约束 |
| 复杂度 | `O(n log m)` / `O(1)` | `O(n log m)` / `O(1)` | 复杂度已达标 |

## 下一步建议

可以进入 `4. Median of Two Sorted Arrays`，但要放慢节奏：它不是普通峰值题，而是要求在两个有序序列之间排除不可能成为中位数的一段。

## 后续练习

1. `162. Find Peak Element` - 回看一维版本，巩固沿更大方向搜索。
2. `74. Search a 2D Matrix` - 对比二维题中“能否拍平成一维有序”的差异。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/1901.find-a-peak-element-ii.cpp`
- 新函数名：`findPeakGridOpt`
- 保留用户原实现：是
