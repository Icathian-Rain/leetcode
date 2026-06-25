# 题解点评 - 300. Longest Increasing Subsequence

## 基本信息

- 日期：2026-06-25
- 主题：动态规划 / 子序列状态
- 难度：中等
- 本次结果：通过，`O(n^2)` 状态定义清楚
- 对应源码：`src/300.longest-increasing-subsequence.cpp`
- 资料来源：LeetCode 官方题目页 `https://leetcode.cn/problems/longest-increasing-subsequence/` 与本地源码
- 查询日期：2026-06-25

## 用户思路概述

1. 用 `dp[i]` 表示以第 `i` 个元素结尾的最长递增子序列长度。
2. 枚举当前元素 `i`，再向前找所有比它小的元素 `j`。
3. 如果 `nums[i-1] > nums[j-1]`，就可以从 `dp[j]` 转移过来。
4. 用 `ans` 记录所有结尾位置中的最大值。

## 用户解法复杂度

- 时间复杂度：`O(n^2)`
- 空间复杂度：`O(n)`
- 复杂度来源：每个位置都会向前枚举所有候选来源。

## 用户代码注释版

```cpp
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n=nums.size();
        vector<int> dp(n+1, 1); // dp[i] 表示以 nums[i-1] 结尾的最长长度。
        int ans = 1;
        for(int i=1; i<=n; i++) {
            for(int j=i-1; j>=1; j--) {
                if(nums[i-1] > nums[j-1]) {
                    dp[i] = max(dp[i], dp[j]+1);
                }
            }
            ans = max(ans, dp[i]);
        }
        return ans;
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 状态定义 | 以当前位置结尾 | 正确，能覆盖所有来源 | 继续保持“包含当前位置”的意识 |
| 严格递增 | 使用 `>` | 正确排除相等元素 | 等号是本题常见坑 |
| 复杂度 | 写出标准 `O(n^2)` | 可通过，但存在更优写法 | 补一个 `O(n log n)` 版本 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 状态直观，容易证明 | 时间复杂度不是最优 | 学习 DP 状态很合适 |
| 推荐最优解 | 用最小结尾数组降到 `O(n log n)` | `tails` 含义不等于真实子序列 | 面试常见优化 |

## 最优解法

1. `tails[len - 1]` 记录长度为 `len` 的递增子序列的最小可能结尾。
2. 对每个数，用二分找到第一个大于等于它的位置。
3. 替换该位置，让同长度子序列结尾更小；如果找不到，则扩展长度。

- 最优时间复杂度：`O(n log n)`
- 最优空间复杂度：`O(n)`

### 最优解代码

```cpp
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int> tails;
        for (int num : nums) {
            // tails[len - 1] 是长度为 len 的递增子序列的最小结尾。
            auto it = lower_bound(tails.begin(), tails.end(), num);
            if (it == tails.end()) tails.push_back(num);
            else *it = num;
        }
        return static_cast<int>(tails.size());
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | 每个位置结尾的长度 | 每种长度的最小结尾 | 从“枚举来源”过渡到“维护候选结尾” |
| 更新逻辑 | 向前扫描 | 二分替换 | 降低时间复杂度 |
| 边界处理 | 初始长度为 1 | 空 `tails` 自然处理 | 都稳定 |
| 复杂度 | `O(n^2)` / `O(n)` | `O(n log n)` / `O(n)` | 推荐掌握优化版 |

## 下一步建议

保留当前 DP 解法用于理解，再单独重写一次 `tails + lower_bound`，重点说清 `tails` 不是最终序列本身。

## 后续练习

1. `1143. Longest Common Subsequence` - 迁移到双序列前缀状态。
2. `354. Russian Doll Envelopes` - 练习 LIS 优化写法的应用。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/300.longest-increasing-subsequence.cpp`
- 新函数名：`lengthOfLISOpt`
- 保留用户原实现：是
