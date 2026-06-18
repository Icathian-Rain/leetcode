# 题解点评 - 698. Partition to K Equal Sum Subsets

## 基本信息

- 日期：2026-06-18
- 主题：回溯 / 分组分配与剪枝
- 难度：中等
- 本次结果：待提交验证，源码逻辑检查通过
- 对应源码：`src/698.partition-to-k-equal-sum-subsets.cpp`
- 资料来源：LeetCode 官方题目页 `https://leetcode.cn/problems/partition-to-k-equal-sum-subsets/`
- 查询日期：2026-06-18

## 用户思路概述

1. 先计算总和，如果不能被 `k` 整除，直接返回 `false`。
2. 目标桶和为 `sum / k`。
3. 将 `nums` 从大到小排序，优先放大数，增强剪枝。
4. 用 `bucket[i]` 表示第 `i` 个桶当前和。
5. 递归按顺序把每个数字尝试放入某个不超目标的桶。
6. 如果某个空桶尝试失败，就不再尝试其他空桶，利用对称性剪枝。

## 用户解法复杂度

- 时间复杂度：最坏接近 `O(k^n)`
- 空间复杂度：`O(k + n)`
- 复杂度来源：每个数字最多尝试放入 `k` 个桶；排序和空桶剪枝能显著减少实际分支。

## 用户代码注释版

```cpp
class Solution {
public:
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        int sum = 0;
        for (auto num : nums) sum += num;
        if (sum % k != 0) return false;

        int target = sum / k;
        sort(nums.begin(), nums.end(), greater<int>()); // 大数优先放，失败更早暴露。
        vector<int> bucket(k, 0);
        if (nums[0] > target) return false;

        function<bool(int)> dfs = [&](int idx) {
            if (idx == nums.size()) return true;

            int x = nums[idx];
            for (int i = 0; i < k; i++) {
                if (bucket[i] + x > target) continue;
                bucket[i] += x;
                if (dfs(idx + 1)) return true;
                bucket[i] -= x;

                if (bucket[i] == 0) break; // 空桶等价，减少重复尝试。
            }
            return false;
        };

        return dfs(0);
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 可行性预判 | 总和整除、最大数不超目标 | 能提前排除明显无解 | 正确 |
| 分配模型 | 每个数尝试放入一个桶 | 命中本题核心建模 | 比枚举子集更直观 |
| 剪枝 | 降序排序 + 空桶剪枝 | 能显著减少重复搜索 | 可以再加相同桶和跳过 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 建模稳，剪枝意识很好 | 可补“相同桶和跳过”的剪枝 | 适合本题 |
| 推荐最优解 | 保留降序与空桶剪枝，代码语义更集中 | 本质仍是指数搜索 | 适合分组分配类题 |

## 最优解法

1. 判断总和是否可整除。
2. 降序排序，优先分配大数。
3. 用 `buckets` 维护每组当前和。
4. 当前数字尝试放入每个合法桶。
5. 空桶失败后跳过其他空桶。

- 最优时间复杂度：最坏 `O(k^n)`
- 最优空间复杂度：`O(k + n)`

### 最优解代码

```cpp
class Solution {
public:
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        int total = accumulate(nums.begin(), nums.end(), 0);
        if (total % k != 0) return false;

        int target = total / k;
        sort(nums.begin(), nums.end(), greater<int>());
        if (!nums.empty() && nums[0] > target) return false;

        vector<int> buckets(k, 0);
        function<bool(int)> dfs = [&](int index) {
            if (index == static_cast<int>(nums.size())) return true;

            int value = nums[index];
            for (int bucket = 0; bucket < k; ++bucket) {
                if (buckets[bucket] + value > target) continue;
                buckets[bucket] += value;
                if (dfs(index + 1)) return true;
                buckets[bucket] -= value;

                if (buckets[bucket] == 0) {
                    break; // 空桶等价，当前空桶失败后无需尝试其他空桶。
                }
            }
            return false;
        };

        return dfs(0);
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | `bucket` 当前桶和 | 相同 | 正确 |
| 更新逻辑 | 放入桶、递归、撤销 | 相同 | 主干正确 |
| 边界处理 | 总和整除和最大数检查 | 相同 | 正确 |
| 复杂度 | 最坏 `O(k^n)` | 最坏 `O(k^n)` | 靠剪枝控制实际运行 |

## 下一步建议

这题建议重点复盘“把数字分配进桶”的建模。遇到 `k` 组、等和、分配类题时，优先想桶状态，而不是强行枚举所有子集。

## 后续练习

1. `473. Matchsticks to Square` - 四个桶的同类分配题。
2. `52. N-Queens II` - 对比“找到可行分配”和“统计方案数”的返回形式。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/698.partition-to-k-equal-sum-subsets.cpp`
- 新函数名：`canPartitionKSubsetsOpt`
- 保留用户原实现：是
