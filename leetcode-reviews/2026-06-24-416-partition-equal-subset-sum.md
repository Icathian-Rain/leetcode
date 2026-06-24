# 题解点评 - 416. Partition Equal Subset Sum

## 基本信息

- 日期：2026-06-24
- 主题：动态规划 / 目标可达性
- 难度：中等
- 本次结果：有阻塞级实现风险，核心思路正确
- 对应源码：`src/416.partition-equal-subset-sum.cpp`
- 资料来源：LeetCode 官方题目页 `https://leetcode.cn/problems/partition-equal-subset-sum/` 与本地源码
- 查询日期：2026-06-24

## 用户思路概述

1. 先统计数组总和。
2. 如果总和为奇数，直接返回 `false`。
3. 把目标转成是否能选出若干数字凑成 `sum / 2`。
4. 用 `dp[j]` 表示容量 `j` 是否可达。
5. 每个数字只能使用一次，所以容量从大到小更新。

## 用户解法复杂度

- 时间复杂度：`O(n * target)`
- 空间复杂度：`O(target)`
- 复杂度来源：每个数都尝试更新从 `target` 到 `num` 的所有容量。

## 用户代码注释版

```cpp
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int n=nums.size();
        int sum = 0, maxNum; // 风险：maxNum 未初始化，后续 max(maxNum, num) 是未定义行为。
        for(auto num: nums) {
            sum += num;
            maxNum = max(maxNum, num);
        }
        if(sum %2 != 0) {
            return false;
        }
        int target = sum/2;
        if(maxNum > target) {
            return false;
        }

        vector<bool> dp(target+1, false);
        dp[0]=true;
        for(int i=0; i<n; i++) {
            int num = nums[i];
            for(int j=target; j>=num; j--) {
                dp[j] = dp[j]|dp[j-num]; // 倒序保证每个 num 只用一次。
            }
        }
        return dp[target];
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 问题转换 | 转成凑出 `sum / 2` | 建模正确 | 这是本题核心 |
| 可达状态 | `dp[j]` 表示容量是否可达 | 状态定义清晰 | `dp[0] = true` 是空集合基础 |
| 遍历方向 | 容量倒序 | 正确保证每个数字只用一次 | 和 322 的正序形成对照 |
| 变量初始化 | `maxNum` 未初始化 | 会导致未定义行为，可能误判或结果不稳定 | 初始化为 `0`，或直接删掉该剪枝 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 背包方向正确，空间已压缩 | `maxNum` 未初始化是阻塞级风险 | 修掉初始化后就是标准解 |
| 推荐最优解 | 去掉不必要剪枝，状态更简洁 | 少了 `maxNum > target` 的提前返回 | 更稳、更少出错点 |

## 最优解法

1. 计算总和，奇数直接返回 `false`。
2. 目标为 `sum / 2`。
3. `dp[j]` 表示是否能用已处理数字凑出 `j`。
4. 每个数字只能使用一次，所以容量从大到小更新。

- 最优时间复杂度：`O(n * target)`
- 最优空间复杂度：`O(target)`

### 最优解代码

```cpp
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if (sum % 2 != 0) return false;

        int target = sum / 2;
        vector<bool> dp(target + 1, false);
        dp[0] = true;
        for (int num : nums) {
            // 每个数只能使用一次，所以容量必须从大到小更新。
            for (int value = target; value >= num; value--) {
                dp[value] = dp[value] || dp[value - num];
            }
        }
        return dp[target];
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | 容量是否可达 | 相同 | 正确 |
| 更新逻辑 | 倒序更新 | 倒序更新 | 正确 |
| 边界处理 | 奇数总和、最大值剪枝 | 奇数总和 | 初始化 `maxNum` 或删除剪枝 |
| 复杂度 | `O(n*target)` / `O(target)` | `O(n*target)` / `O(target)` | 数量级一致 |

## 下一步建议

先修掉 `maxNum` 未初始化，再补测 `[1,5,11,5]`、`[1,2,3,5]` 和单个大数场景。核心 DP 思路已经对了。

## 后续练习

1. `494. Target Sum` - 把目标计数也转成容量问题。
2. `1049. Last Stone Weight II` - 练习同类“分成两组尽量接近”的转换。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/416.partition-equal-subset-sum.cpp`
- 新函数名：`canPartitionOpt`
- 保留用户原实现：是
