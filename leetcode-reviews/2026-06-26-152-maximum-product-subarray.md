# 题解点评 - 152. Maximum Product Subarray

## 基本信息

- 日期：2026-06-26
- 主题：动态规划 / 单序列极值状态
- 难度：中等
- 本次结果：通过，最大最小双状态维护正确
- 对应源码：`src/152.maximum-product-subarray.cpp`
- 资料来源：LeetCode 官方题目页 `https://leetcode.cn/problems/maximum-product-subarray/` 与本地源码
- 查询日期：2026-06-26

## 用户思路概述

1. 用 `mx` 表示以当前位置结尾的最大乘积。
2. 用 `mn` 表示以当前位置结尾的最小乘积。
3. 因为负数会让最大值和最小值互换角色，所以每次同时用旧的最大、旧的最小和当前数更新。
4. 用 `ans` 记录所有位置中的最大乘积。

## 用户解法复杂度

- 时间复杂度：`O(n)`
- 空间复杂度：`O(1)`

## 用户代码注释版

```cpp
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int n=nums.size();
        int mx = nums[0], mn = nums[0], ans = nums[0];
        for(int i=1; i<n; i++) {
            int premx = mx, premn = mn; // 必须保存旧值，避免更新后互相污染。
            mx = max({premx*nums[i], nums[i], premn*nums[i]});
            mn = min({premx*nums[i], nums[i], premn*nums[i]});
            ans = max(mx, ans);
        }
        return ans;
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 双状态 | 同时维护最大和最小 | 正确处理负数翻转 | 这是本题核心 |
| 旧值保存 | 用 `premx/premn` | 避免状态污染 | 写法很稳 |
| 零的处理 | 当前数单独参与比较 | 能自然重启子数组 | 继续保持 |

## 最优解法

当前写法已经是最优复杂度。推荐只把变量名改得更语义化。

- 最优时间复杂度：`O(n)`
- 最优空间复杂度：`O(1)`

### 最优解代码

```cpp
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int maxEndingHere = nums[0];
        int minEndingHere = nums[0];
        int answer = nums[0];
        for (int i = 1; i < static_cast<int>(nums.size()); i++) {
            int num = nums[i];
            int prevMax = maxEndingHere;
            int prevMin = minEndingHere;
            // 负数会让最大和最小互换角色，所以两者都要维护。
            maxEndingHere = max({num, prevMax * num, prevMin * num});
            minEndingHere = min({num, prevMax * num, prevMin * num});
            answer = max(answer, maxEndingHere);
        }
        return answer;
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | `mx/mn` | 语义化最大/最小结尾 | 本质相同 |
| 更新逻辑 | 三者取极值 | 相同 | 正确 |
| 边界处理 | 从 `nums[0]` 初始化 | 相同 | 正确 |
| 复杂度 | `O(n)` / `O(1)` | `O(n)` / `O(1)` | 已最优 |

## 下一步建议

这题可以直接过。复盘时重点说清为什么最大乘积题不能只维护最大值。

## 后续练习

1. `53. Maximum Subarray` - 对照只维护最大结尾的版本。
2. `309. Best Time to Buy and Sell Stock with Cooldown` - 继续练多状态表达。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/152.maximum-product-subarray.cpp`
- 新函数名：`maxProductOpt`
- 保留用户原实现：是
