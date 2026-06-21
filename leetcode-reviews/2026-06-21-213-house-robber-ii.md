# 题解点评 - 213. House Robber II

## 基本信息

- 日期：2026-06-21
- 主题：动态规划 / 环形相邻约束
- 难度：中等
- 本次结果：通过，场景拆分正确
- 对应源码：`src/213.house-robber-ii.cpp`
- 资料来源：LeetCode 官方题目页 `https://leetcode.cn/problems/house-robber-ii/` 与本地源码
- 查询日期：2026-06-21

## 用户思路概述

1. 先处理 `n == 1` 和 `n == 2` 的短数组边界。
2. 因为首尾不能同时选择，把问题拆成两个线性范围。
3. 第一种范围考虑 `0..n-2`，也就是排除最后一间。
4. 第二种范围考虑 `1..n-1`，也就是排除第一间。
5. 两个线性结果取最大值。

## 用户解法复杂度

- 时间复杂度：`O(n)`
- 空间复杂度：`O(n)`
- 复杂度来源：两次线性扫描，每次使用一个长度为 `n` 的 `dp` 数组。

## 用户代码注释版

```cpp
class Solution {
public:
    int rob(vector<int>& nums) {
        int n=nums.size();
        if(n == 1) return nums[0];
        if(n == 2) return max(nums[0], nums[1]);
        int ans = 0;
        vector<int> dp(n, 0);

        dp[0] = nums[0];
        dp[1] = max(nums[0], nums[1]);
        for(int i=2; i<=n-2; i++) {
            dp[i] = max(dp[i-1], dp[i-2]+nums[i]); // 线性打家劫舍：不偷当前或偷当前。
        }
        ans = max(ans, dp[n-2]); // 排除最后一间。

        dp.assign(n, 0);
        dp[1] = nums[1];
        dp[2] = max(nums[1], nums[2]);
        for(int i=3; i<=n-1; i++) {
            dp[i] = max(dp[i-1], dp[i-2]+nums[i]); // 排除第一间后的线性范围。
        }
        ans = max(ans, dp[n-1]);
        return ans;
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 环形约束 | 拆成排除首或排除尾两个场景 | 正确避开首尾同时选择 | 这是本题最关键的建模 |
| 线性子问题 | 沿用 198 的转移 | 迁移能力很好 | 可以抽成区间辅助函数减少重复 |
| 空间使用 | 每个场景用 `dp` 数组 | 正确但空间可降 | 线性打家劫舍只依赖前两项 |
| 边界处理 | 对 `n == 1/2` 特判 | 避免短数组越界 | 保持这个习惯 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 思路正确，两个场景覆盖完整 | 两段代码重复，空间可压缩 | 学习阶段清晰可靠 |
| 推荐最优解 | 抽出区间函数，空间 `O(1)` | 需要小心左右端点闭区间 | 更适合提交和复用 |

## 最优解法

1. 写一个线性区间函数 `robRange(left, right)`。
2. 在区间内用两个变量滚动保存前两项最优结果。
3. 环形问题只需比较 `0..n-2` 和 `1..n-1` 两个线性结果。

- 最优时间复杂度：`O(n)`
- 最优空间复杂度：`O(1)`

### 最优解代码

```cpp
class Solution {
    int robRange(const vector<int>& nums, int left, int right) {
        int bestTwoBack = 0;
        int bestOneBack = 0;
        for (int i = left; i <= right; i++) {
            // 偷当前房屋时，前一间不能偷。
            int current = max(bestOneBack, bestTwoBack + nums[i]);
            bestTwoBack = bestOneBack;
            bestOneBack = current;
        }
        return bestOneBack;
    }

public:
    int rob(vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        if (n == 1) return nums[0];
        return max(robRange(nums, 0, n - 2), robRange(nums, 1, n - 1));
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | `dp[i]` 表示区间内前缀最优 | 两个变量表示前两项最优 | 本质相同 |
| 更新逻辑 | 两段手写线性 DP | 复用 `robRange` | 减少重复和端点错误 |
| 边界处理 | 特判 `n == 1/2` | 只需特判 `n == 1` | 区间函数自然覆盖 `n == 2` |
| 复杂度 | `O(n)` / `O(n)` | `O(n)` / `O(1)` | 空间可优化 |

## 下一步建议

可以进入下一题。复盘时记住：环形相邻限制通常先拆成“不取首”和“不取尾”两个线性问题。

## 后续练习

1. `740. Delete and Earn` - 把数值冲突转成相邻选择限制。
2. `198. House Robber` - 回看线性子问题模板是否已经完全内化。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/213.house-robber-ii.cpp`
- 新函数名：`robOpt`
- 保留用户原实现：是
