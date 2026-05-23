# 题解点评 - 278. First Bad Version

## 基本信息

- 日期：2026-05-23
- 主题：二分查找 - 边界定位与近似答案
- 难度：简单
- 本次结果：待提交验证，源码逻辑检查通过
- 对应源码：`src/278.first-bad-version.cpp`
- 资料来源：本地周计划与源码，题号/题名/难度沿用已校准计划；未联网校准
- 查询日期：未联网

## 用户思路概述

1. 把版本区间定义为 `[1, n]`，维护左右边界 `l` 和 `r`。
2. 每次取中点 `m`，调用 `isBadVersion(m)` 判断当前版本是否已经错误。
3. 如果 `m` 是错误版本，说明第一个错误版本在 `[l, m]` 中，收缩右边界。
4. 如果 `m` 不是错误版本，说明答案只能在 `m` 右侧，移动左边界到 `m + 1`。
5. 循环结束时 `l == r`，返回该位置作为第一个错误版本。

## 用户解法复杂度

- 时间复杂度：`O(log n)`
- 空间复杂度：`O(1)`
- 复杂度来源：每次调用 `isBadVersion` 后排除一半版本区间，只维护常数个变量。

## 用户代码注释版

> 只在点评文档中展示加注释版本；不要把这些注释写回 `src/*.cpp` 的用户原代码。

```cpp
using ll=long long;
class Solution {
public:
    int firstBadVersion(int n) {
        ll l=1, r=n; // 搜索闭区间 [l, r]，答案一定在这个区间内。
        while(l<r) {
            int m=l+(r-l)/2; // 防止 l + r 在极大 n 下溢出。
            if(isBadVersion(m)) {
                r=m; // m 已经错误，m 仍可能是第一个错误版本，所以保留。
            } else {
                l=m+1; // m 不是错误版本，m 及左侧都可以排除。
            }
        }
        return l; // l == r 时，就是第一个进入 bad 区间的位置。
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 单调性建模 | 能把版本序列看成 `false...false true...true` | 正确命中本题核心模式 | 继续复盘 `true` 分支为什么不能写成 `r = m - 1` |
| 区间定义 | 使用闭区间 `[1, n]`，循环条件为 `l < r` | 端点含义稳定，不会漏掉答案 | 每次写二分前先写一句“答案仍在闭区间内” |
| 类型选择 | 用 `long long` 保存边界，`m` 用 `int` | 正确但略不统一；本题 `n` 是 `int`，防溢出中点即可 | 可以统一用 `int left/right/middle` 加安全中点公式 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 区间收缩方向正确，复杂度最优，边界覆盖到 `n = 1` | `ll` 与 `int` 混用略影响表达一致性 | 适合所有符合版本单调性的输入 |
| 推荐最优解 | 保持同一闭区间语义，变量命名更贴近模板 | 本质与用户解法一致，没有复杂度提升空间 | 作为“第一个 true”类题目的标准骨架 |

## 最优解法

1. 把 `isBadVersion(version)` 作为 `check(version)`，目标是找第一个 `true`。
2. 在闭区间 `[left, right]` 中维护答案一定存在。
3. `check(middle)` 为真时，答案可能就是 `middle`，令 `right = middle`。
4. `check(middle)` 为假时，`middle` 及其左侧都不是答案，令 `left = middle + 1`。

- 最优时间复杂度：`O(log n)`
- 最优空间复杂度：`O(1)`

### 最优解代码

```cpp
class Solution {
public:
    int firstBadVersion(int n) {
        int left = 1;
        int right = n;

        while (left < right) {
            int middle = left + (right - left) / 2;
            if (isBadVersion(middle)) {
                right = middle; // middle 可能就是第一个错误版本，必须保留。
            } else {
                left = middle + 1; // middle 及其左侧都不是错误版本。
            }
        }

        return left;
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | `ll l, r` 表示闭区间 | `int left, right` 表示闭区间 | 命名可以更语义化，类型统一即可 |
| 更新逻辑 | bad 保留中点，good 排除中点 | 相同 | 重点不是改代码，而是能解释保留/排除理由 |
| 边界处理 | 覆盖 `n = 1` 和极大 `n` | 覆盖相同边界 | 继续手推长度 1、2 的版本区间 |
| 复杂度 | `O(log n)` / `O(1)` | `O(log n)` / `O(1)` | 已达最优 |

## 下一步建议

进入下一题即可。复盘时重点口述：本题返回的是“第一个 `true` 的位置”，不是查找某个具体值。

## 后续练习

1. `34. Find First and Last Position of Element in Sorted Array` - 同样是边界定位，但要同时处理左边界和右边界。
2. `875. Koko Eating Bananas` - 把 `check` 从数组下标迁移到答案值范围。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/278.first-bad-version.cpp`
- 新函数名：`firstBadVersionOpt`
- 保留用户原实现：是
