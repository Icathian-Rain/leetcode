# 题解点评 - 74. Search a 2D Matrix

## 基本信息

- 日期：2026-05-24
- 主题：二分查找 - 矩阵中的有序关系
- 难度：中等
- 本次结果：待提交验证，源码逻辑检查通过
- 对应源码：`src/74.search-a-2-d-matrix.cpp`
- 资料来源：本地周计划与源码，题号/题名/难度沿用已校准计划；未联网校准
- 查询日期：未联网

## 用户思路概述

1. 先根据每一行的首元素二分，找出最后一个首元素不大于 `target` 的行。
2. 如果不存在这样的行，说明 `target` 比矩阵最小值还小，直接返回 `false`。
3. 在候选行内再次二分，找第一个大于等于 `target` 的列。
4. 如果该列越界或值不等于 `target`，返回 `false`；否则返回 `true`。

## 用户解法复杂度

- 时间复杂度：`O(log m + log n)`
- 空间复杂度：`O(1)`
- 复杂度来源：先在行首数组上二分，再在单行内二分。

## 用户代码注释版

> 只在点评文档中展示加注释版本；不要把这些注释写回 `src/*.cpp` 的用户原代码。

```cpp
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m=matrix.size(), n=matrix[0].size();
        int l=0, r=m;
        while(l<r) {
            int m=l+(r-l)/2; // 这里局部变量 m 会遮蔽行数 m，虽然可编译但不利于复盘。
            if(matrix[m][0] > target) {
                r=m; // 找第一个行首大于 target 的行。
            } else {
                l=m+1;
            }
        }

        if(l == 0) return false;
        int i=l-1; // 候选行是第一个行首大于 target 的前一行。
        l=0, r=n;
        while(l<r) {
            int m=l+(r-l)/2;
            if(matrix[i][m] >= target) {
                r=m; // 在候选行中找第一个 >= target 的列。
            } else {
                l=m+1;
            }
        }
        if(l == n || matrix[i][l] != target) {
            return false;
        }
        return true;
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 矩阵整体有序 | 能先定位行再定位列 | 正确利用了第 74 题的特殊性质 | 可以进一步映射成一维二分，代码更统一 |
| 边界处理 | `l == 0` 和列越界检查完整 | 覆盖目标小于最小值、行内不存在 | 继续保持先判越界再取值 |
| 命名清晰度 | 内层 `int m` 遮蔽外层行数 `m` | 不影响正确性，但降低可读性 | 用 `rows/cols/middle` 避免混淆 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 两次二分语义清楚，边界完整 | 比一维映射多一些分支，变量遮蔽略影响可读性 | 适合理解矩阵行范围与行内范围 |
| 推荐最优解 | 把矩阵当作长度 `m*n` 的一维有序数组，模板统一 | 需要熟悉一维下标到行列的转换 | 适合作为第 74 题标准写法 |

## 最优解法

1. 第 74 题的矩阵满足上一行最后一个元素小于下一行第一个元素，因此整体可以看成一维有序数组。
2. 在 `[0, rows * cols - 1]` 上做普通二分。
3. 对任意一维位置 `middle`，行号为 `middle / cols`，列号为 `middle % cols`。
4. 按该位置值与 `target` 的大小关系收缩区间。

- 最优时间复杂度：`O(log(mn))`
- 最优空间复杂度：`O(1)`

### 最优解代码

```cpp
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int rows = static_cast<int>(matrix.size());
        int cols = static_cast<int>(matrix[0].size());
        int left = 0;
        int right = rows * cols - 1;

        while (left <= right) {
            int middle = left + (right - left) / 2;
            int row = middle / cols;
            int col = middle % cols;
            if (matrix[row][col] == target) {
                return true;
            }
            if (matrix[row][col] < target) {
                left = middle + 1;
            } else {
                right = middle - 1;
            }
        }

        return false;
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | 先行后列两段二分 | 一个一维搜索区间 | 识别整体有序时优先拍平成一维 |
| 更新逻辑 | 行首边界 + 行内边界 | 普通二分比较当前值 | 一维写法更接近基础模板 |
| 边界处理 | 需要额外处理没有候选行 | 区间自然覆盖所有位置 | 减少特殊分支 |
| 复杂度 | `O(log m + log n)` | `O(log(mn))` | 数学上等价，写法更统一 |

## 下一步建议

进入下一题。建议复盘第 74 和第 240 的差异：第 74 能拍平成一维有序数组，第 240 不能。

## 后续练习

1. `240. Search a 2D Matrix II` - 练习只能利用行列有序时的搜索方式。
2. `378. Kth Smallest Element in a Sorted Matrix` - 继续辨析矩阵有序关系和答案值二分。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/74.search-a-2-d-matrix.cpp`
- 新函数名：`searchMatrixOpt`
- 保留用户原实现：是
