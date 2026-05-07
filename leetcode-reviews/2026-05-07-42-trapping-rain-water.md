# 题解点评 - 42. Trapping Rain Water

## 基本信息

- 日期：2026-05-07
- 主题：双指针与滑动窗口 - 综合迁移与模拟面试
- 难度：困难
- 本次结果：待提交验证，源码逻辑检查通过
- 对应源码：`src/42.trapping-rain-water.cpp`
- 资料来源：本地周计划（题号、英文题名和难度已于 2026-05-01 校准）+ 本地源码；本次未重新联网校准
- 查询日期：未联网

## 用户思路概述

1. 从左到右预处理 `lm[i]`，表示位置 `i` 左侧含自身的最高柱子。
2. 从右到左预处理 `rm[i]`，表示位置 `i` 右侧含自身的最高柱子。
3. 对每个位置，水位由 `min(lm[i], rm[i])` 决定。
4. 把每个位置可接的水量 `min(lm[i], rm[i]) - height[i]` 累加为答案。

## 用户解法复杂度

- 时间复杂度：`O(n)`
- 空间复杂度：`O(n)`
- 复杂度来源：三次线性扫描，额外保存左右最大值数组。

## 用户代码注释版

```cpp
class Solution {
public:
    int trap(vector<int>& height) {
        int n=height.size();
        vector<int> lm(n, 0);
        lm[0]=height[0]; // lm[i] 表示 i 左侧含自身的最高柱子。
        for(int i=1; i<n; i++) {
            lm[i] = max(lm[i-1], height[i]);
        }

        vector<int> rm(n, 0);
        rm[n-1]=height[n-1]; // rm[i] 表示 i 右侧含自身的最高柱子。
        for(int i=n-2; i>=0; i--) {
            rm[i] = max(rm[i+1], height[i]);
        }

        int ans=0;
        for(int i=0; i<n; i++) {
            // 当前位置水位由左右两侧较低的最高边界决定。
            ans+=min(lm[i], rm[i])-height[i];
        }
        return ans;
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 水位来源 | 正确使用左右最大值的较小者。 | 核心建模准确，能稳定得到答案。 | 复盘时把“短板决定水位”说成每一格的局部规则。 |
| 空间优化 | 当前保存两张数组。 | 时间最优，但空间不是本周双指针目标下的最优表达。 | 练习用左右指针和两个历史最大值压缩空间。 |
| 边界处理 | LeetCode 约束下 `n >= 1` 没问题。 | 如果放到通用函数，空数组会访问 `lm[0]`。 | 推荐最优写法自然支持空输入，代码更稳。 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 思路直观，容易证明，每个位置水量清楚。 | 需要 `O(n)` 额外空间；没有体现第 7 天要求的双指针移动依据。 | 适合初次理解本题水位公式。 |
| 推荐最优解 | 时间 `O(n)`、空间 `O(1)`，每次只结算确定的一侧。 | 推理门槛更高，需要说清为什么能移动较低一侧。 | 适合面试和本周综合迁移。 |

## 最优解法

1. 用 `left`、`right` 从两端向中间扫描，同时维护 `leftMax` 和 `rightMax`。
2. 如果 `height[left] < height[right]`，说明右侧至少存在一个更高边界，左侧当前位置水量只取决于 `leftMax`。
3. 反之处理右侧当前位置，它的水量只取决于 `rightMax`。
4. 每次结算一侧后移动对应指针，直到两指针相遇。

- 最优时间复杂度：`O(n)`
- 最优空间复杂度：`O(1)`

### 最优解代码

```cpp
class Solution {
public:
    int trap(vector<int>& height) {
        int left = 0;
        int right = (int)height.size() - 1;
        int leftMax = 0;
        int rightMax = 0;
        int ans = 0;

        while (left < right) {
            if (height[left] < height[right]) {
                leftMax = max(leftMax, height[left]);
                // 右侧已有更高边界，左侧当前位置只由 leftMax 决定。
                ans += leftMax - height[left];
                ++left;
            } else {
                rightMax = max(rightMax, height[right]);
                // 左侧已有不低于右侧的边界，右侧当前位置只由 rightMax 决定。
                ans += rightMax - height[right];
                --right;
            }
        }

        return ans;
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | `lm`、`rm` 保存每个位置两侧最大值。 | `leftMax`、`rightMax` 保存当前两侧历史最大值。 | 从“全部预处理”迁移到“边走边结算”。 |
| 更新逻辑 | 预处理后统一累加。 | 每轮根据较低一侧确定当前位置答案。 | 重点练移动依据，而不是只背水位公式。 |
| 边界处理 | 依赖非空约束。 | 空数组也自然返回 `0`。 | 通用代码建议避免裸访问首尾。 |
| 复杂度 | `O(n)` / `O(n)` | `O(n)` / `O(1)` | 空间可以压缩到常数。 |

## 下一步建议

建议重写一遍空间 `O(1)` 的双指针版本。不是因为当前解法不好，而是这题在本周的训练价值正好落在“为什么可以结算较低一侧”。

## 后续练习

1. `11. Container With Most Water` - 复盘移动较短边的排除理由。
2. `407. Trapping Rain Water II` - 作为以后图/堆专题的高阶迁移，不建议现在立刻做。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/42.trapping-rain-water.cpp`
- 新函数名：`trapOpt`
- 保留用户原实现：是
