# 题解点评 - 740. Delete and Earn

## 基本信息

- 日期：2026-06-21
- 主题：动态规划 / 数值相邻约束
- 难度：中等
- 本次结果：通过，建模迁移正确
- 对应源码：`src/740.delete-and-earn.cpp`
- 资料来源：LeetCode 官方题目页 `https://leetcode.cn/problems/delete-and-earn/` 与本地源码
- 查询日期：2026-06-21

## 用户思路概述

1. 统计每个数值出现次数，`cnt[x] * x` 表示选择数值 `x` 能获得的总点数。
2. 找到输入中的最小值和最大值，只在这个范围内做状态推进。
3. 维护两个滚动变量，表达前两项和前一项的最优结果。
4. 对每个数值 `i`，选择它就不能选择 `i - 1`，不选它则沿用前一项结果。
5. 返回滚动后的最大点数。

## 用户解法复杂度

- 时间复杂度：`O(n + U)`，其中 `U` 是最大值和最小值之间的数值范围
- 空间复杂度：`O(M)`，其中 `M` 是题目允许的最大数值范围
- 复杂度来源：一次统计频次，一次数值区间扫描。

## 用户代码注释版

```cpp
class Solution {
public:
    int deleteAndEarn(vector<int>& nums) {
        int mn = 1e4+1, mx=0;
        vector<int> cnt(1e4+1, 0);
        for(auto num: nums) {
            cnt[num]++;
            mn = min(mn, num);
            mx = max(mx, num);
        }
        int a=0, b=mn*cnt[mn], ans=b; // a 是前两项最优，b 是前一项最优。
        for(int i=mn+1; i<=mx; i++) {
            ans = max(b, a+cnt[i]*i); // 不选 i，或选 i 并接上 i-2 之前的结果。
            a = b;
            b = ans;
        }
        return ans;
    }
};
```

## 关键理解点

| 理解点 | 用户当前表现 | 影响 | 建议 |
| --- | --- | --- | --- |
| 建模转换 | 把相邻数值冲突转成打家劫舍 | 非常关键，方向正确 | 这是本题最值得沉淀的迁移模式 |
| 聚合点数 | 用 `cnt[i] * i` 表示选择该数值收益 | 正确消除重复元素影响 | 也可以直接建 `points[i] += i` |
| 滚动变量 | 已经使用 `a/b` 压缩空间 | 复杂度意识不错 | 变量名可更语义化 |
| 数值范围 | 只扫描 `mn..mx` | 避免无意义前缀扫描 | 若约束变化，改用 `maxValue` 动态开数组 |

## 算法优缺点

| 方案 | 优点 | 缺点 | 适用情况 |
| --- | --- | --- | --- |
| 用户解法 | 建模正确，空间滚动到 `O(1)` 状态 | `a/b/ans` 语义略隐晦，数组大小写死 | 当前约束下可以通过 |
| 推荐最优解 | 用 `points` 和语义变量表达收益与状态 | 会从 0 扫到最大值 | 更易读，更方便迁移 |

## 最优解法

1. 先把每个数值能贡献的总点数聚合到 `points[value]`。
2. 数值 `value` 与 `value - 1` 不能同时选，结构等价于线性相邻选择限制。
3. 用两个变量滚动保存前两项和前一项最优值。

- 最优时间复杂度：`O(n + M)`
- 最优空间复杂度：`O(M)`

### 最优解代码

```cpp
class Solution {
public:
    int deleteAndEarn(vector<int>& nums) {
        int maxValue = *max_element(nums.begin(), nums.end());
        vector<int> points(maxValue + 1, 0);
        for (int num : nums) {
            points[num] += num;
        }

        int bestTwoBack = 0;
        int bestOneBack = 0;
        for (int value = 0; value <= maxValue; value++) {
            // 选择 value 会删除 value-1，等价于相邻房屋不能同时选。
            int current = max(bestOneBack, bestTwoBack + points[value]);
            bestTwoBack = bestOneBack;
            bestOneBack = current;
        }
        return bestOneBack;
    }
};
```

## 对比与改进方向

| 对比项 | 用户代码 | 最优解代码 | 改进方向 |
| --- | --- | --- | --- |
| 状态定义 | `a/b` 表示前两项和前一项 | 语义变量表达同样状态 | 命名更清楚 |
| 更新逻辑 | `max(b, a + cnt[i] * i)` | `max(bestOneBack, bestTwoBack + points[value])` | 本质一致 |
| 边界处理 | 从最小值开始初始化 | 从 0 开始统一滚动 | 两种都正确 |
| 复杂度 | `O(n + U)` / 固定数组 | `O(n + M)` / 动态数组 | 当前写法扫描更少，推荐写法更直观 |

## 下一步建议

这题完成质量不错。复盘重点是把题面里的“删除相邻数值”翻译成“相邻位置不能同时选”。

## 后续练习

1. `213. House Robber II` - 对照同一线性模板在环形限制中的拆分方式。
2. `198. House Robber` - 回看相邻选择限制的最小骨架。

## 代码同步

- 已将最优解作为新的解题函数写入：`src/740.delete-and-earn.cpp`
- 新函数名：`deleteAndEarnOpt`
- 保留用户原实现：是
